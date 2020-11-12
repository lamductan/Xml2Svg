#include "stdafx.h"
#include "Transformer.h"
#include "RGB.h"
#include "General.h"

//Transform
Transform::~Transform() {}

//Translate
Translate::Translate(float x, float y) { this->m_x = x, this->m_y = y; }
Translate::Translate(Translate& p) { this->m_x = p.m_x, this->m_y = p.m_y; }
Translate::Translate(char* charTranslate)
{
	this->m_x = this->m_y = 0;
	this->setValue(charTranslate);
}

myPoint Translate::getValue()  
{
	myPoint translate(this->m_x, this->m_y);
	return translate;
}

void Translate::setValue(char* charTranslate)
{
	char* tmp = new char[strlen(charTranslate) + 1];
	strcpy(tmp, charTranslate);
	char* token = strtok(tmp, DELIMITER);
	
	float x[2] = { 0.0f, 0.0f };
	for (int i = 0; i < 2; ++i)
	{
		token = strtok(NULL, DELIMITER);
		if (token != NULL)
			x[i] = atof(token);
		else break;
	}

	this->m_x = x[0];
	this->m_y = x[1];
	delete[]tmp;
}

Matrix* Translate::getMatrix()  
{
	Matrix* translateMatrix = new Matrix;
	translateMatrix->Translate(this->m_x, this->m_y);
	return translateMatrix;
}

Matrix* Translate::getReverseMatrix()  
{
	Matrix* rtranslateMatrix = new Matrix;
	rtranslateMatrix->Translate(-this->m_x, -this->m_y);
	return rtranslateMatrix;
}

Transform* Translate::clone() { return new Translate(*this); }

myPoint Translate::transform(  myPoint& p)  
{
	myPoint translatePoint;
	translatePoint.x = p.x + this->m_x;
	translatePoint.y = p.y + this->m_y;
	return translatePoint;
}

const char* Translate::getTransformName() { return "translate"; }

string Translate::getTransformCode()
{
	string Code;
	if (this->m_x != 0 || this->m_y != 0)
	{
		ostringstream buffer;
		Code += "translate(";
		buffer << this->m_x;
		Code += buffer.str();
		buffer.str("");
		Code += ",";
		buffer << this->m_y;
		Code += buffer.str();
		buffer.str("");
		Code += ") ";
	}
	return Code;
}

Translate::~Translate() {}

//Rotate
Rotate::Rotate(float angle, float x, float y)
{
	this->m_angle = angle;
	this->m_x = x;
	this->m_y = y;
}

Rotate::Rotate(Rotate& p)
{
	this->m_angle = p.m_angle;
	this->m_x = p.m_x;
	this->m_y = p.m_y;
}

Rotate::Rotate(char* charRotate)
{
	this->m_angle = this->m_x = this->m_y = 0;
	this->setValue(charRotate);
}

float Rotate::getAngle() { return this->m_angle; }

myPoint Rotate::getRotateCenter()  
{
	myPoint rotateCenter(this->m_x, this->m_y);
	return rotateCenter;
}

void Rotate::setValue(char* charRotate)
{
	char* tmp = new char[strlen(charRotate) + 1];
	strcpy(tmp, charRotate);
	char* token = strtok(tmp, DELIMITER);

	float x[3] = { 0.0f, 0.0f, 0.0f };
	for (int i = 0; i < 3; ++i)
	{
		token = strtok(NULL, DELIMITER);
		if (token != NULL)
			x[i] = atof(token);
		else break;
	}

	this->m_angle = x[0];
	this->m_x = x[1];
	this->m_y = x[2];
	delete[]tmp;
}

Matrix* Rotate::getMatrix()  
{
	Matrix* rotate = new Matrix;
	PointF rotateCenter(this->m_x, this->m_y);
	rotate->RotateAt(this->m_angle, rotateCenter);
	return rotate;
}

Matrix* Rotate::getReverseMatrix()  
{
	Matrix* rotate = new Matrix;
	PointF rotateCenter(this->m_x, this->m_y);
	rotate->RotateAt(-this->m_angle, rotateCenter);
	return rotate;	
}

myPoint Rotate::transform(myPoint& p)  
{
	myPoint translatePoint, rotatePoint;
	translatePoint = p.translate(this->m_x, this->m_y);

	double theta = acos(-1) / 180 * this->m_angle;
	rotatePoint.x = cos(theta)*translatePoint.x - sin(theta)*translatePoint.y;
	rotatePoint.y = cos(theta)*translatePoint.y + sin(theta)*translatePoint.x;

	rotatePoint = rotatePoint.translate(-this->m_x, -this->m_y);
	return rotatePoint;
}

Transform* Rotate::clone() { return new Rotate(*this); }

const char* Rotate::getTransformName() { return "rotate"; }

string Rotate::getTransformCode()
{
	string Code;
	if (this->m_angle != 0 || this->m_x != 0 || this->m_y != 0)
	{
		ostringstream buffer;
		Code += "rotate(";
		buffer << this->m_angle;
		Code += buffer.str();
		buffer.str("");
		if (this->m_x != 0 || this->m_y != 0)
		{
			Code += ",";
			buffer << this->m_x;
			Code += buffer.str();
			Code += ",";
			buffer << this->m_y;
			Code += buffer.str();
			buffer.str("");
		}
		Code += ") ";
	}
	return Code;
}

Rotate::~Rotate() {}

//Scale
Scale::Scale(float d) { this->m_x = this->m_y = d; }
Scale::Scale(float x, float y) { this->m_x = x, this->m_y = y; }
Scale::Scale(Scale& p) { this->m_x = p.m_x, this->m_y = p.m_y; }
Scale::Scale(char* charScale)
{
	this->m_x = this->m_y = 1;
	this->setValue(charScale);
}

float Scale::getScaleX() { return this->m_x; }
float Scale::getScaleY() { return this->m_y; }
void Scale::setValue(char* charScale)
{
	char* tmp = new char[strlen(charScale) + 1];
	strcpy(tmp, charScale);
	char* token = strtok(tmp, DELIMITER);

	float x[2] = { 1.0f, -1.0f };
	for (int i = 0; i < 2; ++i)
	{
		token = strtok(NULL, DELIMITER);
		if (token != NULL)
			x[i] = atof(token);
		else break;
	}

	this->m_x = x[0];
	if (x[1] == -1.0f) 
		this->m_y = this->m_x;
	else 
		this->m_y = x[1];
	
	delete[]tmp;
}

Matrix* Scale::getMatrix()
{
	Matrix* scaleMatrix = new Matrix;
	scaleMatrix->Scale(this->m_x, this->m_y);
	return scaleMatrix;
}

Matrix* Scale::getReverseMatrix()
{
	Matrix* scaleMatrix = new Matrix;
	scaleMatrix->Scale(1.0f / this->m_x, 1.0f / this->m_y);
	return scaleMatrix;
}

Transform* Scale::clone() { return new Scale(*this); }
myPoint Scale::transform(myPoint& p)
{
	myPoint scalePoint;
	scalePoint.x = p.x * this->m_x;
	scalePoint.y = p.y * this->m_y;
	return scalePoint;
}

const char* Scale::getTransformName() { return "scale"; }

string Scale::getTransformCode()
{
	string Code;
	if (this->m_x != 0 || this->m_y != 0)
	{
		ostringstream buffer;
		Code += "scale(";
		if (this->m_x != this->m_y)
		{
			buffer << this->m_x;
			Code += buffer.str();
			Code += ",";
			buffer << this->m_y;
			Code += buffer.str();
			buffer.str("");
		}
		else
		{
			buffer << this->m_x;
			Code += buffer.str();
		}
		Code += ") ";
	}
	return Code;
}

Scale::~Scale() {}

//ListTransform
ListTransform::ListTransform() { this->m_listTransform.clear(); }

ListTransform::ListTransform(  ListTransform& p)
{
	this->setValue(p.getValue());
}

const char* ListTransform::getAttrName() { return "transform"; }

int ListTransform::getTransformSize() const { return this->m_listTransform.size(); }

const vector<Transform*>& ListTransform::getValue() const { return this->m_listTransform; }

void ListTransform::setValue(const vector<Transform*>& p)
{
	for (int i = 0; i < this->m_listTransform.size(); ++i)
		delete this->m_listTransform[i];
	this->m_listTransform.clear();
	for (int i = 0; i < p.size(); ++i)
		this->m_listTransform.push_back(p[i]->clone());
}

void ListTransform::addValue(const vector<Transform*>& p)
{
	vector<Transform*> newVectorTransform;
	for (int i = 0; i < p.size(); ++i)
		newVectorTransform.push_back(p[i]->clone());
	for (int i = 0; i < this->m_listTransform.size(); ++i)
		newVectorTransform.push_back(this->m_listTransform[i]);
	this->m_listTransform = newVectorTransform;
}

void ListTransform::setValue1(char* charTransform,   char order)
{
	this->m_listTransform.clear();

	int len = strlen(charTransform);
	char* mCharTransform = new char[len + 1];
	strcpy(mCharTransform, charTransform);

	int nTransforms = 0;
	for (int i = 0; i < len; ++i)
		if (charTransform[i] == '(') ++nTransforms;

	char** cTransforms = new char*[nTransforms];
	for (int i = 0; i < nTransforms; ++i)
		cTransforms[i] = new char[30];

	char* token;
	token = strtok(mCharTransform, ")");
	if (token != NULL) strcpy(cTransforms[0], token);
	int cur = 1;
	while (token != NULL)
	{
		token = strtok(NULL, ")");
		if (token != NULL && cur < nTransforms)
			strcpy(cTransforms[cur++], token);
	}

	for (int i = 0; i < nTransforms; ++i)
	{
		if (cTransforms[i][1] == 't' || cTransforms[i][0] == 't')
		{
			this->m_listTransform.push_back(new Translate(cTransforms[i]));
		}
		else if (cTransforms[i][1] == 'r' || cTransforms[i][0] == 'r')
		{
			this->m_listTransform.push_back(new Rotate(cTransforms[i]));
		}
		else 
		{
			this->m_listTransform.push_back(new Scale(cTransforms[i]));
		}
	}

	for (int i = 0; i < nTransforms; ++i)
		delete[] cTransforms[i];
	delete[] cTransforms;
	delete[] mCharTransform;

	if (order == INVERSE_ORDER)
	{
		reverse(this->m_listTransform.begin(), this->m_listTransform.end());
	}
}

void ListTransform::setValue(char* charTransform) { return this->setValue1(charTransform, INVERSE_ORDER); }

Matrix* ListTransform::getMatrix()
{
	Matrix* transformMatrix = new Matrix(1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	for (int i = 0; i < this->m_listTransform.size(); ++i)
	{
		Matrix* tmp = this->m_listTransform[i]->getMatrix();
		transformMatrix->Multiply(tmp, MatrixOrderAppend);
		delete tmp;
	}
	return transformMatrix;
}

Matrix* ListTransform::getReverseMatrix()
{
	Matrix* transformMatrix = new Matrix(1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	for (int i = 0; i < this->m_listTransform.size(); ++i)
	{
		Matrix* tmp = this->m_listTransform[i]->getReverseMatrix();
		transformMatrix->Multiply(tmp);
		delete tmp;
	}
	return transformMatrix;
}

string ListTransform::getTransformCode()
{
	string Code = "transform=\"";
	for (int i = 0; i < this->m_listTransform.size(); ++i)
		Code += this->m_listTransform[i]->getTransformCode();
	Code += "\" ";
	return Code;
}

ListTransform::~ListTransform()
{
	for (int i = 0; i < this->m_listTransform.size(); ++i)
		delete this->m_listTransform[i];
	this->m_listTransform.clear();
}