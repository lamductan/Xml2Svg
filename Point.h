#pragma once
#include "stdafx.h"

#define TRANSLATE_FIRST 0
#define ROTATE_FIRST	1

#define TRANSLATE 0
#define ROTATE	  1

class myPoint
{
public:
	int x;
	int y;
	myPoint(int x = 0, int y = 0);
	myPoint(const myPoint&);
	virtual ~myPoint();
	myPoint& operator=(int);
	myPoint& operator=(const myPoint&);

	myPoint translate(myPoint);
	myPoint translate(int, int);
	myPoint rotate(int);
	myPoint transform(const vector<myPoint>&, const vector<char>&, const vector<char>&);
};
