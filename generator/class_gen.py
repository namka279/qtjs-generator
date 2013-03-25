
import os
import re
from string import Template
import ast_info
import config
import itertools

MYDIR = os.path.dirname(os.path.realpath(__file__))


def class_template():
    return """
#include <qtjs_bindings/shared.h>

$includes

namespace qtjs_binder {

$shell_class_code

}

namespace vu8 {

template <>
struct ClassInfo< $class_name > {
    typedef qtjs_binder::$shell_class_name Impl;
};


}

namespace qtjs_binder {

void bind_${module}_$safe_class_name(vu8::Module &module)
{
    vu8::Class< $shell_class_name > classBinder;

    classBinder.Constructor< $constructors >();

$conversions
    ${method_binders}

    module("$safe_class_name", classBinder);
}

} // namespace
    """


def method_template():
    return """
        classBinder.Set< $method_type, &$class_name::$method >("$method");"""


def method_template_base():
    return """
        classBinder.Set< $base, $method_type, &$class_name::$method >("$method");"""


def method_params(cpp_method, template_params, param_limit=None):
    params = ast_info.retrieve_method_params(cpp_method)
    if None != param_limit:
        params = list(params)[:param_limit]
    return ', '.join([ast_info.type_to_string(p.type.get_canonical(), template_params) for p in params])


def is_type_blacklisted(cpp_type, template_params):
    typename = ast_info.type_to_string(cpp_type.get_canonical(), template_params)
    return config.is_class_private(typename) \
           or 'UNKNOWN:' in typename


def are_method_params_blacklisted(cpp_method, template_params):
    if is_type_blacklisted(cpp_method.result_type, template_params):
        return True
    for param in ast_info.retrieve_method_params(cpp_method):
        if is_type_blacklisted(param.type, template_params):
            return True
    return False


def method_type(cpp_method, template_params, param_limit = None):
    constness = ' const' if ast_info.parse_method_usr(cpp_method.get_usr())['const'] else ''
    return ast_info.type_to_string(cpp_method.result_type.get_canonical(), template_params) + \
        '('+method_params(cpp_method, template_params, param_limit)+')' + \
        constness


def method_definition(cpp_method, template_params, param_limit = None):
    constness = ' const' if ast_info.parse_method_usr(cpp_method.get_usr())['const'] else ''
    return ast_info.type_to_string(cpp_method.result_type.get_canonical(), template_params) + \
        ' ' + cpp_method.spelling + \
        '('+method_params(cpp_method, template_params, param_limit)+')' + \
        constness


def render_constructors(constructors, template_params):
    if len(constructors) == 0:
        return 'vu8::Factory<>'
    else:
        factories = []
        for constructor in constructors:
            param_count = len(list(ast_info.retrieve_method_params(constructor)))
            first_opt = ast_info.method_first_optional_param(constructor)
            if first_opt == None:
                first_opt = param_count
            for i in range(first_opt, param_count + 1):
                factories.append('vu8::Factory< ' + method_params(constructor, template_params, i) + ' > ')
        return 'vu8::FactorySelector< ' + ', '.join(factories) + ' > '


def filter_methods_by_access(methods, access = 'public'):
    for method_access, method in methods:
        if method_access == access:
            yield method


def render_method(classname, cpp_method, template_params, parent=None):
    if not parent:
        return Template(method_template()) \
            .substitute({
                'method_type':method_type(cpp_method, template_params),
                'class_name':classname,
                'method':cpp_method.spelling
            })
    else:
        return Template(method_template_base()) \
            .substitute({
                'method_type':method_type(cpp_method, template_params),
                'class_name':classname,
                'method':cpp_method.spelling,
                'base':parent
            })


def enumerate_optional_params(cpp_method):
    param_count = len(list(ast_info.retrieve_method_params(cpp_method)))
    first_opt = ast_info.method_first_optional_param(cpp_method)
    if first_opt == None:
        first_opt = param_count
    for i in range(first_opt, param_count+1):
        yield (i, list(ast_info.retrieve_method_params(cpp_method))[:i])


def render_methods(classname, methods, method_name, template_params):
    if len(methods) == 0:
        return ''
    elif len(methods) == 1 and not ast_info.method_has_optional_params(methods[0][1]):
        (parentname, cpp_method) = methods[0]
        return render_method((parentname if parentname else classname), cpp_method, template_params, parentname)
    else:
        method_binders = []
        for (pname, cppm) in methods:
            binding_class = (pname if pname else classname)
            for (i, _) in enumerate_optional_params(cppm):
                method_binders.append(
                    'vu8::Method< ' + \
                        binding_class +', '+ method_type(cppm, template_params, i) +', &' + binding_class + '::' + cppm.spelling + \
                    ' > '
                )
        return "\n        classBinder.Set< vu8::Selector< " + ', '.join(method_binders) + " > > (\""+method_name+"\");"


def sanitize_name(name):
    return   re.sub(r'^::', '', name) \
            .replace('::', '_') \
            .replace(' ', '') \
            .replace('<', '_') \
            .replace('>', '_') \
            .replace(',', '_c_') \
            .replace('&', '_R') \
            .replace('*', '_P')


def file_name_from_class(classname):
    return sanitize_name(classname) + '.cpp'


def render_arg(param, number):
    return (param.spelling if param.spelling else 'arg_'+str(number))


def render_shell_constructor(shellname, params, classname, template_params):
    return shellname+'(' + \
           ', '.join([
               ast_info.type_to_string(p.type.get_canonical(), template_params)+' '+ \
               render_arg(p, p_i) for (p_i, p) in enumerate(params)
           ]) + \
           ') : ' + classname + '(' + \
           ', '.join([
               render_arg(p, p_i) for (p_i, p) in enumerate(params)
           ]) + \
           ') {}'


def render_shell_constructors(constructors, classname, shellname, template_params):
    constructor_overrides = []
    for constructor in filter_methods_by_access(constructors):
        for (i, params) in enumerate_optional_params(constructor):
            constructor_overrides.append(
                render_shell_constructor(shellname, params, classname, template_params)
            )
    if 0 == len(constructor_overrides):
        constructor_overrides.append(shellname+'() : '+classname+'() {}')
    if config.can_copy_object(classname) and not has_copy_constructor(constructors, classname, template_params):
        constructor_overrides.append(shellname+'(const '+classname+ ' &arg1) : '+classname+'(arg1) {}')
    return '\n'.join(constructor_overrides) + '\n'


def has_copy_constructor(constructors, classname, template_params):
    for access, constructor in constructors:
        params = list(ast_info.retrieve_method_params(constructor))
        if 1 == len(params) \
            and ('const '+classname+' &' == ast_info.type_to_string(params[0].type.get_canonical(), template_params)):
            return True
    return False


def render_shell_method(method, params, method_class, template_params):
    constness = (' const' if ast_info.parse_method_usr(method.get_usr())['const'] else '')
    return  ast_info.type_to_string(method.result_type.get_canonical(), template_params) + ' ' + \
            method.spelling + '(' + \
            ', '.join([
                ast_info.type_to_string(p.type.get_canonical(), template_params)+' '+ \
                render_arg(p, p_i) for (p_i, p) in enumerate(params)
            ]) + \
            ')' + constness + '\n{\n' + \
            '  return '+method_class+'::'+method.spelling+'(' + \
            ', '.join([
                render_arg(p, p_i) for (p_i, p) in enumerate(params)
            ]) + \
            ');\n}\n'


def render_shell_methods(methods_by_name, classname, shellname, template_params):
    method_overrides = []
    addedMethods = []
    for (_, methods_for_name) in methods_by_name.items():
        for (method_class, method) in methods_for_name:
            if ast_info.method_has_optional_params(method):
                for (i, params) in enumerate_optional_params(method):
                    mdef = method_definition(method, template_params, i)
                    if mdef not in addedMethods:
                        addedMethods.append(mdef)
                        method_overrides.append(
                           render_shell_method(method, params, method_class, template_params)
                        )
    return '\n'.join(method_overrides)+'\n'


def generate_shell(cpp_class, module, classname, shellname, methods, template_params):
    return 'class '+shellname+' : public '+classname+' {\npublic:\n' + \
        render_shell_constructors(get_class_constructors(cpp_class, template_params), classname, shellname, template_params) + \
        '\n' + \
        render_shell_methods(methods, classname, shellname, template_params) + \
        '};'


def generate_class(classname, cpp_class, classfile, module, rootdir):
    target_dir = os.path.join(MYDIR, '..', 'generated_cpp', module)
    if not os.path.isdir(target_dir):
        os.makedirs(target_dir)

    template_args = {'module':module}

    template_params = extract_template_parameters(classname, cpp_class)

    shellname = '_Shell_'+sanitize_name(classname)
    methods_by_name = get_class_methods(cpp_class, classname, shellname, template_params)

    template_args['class_name'] = classname
    template_args['shell_class_name'] = shellname
    template_args['includes'] = "\n".join(["#include <"+path+">" for path in get_includes(cpp_class, rootdir) + [classfile]])
    template_args['safe_class_name'] = sanitize_name(classname)
    template_args['constructors'] = render_constructors(list(filter_methods_by_access(get_class_constructors(cpp_class, template_params))), template_params)
    template_args['method_binders'] = ''
    template_args['shell_class_code'] = generate_shell(cpp_class, module, classname, shellname, methods_by_name, template_params)
    if '<' in classname:
        # TODO: only partial support for class templates
        template_args['conversions'] = "    classBinder.ConvertibleTo< "+classname+" >();"
    else:
        template_args['conversions'] = "\n".join(["    classBinder.ConvertibleTo< "+ast_info.semantic_name(base)+" >();" for base in [cpp_class]+list(ast_info.retrieve_class_parents_recursive(cpp_class))])

    for (name, methods) in methods_by_name.items():
        methods = [(shellname if ast_info.method_has_optional_params(mt) else cl, mt) for (cl, mt) in methods]
        template_args['method_binders'] += render_methods(classname, methods, name, template_params)

    update_file(
        os.path.join(target_dir, file_name_from_class(classname)),
        Template(class_template()).substitute(template_args)
    )


def extract_template_parameters(classname, cpp_class):
    if not ast_info.is_class_template(cpp_class):
        return {}
    # TODO: implement proper param mapping as this approach fails on nested templates
    params = re.findall("(?<=^<|,)[^,]+(?=>$|,)", classname[(classname.index('<')):])
    paramNames = [p.displayname for p in ast_info.retrieve_template_params(cpp_class)]
    return dict(zip(paramNames, params))


def get_includes(classnode, rootdir):
    used_type_paths = set([t.location.file.name for t in ast_info.retrieve_used_types(classnode)]) | \
                    set([
                        t.location.file.name for p in ast_info.retrieve_class_parents(classnode) \
                        for t in ast_info.retrieve_used_types(p)
                    ])
    return sorted(set([
        path for path in used_type_paths if path.startswith(rootdir) and not config.is_include_blacklisted(path)
    ]))


def retrieve_class_constructors(classnode, template_params):
    for access, constructor in ast_info.retrieve_class_constructors(classnode):
        if not are_method_params_blacklisted(constructor, template_params):
            yield access, constructor


def get_class_constructors(classnode, template_params):
    return list(retrieve_class_constructors(classnode, template_params))


def get_class_methods(cpp_class, classname, shellname, template_params):
    methods_by_name = {}
    added_methods = {}
    for (access, method) in ast_info.retrieve_class_methods(cpp_class):
        if should_include_method(classname, method, access, template_params):
            if method.spelling not in methods_by_name:
                methods_by_name[method.spelling] = []
            methods_by_name[method.spelling].append( (classname, method) )
        for (i, _) in enumerate_optional_params(method):
            added_methods[method_definition(method, template_params, i)] = True

    for base in ast_info.retrieve_class_parents_recursive(cpp_class):
        for (access, method) in ast_info.retrieve_class_methods(base):
            mdef = method_definition(method, template_params)
            rel_basename = shellname+classname[classname.rindex('::'):]+"::"+base.displayname
            abs_basename = ast_info.semantic_name(base)
            if mdef not in added_methods and should_include_method(abs_basename, method, access, template_params):
                if method.spelling not in methods_by_name:
                    methods_by_name[method.spelling] = []
                methods_by_name[method.spelling].append( (rel_basename, method) )
                for (i, _) in enumerate_optional_params(method):
                    added_methods[method_definition(method, template_params, i)] = True

    return methods_by_name


def should_include_method(classname, method, access, template_params):
    return not config.should_skip_class_method(classname, method.spelling) \
           and not are_method_params_blacklisted(method, template_params) \
           and access == 'public'


def update_file(filename, file_content):
    if not is_file_content_same(filename, file_content):
        target_file = open(filename, 'w')
        target_file.write(file_content)
        target_file.close()


def is_file_content_same(filename, file_content):
    orig_content = ''
    try:
        target_file = open(filename, 'r')
        orig_content = target_file.read()
        target_file.close()
    except IOError:
        return False

    return file_content == orig_content


