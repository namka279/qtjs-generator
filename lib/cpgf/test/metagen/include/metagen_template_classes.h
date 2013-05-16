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


#ifndef __METAGEN_TEMPLATE_CLASSES_H
#define __METAGEN_TEMPLATE_CLASSES_H


template <typename T, typename U, int N>
struct TemplateClassA
{
public:
	template <typename I>
	struct TemplateClassInnerA
	{
	};

	struct Shared
	{
	};

//	void a(TemplateClassInnerA<T> *) {}
	void a(int) {}
	void b(Shared *) {}
	void b(void *) {}
};

struct TemplateBase
{
};

namespace NS1 {
namespace NS2 {

template <typename T>
struct TemplateClassB : public T
{
public:
	struct Shared
	{
	};

	void b(Shared *) {}
	void b(void *) {}
};

}
}


#endif
