#include "stdafx.h"
#include "Point.h"
#include "Transformer.h"

//myPoint
myPoint::myPoint(float x, float y)
{
	this->x = x;
	this->y = y;
}

myPoint::myPoint(const myPoint& p)
{
	this->x = p.x;
	this->y = p.y;
}

myPoint& myPoint::operator=(float value)
{
	this->x = this->y = value;
	return *this;
}

myPoint& myPoint::operator=(const myPoint& p)
{
	this->x = p.x;
	this->y = p.y;
	return *this;
}

float myPoint::calcDistance(const myPoint& p)
{
	return sqrt(pow((this->x - p.x), 2.0) + pow((this->y - p.y), 2.0));
}

myPoint myPoint::translate(myPoint vectorTranslate)
{
	myPoint translatemyPoint;
	translatemyPoint.x = this->x + vectorTranslate.x;
	translatemyPoint.y = this->y + vectorTranslate.y;
	return translatemyPoint;
}

myPoint myPoint::translate(float x, float y)
{
	myPoint translatemyPoint;
	translatemyPoint.x = this->x + x;
	translatemyPoint.y = this->y + y;
	return translatemyPoint;
}

myPoint myPoint::rotate(float angle, float x, float y)
{
	myPoint rotatePoint;

	rotatePoint.translate(-x, -y);
	
	double theta = acos(-1) / 180 * angle;
	rotatePoint.x = cos(theta)*this->x - sin(theta)*this->y;
	rotatePoint.y = cos(theta)*this->y + sin(theta)*this->x;

	rotatePoint.translate(x, y);
	return rotatePoint;
}

myPoint myPoint::transform(const vector<Transform*>& list)
{
	myPoint transformPoint = *this;
	for (int i = 0; i < list.size(); ++i)
	{
		transformPoint = list[i]->transform(transformPoint);
	}
	return transformPoint;
}

myPoint::~myPoint() {}