/*
  cpgf Library
  Copyright (C) 2011 - 2013 Wang Qi http://www.cpgf.org/
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


#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4996)
#endif

#include "testcase.h"

#include "../ui/sprite.h"
#include "../easeinfo.h"

#include "cpgf/tween/gtweenlist.h"
#include "cpgf/accessor/gaccessor.h"

#if defined(_WIN32)
    #include <windows.h>
#endif
#include <GL/gl.h>

using namespace cpgf;

class TestCaseAnimation : public TestCase
{
public:
	TestCaseAnimation();

	virtual std::string getDescription();
	virtual void render(int viewWidth, int viewHeight);

protected:
	virtual void doReset();

private:
	Sprite sprite;
	Sprite target;
};

const int startX = 150;
const int endX = SpriteBoardSize - startX;
const int startY = endX;
const int endY = startX;

TestCasePtr createTestCaseAnimation()
{
	return TestCasePtr(new TestCaseAnimation);
}

TestCaseAnimation::TestCaseAnimation()
{
}

std::string TestCaseAnimation::getDescription()
{
	return "Play tweening animation with fixed target.\n"
		"The ease and tween parameters can be changed in the left panel."
	;
}

void TestCaseAnimation::render(int viewWidth, int viewHeight)
{
    glEnable(GL_LIGHTING);

	this->sprite.render(viewWidth, viewHeight);
	this->target.render(viewWidth, viewHeight);
}

void TestCaseAnimation::doReset()
{
	this->sprite.setX(startX);
	this->sprite.setY(startY);
	this->sprite.setZ(0);
	this->sprite.setAlpha(1.0f);
	this->sprite.setSize(60);
	this->sprite.setColor(0x7777ff);
	this->sprite.setRotate(0);

	this->target.setX(endX);
	this->target.setY(endY);
	this->target.setZ(0);
	this->target.setAlpha(0.1f);
	this->target.setSize(this->sprite.getSize());
	this->target.setColor(0x7777ff);

	GTween & tween = GTweenList::getInstance()->tween()
		.target(createAccessor(&this->sprite, &Sprite::getX, &Sprite::setX), endX)
		.target(createAccessor(&this->sprite, &Sprite::getY, &Sprite::setY), endY)
		.target(createAccessor(&this->sprite, &Sprite::getRotate, &Sprite::setRotate), 360)
	;

	this->setTweenable(&tween);
}

