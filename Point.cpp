#include "stdafx.h"
#include "Point.h"

//myPoint
myPoint::myPoint(int x, int y)
{
	this->x = x;
	this->y = y;
}

myPoint::myPoint(const myPoint& p)
{
	this->x = p.x;
	this->y = p.y;
}

myPoint& myPoint::operator=(int value)
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

myPoint myPoint::translate(myPoint vectorTranslate)
{
	myPoint translatemyPoint;
	translatemyPoint.x = this->x + vectorTranslate.x;
	translatemyPoint.y = this->y + vectorTranslate.y;
	return translatemyPoint;
}

myPoint myPoint::translate(int x, int y)
{
	myPoint translatemyPoint;
	translatemyPoint.x = this->x + x;
	translatemyPoint.y = this->y + y;
	return translatemyPoint;
}

myPoint myPoint::rotate(int angle)
{
	myPoint rotatePoint;
	double theta = acos(-1) / 180 * angle;
	rotatePoint.x = floor(cos(theta)*this->x - sin(theta)*this->y);
	rotatePoint.y = floor(cos(theta)*this->y + sin(theta)*this->x);
	return rotatePoint;
}

myPoint myPoint::transform(const vector<myPoint>& translate, const vector<char>& rotate, const vector<char>& transformOrder)
{
	myPoint transformPoint = *this;
	int j = 0, k = 0;
	for (int i = 0; i < transformOrder.size(); ++i)
	{
		if (transformOrder[i] == 0)
		{
			transformPoint = transformPoint.translate(translate[j++]);
		}
		else transformPoint = transformPoint.rotate(rotate[k++]);
	}
	return transformPoint;
}

myPoint::~myPoint() {}