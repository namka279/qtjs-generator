// Auto generated file, don't modify.

#ifndef __META_QTGUI_QSCREEN_H
#define __META_QTGUI_QSCREEN_H


#include <qtGui_cpgf_compat.h>

#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"
#include "cpgf/scriptbind/gscriptbindutil.h"
#include "cpgf/scriptbind/gscriptwrapper.h"
#include "cpgf/gscopedinterface.h"




namespace meta_qtgui { 


template <typename D>
void buildMetaClass_QScreen(const cpgf::GMetaDataConfigFlags & config, D _d)
{
    (void)config; (void)_d; (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _field("staticMetaObject", &D::ClassType::staticMetaObject);
    _d.CPGF_MD_TEMPLATE _method("metaObject", &D::ClassType::metaObject);
    _d.CPGF_MD_TEMPLATE _method("qt_metacast", &D::ClassType::qt_metacast);
    _d.CPGF_MD_TEMPLATE _method("qt_metacall", &D::ClassType::qt_metacall);
    _d.CPGF_MD_TEMPLATE _method("name", &D::ClassType::name);
    _d.CPGF_MD_TEMPLATE _method("depth", &D::ClassType::depth);
    _d.CPGF_MD_TEMPLATE _method("size", &D::ClassType::size);
    _d.CPGF_MD_TEMPLATE _method("geometry", &D::ClassType::geometry);
    _d.CPGF_MD_TEMPLATE _method("physicalSize", &D::ClassType::physicalSize);
    _d.CPGF_MD_TEMPLATE _method("physicalDotsPerInchX", &D::ClassType::physicalDotsPerInchX);
    _d.CPGF_MD_TEMPLATE _method("physicalDotsPerInchY", &D::ClassType::physicalDotsPerInchY);
    _d.CPGF_MD_TEMPLATE _method("physicalDotsPerInch", &D::ClassType::physicalDotsPerInch);
    _d.CPGF_MD_TEMPLATE _method("logicalDotsPerInchX", &D::ClassType::logicalDotsPerInchX);
    _d.CPGF_MD_TEMPLATE _method("logicalDotsPerInchY", &D::ClassType::logicalDotsPerInchY);
    _d.CPGF_MD_TEMPLATE _method("logicalDotsPerInch", &D::ClassType::logicalDotsPerInch);
    _d.CPGF_MD_TEMPLATE _method("devicePixelRatio", &D::ClassType::devicePixelRatio);
    _d.CPGF_MD_TEMPLATE _method("availableSize", &D::ClassType::availableSize);
    _d.CPGF_MD_TEMPLATE _method("availableGeometry", &D::ClassType::availableGeometry);
    _d.CPGF_MD_TEMPLATE _method("virtualSiblings", &D::ClassType::virtualSiblings);
    _d.CPGF_MD_TEMPLATE _method("virtualSize", &D::ClassType::virtualSize);
    _d.CPGF_MD_TEMPLATE _method("virtualGeometry", &D::ClassType::virtualGeometry);
    _d.CPGF_MD_TEMPLATE _method("availableVirtualSize", &D::ClassType::availableVirtualSize);
    _d.CPGF_MD_TEMPLATE _method("availableVirtualGeometry", &D::ClassType::availableVirtualGeometry);
    _d.CPGF_MD_TEMPLATE _method("primaryOrientation", &D::ClassType::primaryOrientation);
    _d.CPGF_MD_TEMPLATE _method("orientation", &D::ClassType::orientation);
    _d.CPGF_MD_TEMPLATE _method("nativeOrientation", &D::ClassType::nativeOrientation);
    _d.CPGF_MD_TEMPLATE _method("orientationUpdateMask", &D::ClassType::orientationUpdateMask);
    _d.CPGF_MD_TEMPLATE _method("setOrientationUpdateMask", &D::ClassType::setOrientationUpdateMask);
    _d.CPGF_MD_TEMPLATE _method("angleBetween", &D::ClassType::angleBetween);
    _d.CPGF_MD_TEMPLATE _method("transformBetween", &D::ClassType::transformBetween);
    _d.CPGF_MD_TEMPLATE _method("mapBetween", &D::ClassType::mapBetween);
    _d.CPGF_MD_TEMPLATE _method("isPortrait", &D::ClassType::isPortrait);
    _d.CPGF_MD_TEMPLATE _method("isLandscape", &D::ClassType::isLandscape);
    _d.CPGF_MD_TEMPLATE _method("grabWindow", &D::ClassType::grabWindow, cpgf::MakePolicy<cpgf::GMetaRuleParamNoncopyable<-1> >())
        ._default(copyVariantFromCopyable(-1))
        ._default(copyVariantFromCopyable(-1))
        ._default(copyVariantFromCopyable(0))
        ._default(copyVariantFromCopyable(0))
    ;
    _d.CPGF_MD_TEMPLATE _method("refreshRate", &D::ClassType::refreshRate);
    _d.CPGF_MD_TEMPLATE _method("geometryChanged", &D::ClassType::geometryChanged);
    _d.CPGF_MD_TEMPLATE _method("physicalSizeChanged", &D::ClassType::physicalSizeChanged);
    _d.CPGF_MD_TEMPLATE _method("physicalDotsPerInchChanged", &D::ClassType::physicalDotsPerInchChanged);
    _d.CPGF_MD_TEMPLATE _method("logicalDotsPerInchChanged", &D::ClassType::logicalDotsPerInchChanged);
    _d.CPGF_MD_TEMPLATE _method("virtualGeometryChanged", &D::ClassType::virtualGeometryChanged);
    _d.CPGF_MD_TEMPLATE _method("primaryOrientationChanged", &D::ClassType::primaryOrientationChanged);
    _d.CPGF_MD_TEMPLATE _method("orientationChanged", &D::ClassType::orientationChanged);
    _d.CPGF_MD_TEMPLATE _method("refreshRateChanged", &D::ClassType::refreshRateChanged);
    _d.CPGF_MD_TEMPLATE _method("tr", &D::ClassType::tr)
        ._default(copyVariantFromCopyable(-1))
        ._default(copyVariantFromCopyable(0))
    ;
}


class QScreenWrapper : public QScreen, public cpgf::GScriptWrapper {
public:
    
    void connectNotify(const QMetaMethod & signal)
    {
        cpgf::GScopedInterface<cpgf::IScriptFunction> func(this->getScriptFunction("connectNotify"));
        if(func)
        {
            cpgf::invokeScriptFunction(func.get(), this, signal);
            return;
        }
        QObject::connectNotify(signal);
    }
    void super_connectNotify(const QMetaMethod & signal)
    {
        QObject::connectNotify(signal);
    }
    
    void customEvent(QEvent * __arg0)
    {
        cpgf::GScopedInterface<cpgf::IScriptFunction> func(this->getScriptFunction("customEvent"));
        if(func)
        {
            cpgf::invokeScriptFunction(func.get(), this, __arg0);
            return;
        }
        QObject::customEvent(__arg0);
    }
    void super_customEvent(QEvent * __arg0)
    {
        QObject::customEvent(__arg0);
    }
    
    void childEvent(QChildEvent * __arg0)
    {
        cpgf::GScopedInterface<cpgf::IScriptFunction> func(this->getScriptFunction("childEvent"));
        if(func)
        {
            cpgf::invokeScriptFunction(func.get(), this, __arg0);
            return;
        }
        QObject::childEvent(__arg0);
    }
    void super_childEvent(QChildEvent * __arg0)
    {
        QObject::childEvent(__arg0);
    }
    
    bool isSignalConnected(const QMetaMethod & signal) const
    {
        return QObject::isSignalConnected(signal);
    }
    
    bool event(QEvent * __arg0)
    {
        cpgf::GScopedInterface<cpgf::IScriptFunction> func(this->getScriptFunction("event"));
        if(func)
        {
            return cpgf::fromVariant<bool >(cpgf::invokeScriptFunction(func.get(), this, __arg0));
        }
        return QObject::event(__arg0);
    }
    bool super_event(QEvent * __arg0)
    {
        return QObject::event(__arg0);
    }
    
    int receivers(const char * signal) const
    {
        return QObject::receivers(signal);
    }
    
    int qt_metacall(QMetaObject::Call __arg0, int __arg1, void ** __arg2)
    {
        cpgf::GScopedInterface<cpgf::IScriptFunction> func(this->getScriptFunction("qt_metacall"));
        if(func)
        {
            return cpgf::fromVariant<int >(cpgf::invokeScriptFunction(func.get(), this, __arg0, __arg1, __arg2));
        }
        return QScreen::qt_metacall(__arg0, __arg1, __arg2);
    }
    int super_qt_metacall(QMetaObject::Call __arg0, int __arg1, void ** __arg2)
    {
        return QScreen::qt_metacall(__arg0, __arg1, __arg2);
    }
    
    void timerEvent(QTimerEvent * __arg0)
    {
        cpgf::GScopedInterface<cpgf::IScriptFunction> func(this->getScriptFunction("timerEvent"));
        if(func)
        {
            cpgf::invokeScriptFunction(func.get(), this, __arg0);
            return;
        }
        QObject::timerEvent(__arg0);
    }
    void super_timerEvent(QTimerEvent * __arg0)
    {
        QObject::timerEvent(__arg0);
    }
    
    int senderSignalIndex() const
    {
        return QObject::senderSignalIndex();
    }
    
    void disconnectNotify(const QMetaMethod & signal)
    {
        cpgf::GScopedInterface<cpgf::IScriptFunction> func(this->getScriptFunction("disconnectNotify"));
        if(func)
        {
            cpgf::invokeScriptFunction(func.get(), this, signal);
            return;
        }
        QObject::disconnectNotify(signal);
    }
    void super_disconnectNotify(const QMetaMethod & signal)
    {
        QObject::disconnectNotify(signal);
    }
    
    bool eventFilter(QObject * __arg0, QEvent * __arg1)
    {
        cpgf::GScopedInterface<cpgf::IScriptFunction> func(this->getScriptFunction("eventFilter"));
        if(func)
        {
            return cpgf::fromVariant<bool >(cpgf::invokeScriptFunction(func.get(), this, __arg0, __arg1));
        }
        return QObject::eventFilter(__arg0, __arg1);
    }
    bool super_eventFilter(QObject * __arg0, QEvent * __arg1)
    {
        return QObject::eventFilter(__arg0, __arg1);
    }
    
    void * qt_metacast(const char * __arg0)
    {
        cpgf::GScopedInterface<cpgf::IScriptFunction> func(this->getScriptFunction("qt_metacast"));
        if(func)
        {
            return cpgf::fromVariant<void * >(cpgf::invokeScriptFunction(func.get(), this, __arg0));
        }
        return QScreen::qt_metacast(__arg0);
    }
    void * super_qt_metacast(const char * __arg0)
    {
        return QScreen::qt_metacast(__arg0);
    }
    
    QObject * sender() const
    {
        return QObject::sender();
    }
    
    const QMetaObject * metaObject() const
    {
        cpgf::GScopedInterface<cpgf::IScriptFunction> func(this->getScriptFunction("metaObject"));
        if(func)
        {
            return cpgf::fromVariant<const QMetaObject * >(cpgf::invokeScriptFunction(func.get(), this));
        }
        return QScreen::metaObject();
    }
    const QMetaObject * super_metaObject() const
    {
        return QScreen::metaObject();
    }
};


template <typename D>
void buildMetaClass_QScreenWrapper(const cpgf::GMetaDataConfigFlags & config, D _d)
{
    (void)config; (void)_d; (void)_d;
    using namespace cpgf;
    
    
    _d.CPGF_MD_TEMPLATE _method("connectNotify", (void (D::ClassType::*) (const QMetaMethod &))&D::ClassType::connectNotify);
    _d.CPGF_MD_TEMPLATE _method("customEvent", (void (D::ClassType::*) (QEvent *))&D::ClassType::customEvent);
    _d.CPGF_MD_TEMPLATE _method("childEvent", (void (D::ClassType::*) (QChildEvent *))&D::ClassType::childEvent);
    _d.CPGF_MD_TEMPLATE _method("isSignalConnected", (bool (D::ClassType::*) (const QMetaMethod &) const)&D::ClassType::isSignalConnected);
    _d.CPGF_MD_TEMPLATE _method("receivers", (int (D::ClassType::*) (const char *) const)&D::ClassType::receivers);
    _d.CPGF_MD_TEMPLATE _method("timerEvent", (void (D::ClassType::*) (QTimerEvent *))&D::ClassType::timerEvent);
    _d.CPGF_MD_TEMPLATE _method("senderSignalIndex", (int (D::ClassType::*) () const)&D::ClassType::senderSignalIndex);
    _d.CPGF_MD_TEMPLATE _method("disconnectNotify", (void (D::ClassType::*) (const QMetaMethod &))&D::ClassType::disconnectNotify);
    _d.CPGF_MD_TEMPLATE _method("sender", (QObject * (D::ClassType::*) () const)&D::ClassType::sender);
    _d.CPGF_MD_TEMPLATE _method("super_connectNotify", (void (D::ClassType::*) (const QMetaMethod &))&D::ClassType::super_connectNotify);
    _d.CPGF_MD_TEMPLATE _method("super_customEvent", (void (D::ClassType::*) (QEvent *))&D::ClassType::super_customEvent);
    _d.CPGF_MD_TEMPLATE _method("super_childEvent", (void (D::ClassType::*) (QChildEvent *))&D::ClassType::super_childEvent);
    _d.CPGF_MD_TEMPLATE _method("super_event", (bool (D::ClassType::*) (QEvent *))&D::ClassType::super_event);
    _d.CPGF_MD_TEMPLATE _method("super_qt_metacall", (int (D::ClassType::*) (QMetaObject::Call, int, void **))&D::ClassType::super_qt_metacall);
    _d.CPGF_MD_TEMPLATE _method("super_timerEvent", (void (D::ClassType::*) (QTimerEvent *))&D::ClassType::super_timerEvent);
    _d.CPGF_MD_TEMPLATE _method("super_disconnectNotify", (void (D::ClassType::*) (const QMetaMethod &))&D::ClassType::super_disconnectNotify);
    _d.CPGF_MD_TEMPLATE _method("super_eventFilter", (bool (D::ClassType::*) (QObject *, QEvent *))&D::ClassType::super_eventFilter);
    _d.CPGF_MD_TEMPLATE _method("super_qt_metacast", (void * (D::ClassType::*) (const char *))&D::ClassType::super_qt_metacast);
    _d.CPGF_MD_TEMPLATE _method("super_metaObject", (const QMetaObject * (D::ClassType::*) () const)&D::ClassType::super_metaObject);
    
    buildMetaClass_QScreen<D>(config, _d);
}


} // namespace meta_qtgui




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif