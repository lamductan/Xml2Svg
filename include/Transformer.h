#pragma once
#include "stdafx.h"
#include "Point.h"
#include "Attribute.h"

#define ORDER   0
#define INVERSE_ORDER 1

class Transform
{
public:
	virtual Transform* clone() = 0;
	virtual void setValue(char*) = 0;
	virtual Matrix* getMatrix() = 0;
	virtual Matrix* getReverseMatrix() = 0;
	virtual myPoint transform( myPoint&) = 0;
	virtual const char* getTransformName() = 0;
	virtual string getTransformCode() = 0;
	virtual ~Transform();
};

class Translate :public Transform
{
protected:
	float m_x;
	float m_y;
public:
	Translate(float x = 0.0f, float y = 0.0f);
	Translate(Translate&);
	Translate(char*);
	myPoint getValue() ;
	void setValue(char*);
	Matrix* getMatrix() ;
	Matrix* getReverseMatrix() ;
	Transform* clone() ;
	myPoint transform(myPoint&) ;
	const char* getTransformName();
	string getTransformCode();
	virtual ~Translate();
};

class Rotate :public Transform
{
protected:
	float m_angle;
	float m_x;
	float m_y;
public:
	Rotate(float angle = 0.0f, float x = 0.0f, float y = 0.0f);
	Rotate(Rotate&);
	Rotate(char*);
	float getAngle() ;
	myPoint getRotateCenter();
	void setValue(char*);
	Matrix* getMatrix() ;
	Matrix* getReverseMatrix() ;
	Transform* clone() ;
	myPoint transform(myPoint&) ;
	const char* getTransformName();
	string getTransformCode();
	virtual ~Rotate();
};

class Scale : public Transform
{
protected:
	float m_x;
	float m_y;
public:
	Scale(float d);
	Scale(float x, float y);
	Scale(Scale&);
	Scale(char*);
	float getScaleX();
	float getScaleY();
	void setValue(char*);
	Matrix* getMatrix();
	Matrix* getReverseMatrix();
	Transform* clone();
	myPoint transform(myPoint&);
	const char* getTransformName();
	string getTransformCode();
	virtual ~Scale();
};

class ListTransform: public Attribute
{
protected:
	vector<Transform*> m_listTransform;
public:
	ListTransform();
	ListTransform(ListTransform&);
	const char* getAttrName();
	virtual void setValue1(char*, char order);
	virtual void setValue(char*);
	virtual void setValue(const vector<Transform*>&);
	virtual void addValue(const vector<Transform*>&);
	int getTransformSize() const;
	const vector<Transform*>& getValue() const;
	Matrix* getMatrix();
	Matrix* getReverseMatrix();
	string getTransformCode();
	virtual ~ListTransform();
};
