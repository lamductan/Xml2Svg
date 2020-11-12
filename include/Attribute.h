#pragma once
#include "stdafx.h"

class Attribute
{
public:
	virtual const char* getAttrName() = 0;
	virtual void setValue(char*) = 0;
	virtual ~Attribute();
};