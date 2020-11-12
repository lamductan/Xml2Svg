#pragma once
#include "stdafx.h"

class Transform;

class myPoint
{
public:
	float x;
	float y;
	myPoint(float x = 0.0f, float y = 0.0f);
	myPoint(const myPoint&);
	virtual ~myPoint();
	myPoint& operator=(float);
	myPoint& operator=(const myPoint&);
	float calcDistance(const myPoint&);

	myPoint translate(myPoint);
	myPoint translate(float, float);
	myPoint rotate(float, float, float);
	myPoint transform(const vector<Transform*>&);
};
