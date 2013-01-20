/*
  cpgf Library
  Copyright (C) 2011, 2012 Wang Qi http://www.cpgf.org/
  All rights reserved.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/


#ifndef __GMETAARCHIVECOMMONIMPL_H
#define __GMETAARCHIVECOMMONIMPL_H


#include "cpgf/serialization/gmetaarchivecommon.h"

#include "cpgf/gflags.h"
#include "cpgf/gmetaapi.h"
#include "cpgf/gexception.h"

#include "cpgf/gstringmap.h"


#include <stack>


namespace cpgf {


const char * const nameRootNode = "cpgf";
const char * const nameDataNode = "data";
const char * const nameClassTypesNode = "classtypes";

const char * const nameType = "type";
const char * const nameVersion = "version";
const char * const nameArchiveID = "aid";
const char * const nameClassTypeID = "cid";
const char * const nameLength = "len";
const char * const prefixClassType = "c";

const char * const nameReferenceID = "rid";
const char * const nameObject = "object";
const char * const nameString = "string";
const char * const nameArray = "array";
const char * const nameNull = "null";



class GBaseClassMap
{
private:
	typedef GStringMap<void *, GStringMapReuseKey> MapType;

public:
	bool hasMetaClass(void * instance, IMetaClass * metaClass) const;
	void addMetaClass(void * instance, IMetaClass * metaClass);

private:
	MapType itemMap;
};


class GMetaArchiveConfigMap
{
private:
	typedef GStringMap<GMetaArchiveConfig, GStringMapReuseKey> MapType;

public:
	GMetaArchiveConfig getConfig(IMetaClass * metaClass) const;

private:
	mutable MapType itemMap;
};


class GClassSerializeHeader
{
private:
	typedef std::stack<bool> SType;
	
public:
	void beginSerialize() {
		this->headerStack.push(false);
	}
	
	void endSerialize() {
		this->headerStack.pop();
	}
	
	bool needBegin() const {
		return (! this->headerStack.empty()) && ! this->headerStack.top();
	}
	
	bool needEnd() const {
		return ! this->needBegin();
	}
	
	void addedHeader() {
		if(this->needBegin()) {
			this->headerStack.pop();
			this->headerStack.push(true);
		}
	}
	
private:
	SType headerStack;
	
private:
	friend class GClassSerializeHeaderGuard;	
};


class GClassSerializeHeaderGuard
{
public:
	explicit GClassSerializeHeaderGuard(GClassSerializeHeader * header)
		: header(header)
	{
		this->header->beginSerialize();
	}
	
	~GClassSerializeHeaderGuard()
	{
		this->header->endSerialize();
	}
	
private:
	GClassSerializeHeader * header;	
};


bool canSerializeItem(const GMetaArchiveConfig & config, IMetaItem * item);
bool canSerializeObject(const GMetaArchiveConfig & config, IMetaClass * metaClass);
bool canSerializeField(const GMetaArchiveConfig & config, IMetaAccessible * accessible, IMetaService * service);
bool canSerializeBaseClass(const GMetaArchiveConfig & config, IMetaClass * baseClass, IMetaClass * metaClass);



} // namespace cpgf


#endif
