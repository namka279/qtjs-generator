var config = {
  projectID : "QtCore",

  headerOutput : "build/QtCore/include",
  sourceOutput : "build/QtCore/src",

  metaItemCallback : processCallback,

  cppNamespace : "meta_qtcore",

  metaClassFunctionPrefix : "buildMetaClass_",
  metaClassCreatePrefix : "createMetaClass_",

  metaClassMainRegisterPrefix : "registerMain_",

  sourceFilePrefix : "meta_qtcore_",
  mainSourceFile : "register_meta_qtcore",

  wrapBitField : true, // default is true
  wrapOperator : true, // default is true

  autoRegisterToGlobal : true,

  metaNamespace : "qtcore",
  headerHeaderCode : "#include \"../../../qtcompat.h\"\n",
  sourceHeaderCode : "#include <QtCore/qglobal.h>\n#include <QtCore/QString>\n#include <QtCore/QDataStream>\n"
  +"#include <QtCore/QDateTime>\n"
  +"#include <QtCore/QTranslator>\n"
  +"#include <QtCore/QAbstractEventDispatcher>\n"
  +"#include <QtCore/QRegularExpression>\n"
  +"#include <QtCore/QUrl>\n"
  +"#include <QtCore/QAbstractNativeEventFilter>\n"
  +"#include <QtCore/QItemSelection>\n"
  +"#include <QtCore/QTextCodec>\n"
  +"#include <QtCore/qabstractanimation.h>\n"
  +"#include <QtCore/QDebug>\n"
  +"#include <QtCore/QThread>\n"
  +"#include <QtCore/QEvent>\n"
  +"#include <QtCore/QStringList>\n"
  +"#include <QtCore/QState>\n",
  //	sourceHeaderReplacer : [ "!.*Box2D[^/]*/Box2D!i", "Box2D" ],
//	metaHeaderPath : "cpgf/metadata/box2d/",
parameterTypeReplacer : [
  "Q_DECL_CONSTEXPR", "",
  "Q_CORE_EXPORT", "",
]
};

function processCallback(item, data)
{
  var name = item.getPrimaryName();
  print (">>>> "+item.getLocation()+"\n");

  if(item.isClass() && (name.indexOf('Private') >= 0)) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('/private/') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('qobject_impl') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('qatomic_sparc.h') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('qatomic_cxx11.h') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('qatomic_x86.h') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('_impl.h') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('/qatomic_') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('/qoldbasicatomic') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('windows.h') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('qglobal') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('qobjectdefs') >= 0) {		data.skipBind = true;	}

  if(item.getLocation().indexOf('easing') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('qmime') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('qabstractitemmodel') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('qabstractproxymodel') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('hash') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('qconfig') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('qshareddata') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('qfutureinterface') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('qtypetraits') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('qstate') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('qvariant') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('qfileinfo') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('qcoreevent') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('qmutex') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('qfuture') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('settings') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('cache') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('qflags') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('qcompilerde') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('qsize') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('qplugin') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('qmetatype') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('qsignalmapper') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('qstringbuilder') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('qarraydatapointer') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('qhistorystate') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('qstringmatcher') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('qwaitcondition') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('qmap') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('qidentityproxymodel') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('qfile') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('qregularexpression') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('qexception') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('qgenericatomic') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('qabstract') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('qlinkedlist') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('qtextcodec') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('qeventtransition') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('json') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('pointer') >= 0) {		data.skipBind = true;	}
  if(item.getLocation().indexOf('refcount') >= 0) {		data.skipBind = true;	}
  if(name.indexOf('Q_DECLARE_TYPEINFO') >= 0) {		data.skipBind = true;	}
  if(name.indexOf('QTypeInfo') >= 0) {		data.skipBind = true;	}
  if(name.indexOf('QUrl') >= 0) { // fails
    data.skipBind = true;
  }
  if(name.indexOf('QFinalState') >= 0) { // fails
    data.skipBind = true;
  }
  if(name.indexOf('Animation') >= 0) { // fails
    data.skipBind = true;
  }
  if(name.indexOf('QTimer') >= 0) { // fails
    data.skipBind = true;
  }
  if(name.indexOf('Semaphore') >= 0) { // fails
    data.skipBind = true;
  }
  if(name.indexOf('QAbstractState') >= 0) { // fails
    data.skipBind = true;
  }
  if(name.indexOf('QStateMachine') >= 0) { // fails
    data.skipBind = true;
  }
  if(name.indexOf('QObject') >= 0) { // fails
    data.skipBind = true;
  }
  if(name.indexOf('QDynamicMetaObjectData') >= 0) { // fails
    data.skipBind = true;
  }
  if(name.indexOf('QRegularExpression') >= 0) { // fails
    data.skipBind = true;
  }
  if(name.indexOf('QByteArray') >= 0) { // fails
    data.skipBind = true;
  }
  if(name.indexOf('QDataStream') >= 0) { // fails
    data.skipBind = true;
  }
  if(name.indexOf('QNoImplicitBoolCast') >= 0) { // fails
    data.skipBind = true;
  }
  if(name.indexOf('QVariant') >= 0) { // fails
    data.skipBind = true;
  }
  if(name.indexOf('QMeta') >= 0) { // fails
    data.skipBind = true;
  }
  if(name.indexOf('qmeta') >= 0) { // fails
    data.skipBind = true;
  }
  if(name.indexOf('QResource') >= 0) { // fails
    data.skipBind = true;
  }
  if(name.indexOf('QSortFilterProxyModel') >= 0) { // fails
    data.skipBind = true;
  }
  if(name.indexOf('QTranslator') >= 0) { // fails
    data.skipBind = true;
  }
  if(name.indexOf('QMimeData') >= 0) { // fails
    data.skipBind = true;
  }
  if(name.indexOf('QProcess') >= 0) { // fails
    data.skipBind = true;
  }
  if(name.indexOf('QThread') >= 0) { // fails
    data.skipBind = true;
  }
  if(name.indexOf('Q_PID') >= 0) { // fails
    data.skipBind = true;
  }
  if(name.indexOf('RefCount') >= 0) { // fails
    data.skipBind = true;
  }
  if(name.indexOf('QListData') >= 0) { // fails
    data.skipBind = true;
  }
  if(name.indexOf('QXmlStream') >= 0) { // fails
    data.skipBind = true;
  }
  if(name.indexOf('QJson') >= 0) { // fails
    data.skipBind = true;
  }
  if(name.indexOf('QStringListModel') >= 0) { // fails
    data.skipBind = true;
  }
  if(name.indexOf('QDir') >= 0) { // fails
    data.skipBind = true;
  }
  if(name.indexOf('QBitArray') >= 0) { // fails
    data.skipBind = true;
  }
  if(name.indexOf('QNoDebug') >= 0) { // fails
    data.skipBind = true;
  }
  switch (""+item.getQualifiedName()) {
    case "qErrnoWarning":
      case "qDebug":
      case "qWarning":
      case "qCritical":
      case "qFatal":
      case "QT_NO_QDEBUG_MACRO":
      case "QT_NO_QWARNING_MACRO":
      case "QMessageLogContext":
      case "QString::vsprintf":
      case "QString::fromStdString":
      case "QString::fromStdWString":
      case "qvsnprintf":
      case "QArrayData::ref":
        data.skipBind = true;
        break;
      case "QArrayData":
        item.getTraits().setDefaultConstructorHidden(true);
        item.getTraits().setCopyConstructorHidden(true);
        break;
      case "QTypedArrayData::begin":
      case "QTypedArrayData::end":
      case "QTypedArrayData::constBegin":
      case "QTypedArrayData::constEnd":
      case "QTypedArrayData::allocate":
      case "QTypedArrayData::fromRawData":
        if (item.getParameterList().size() > 0) {
          item.getParameterList().get(item.getParameterList().size()-1).setDefaultValue("QTypedArrayData<T>::"+item.getParameterList().get(0).getDefaultValue());
      }
    default:
      print("#"+item.getQualifiedName()+"\n");
  }
  if(item.isMethod()) {
    var params = item.getParameterList();
    for(var i = 0; i < params.size(); i++) {
      if ('...' == params.get(i).getType().getLiteralType()) {
        data.skipBind = true;
      }
    }
  }
}
