
#include "dynamic_qobject.h"

#include <QStringList>
#include <QDate>
#include <QTime>
#include <QDateTime>
#include <QBitArray>
#include <QSize>
#include <QSizeF>
#include <QRect>
#include <QRectF>
#include <QLine>
#include <QLineF>
#include <QPoint>
#include <QPointF>
#include <QUrl>
#include <QEasingCurve>
#include <QLocale>

#include <private/qmetaobjectbuilder_p.h>

#include "llvmapi.h"

// for QVariant - cpgf interop ->
#include <qtCore_cpgf_compat.h>
#include <qtGui_cpgf_compat.h>
#include <qtQml_cpgf_compat.h>
#include <qtWidgets_cpgf_compat.h>

#include <QUuid>
#include <QJsonArray>
#include <QJsonDocument>
// <- for QVariant - cpgf interop

#include "callInfo.h"
#include "autoCallback.h"

namespace qtjs_binder {


DynamicMetaObjects::DynamicMetaObjects()
{
    nextId = 0;
    allocated = 10;
    metaObjects = (QMetaObject **) malloc(sizeof(QMetaObject *) * allocated);
}

DynamicMetaObjects::~DynamicMetaObjects()
{
    dispose();
}

void DynamicMetaObjects::dispose()
{
    if (metaObjects) {
        for (unsigned int i = 0; i < nextId; i++) {
            free(metaObjects[i]);
        }
        free(metaObjects);
        metaObjects = nullptr;
    }
    for (auto ci : classesInfo) {
        if (ci.second.initCallback) {
            delete ci.second.initCallback;
        }
        for (auto callback : ci.second.callbacks) {
            delete callback.second;
        }
        ci.second.callbacks.clear();
    }
    classesInfo.clear();
    nextId = 0;
    allocated = 0;
}

unsigned int DynamicMetaObjects::finalizeBuild(DynamicMetaObjectBuilder &builder)
{
    if (nextId >= allocated) {
        allocated *= 2;
        metaObjects = (QMetaObject **) realloc(metaObjects, sizeof(QMetaObject *) * allocated);
    }
    unsigned int currentId = nextId;
    nextId++;

    metaObjects[currentId] = builder.toMetaObject(currentId);

    auto initFnc = builder.getInitCallback();
    if (initFnc) {
        classesInfo[currentId].initCallback =
                new CallInfo({
                                 {qMetaTypeId<DynamicQObject>()},
                                 -1,
                                 initFnc
                             });
    } else {
        classesInfo[currentId].initCallback = nullptr;
    }
    classesInfo[currentId].callbacks.clear();
    for (auto it : builder.getCallbacks()) {

        int methodID = metaObjects[currentId]->indexOfMethod( builder.methodSignature(it.first) );
        assert(methodID >= 0);

        classesInfo[currentId].callbacks[it.first] =
                new CallInfo({
                                 QVector<int>({qMetaTypeId<DynamicQObject>()}) << metaMethodParamTypeIds( metaObjects[currentId]->method(methodID) ),
                                 -1,
                                 it.second
                             });
    }

    return currentId;
}

QMetaObject *DynamicMetaObjects::getMetaObject(unsigned int id) 
{
    if (id >= nextId) {
        return nullptr;
    }
    return metaObjects[id];
}

DynamicQObject *DynamicMetaObjects::construct(unsigned int id, QObject *parent)
{
    DynamicQObject *ret = new DynamicQObject(parent);
    ret->__setClassIdx(id);
    return ret;
}

void DynamicMetaObjects::callInit(size_t classIdx, DynamicQObject *obj)
{
    if (classesInfo[classIdx].initCallback) {
        void **data = new void*[2];
        data[0] = 0;
        data[1] = obj;
        classesInfo[classIdx].initCallback->invoke(data);
        delete [] data;
    }
}

void DynamicMetaObjects::metacall(size_t classIdx, DynamicQObject *obj, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        assert(classesInfo[classIdx].callbacks.find(_id) != classesInfo[classIdx].callbacks.end());
        int paramCnt = classesInfo[classIdx].callbacks[_id]->parameterTypeIds.count();
        void **data = nullptr;

        data = new void*[paramCnt+2];
        data[0] = _a[0];
        data[1] = obj;
        for (int i = 0; i < paramCnt; i++) {
            data[i+2] = _a[i+1];
        }
        AutoCallback paramDeleter(
            [&](){
                delete [] data;
            }
        );
        Q_UNUSED(paramDeleter);

        classesInfo[classIdx].callbacks[_id]->invoke(data);
    } else if (_c == QMetaObject::IndexOfMethod) {
        throw std::runtime_error("IndexOfMethod support is not implemented for DynamicQObject");
    }
}


DynamicMetaObjects &dynamicMetaObjects()
{
    static DynamicMetaObjects _dynamicMetaObjects;
    return _dynamicMetaObjects;
}





}

#include "qtQml_cpgf_compat.h"

namespace qtjs_binder {

cpgf::GDefineMetaInfo createDynamicObjectsMetaClasses()
{
    using namespace cpgf;

    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    {
        GDefineMetaClass<DynamicMetaObjectBuilder> _nd = GDefineMetaClass<DynamicMetaObjectBuilder>::declare("DynamicMetaObjectBuilder");
        _nd._method("setClassName", &DynamicMetaObjectBuilder::setClassName);
        _nd._method("setInit", &DynamicMetaObjectBuilder::setInit);
        _nd._method("addSignal", &DynamicMetaObjectBuilder::addSignal);
        _nd._method("addSlot", &DynamicMetaObjectBuilder::addSlot);
        _nd._method("addProperty", &DynamicMetaObjectBuilder::addProperty);

        _d._class(_nd);
    }
    {
        GDefineMetaClass<DynamicMetaObjects> _nd = GDefineMetaClass<DynamicMetaObjects>::declare("DynamicMetaObjects");
        _nd._method("finalizeBuild", &DynamicMetaObjects::finalizeBuild);
        _nd._method("getMetaObject", &DynamicMetaObjects::getMetaObject);
        _nd._method("construct", &DynamicMetaObjects::construct, cpgf::MakePolicy<cpgf::GMetaRuleTransferOwnership<-1> >())
            ._default(copyVariantFromCopyable(0));

        _d._class(_nd);
    }
    {
        GDefineMetaClass<DynamicQObject, QObject> _nd = GDefineMetaClass<DynamicQObject, QObject>::declare("DynamicQObject");
        _d._class(_nd);
    }

    return _d.getMetaInfo();
}

}

