#include "stdafx.h"
#include "Path.h"
#include "General.h"
#include "Line.h"

//myPath
myPath::myPath() : FillFigure() { init(); addSample(this); }
myPath::myPath(myPath* p) : FillFigure(p)
{
	this->m_Path = p->m_Path;
	this->m_firstPointX = p->m_firstPointX;
	this->m_firstPointY = p->m_firstPointY;
	this->m_lastPointX = p->m_lastPointX;
	this->m_lastPointY = p->m_lastPointY;
}

void myPath::init() 
{ 
	this->m_Path.clear(); 
	this->m_vectorPoints.clear();
	this->m_firstPointX = this->m_firstPointY 
		= this->m_lastPointX = this->m_lastPointY = 0.0f;
}

vector<pair<char, vector<float>>>& myPath::getPath() { return this->m_Path; }
void myPath::setPath(vector<pair<char, vector<float>>>& path) { this->m_Path = path; }

void myPath::setPath(char* charPath)
{
	char* tmp = new char[strlen(charPath) + 3];
	strcpy(tmp, charPath);
	strcat(tmp, " A");
	char* token = strtok(tmp, DELIMITER);
	if (token[0] != 'M')
		return;
	else
	{
		pair<char, vector<float>> a;
		a.first = token[0];
		if (token != NULL) a.second.push_back(atof(token + 1));
		else return;

		while (token != NULL)
		{
			token = strtok(NULL, DELIMITER);
			if (token != NULL)
			{
				if (isNewCommand(token))
				{
					this->m_Path.push_back(a);
					a.second.clear();
					a.first = token[0];
					a.second.push_back(atof(token + 1));
				}
				else
				{
					a.second.push_back(atof(token));
				}
			}
		}
	}

	this->setFirstPoint(this->m_Path[0].second[0], this->m_Path[0].second[1]);

	delete[] tmp;
}

void myPath::draw(CImg<unsigned char>& img)
{
	for (int i = 0; i < this->m_Path.size(); ++i)
	{
		if (this->m_Path[i].first == 'M')
			this->moveTo(this->m_Path[i].second[0], this->m_Path[i].second[1]);
		else if (this->m_Path[i].first == 'L')
			this->drawL(this->m_Path[i].second, img);
		else if (this->m_Path[i].first == 'H')
			this->drawH(this->m_Path[i].second, img);
		else if (this->m_Path[i].first == 'V')
			this->drawV(this->m_Path[i].second, img);
		else if (this->m_Path[i].first == 'C')
			this->drawC(this->m_Path[i].second, img);
		else if (this->m_Path[i].first == 'Z')
			this->drawZ(img);
	}
	this->m_vectorPoints.clear();
}

void myPath::draw(HDC& hdc)
{
	for (int i = 0; i < this->m_Path.size(); ++i)
	{
		if (this->m_Path[i].first == 'M')
			this->moveTo(this->m_Path[i].second[0], this->m_Path[i].second[1]);
		else if (this->m_Path[i].first == 'L')
			this->drawL(this->m_Path[i].second, hdc);
		else if (this->m_Path[i].first == 'H')
			this->drawH(this->m_Path[i].second, hdc);
		else if (this->m_Path[i].first == 'V')
			this->drawV(this->m_Path[i].second, hdc);
		else if (this->m_Path[i].first == 'C')
			this->drawC(this->m_Path[i].second, hdc);
		else if (this->m_Path[i].first == 'Z')
			this->drawZ(hdc);
	}
	this->fillPath(hdc);
}

void myPath::setFirstPoint(float x, float y)
{
	this->m_firstPointX = x;
	this->m_firstPointY = y;
}

myPoint myPath::getFirstPoint()
{
	myPoint firstPoint(this->m_firstPointX, this->m_firstPointY);
	return firstPoint;
}

void myPath::setLastPoint(float x, float y)
{
	this->m_lastPointX = x;
	this->m_lastPointY = y;
}

myPoint myPath::getLastPoint()
{
	myPoint lastPoint(this->m_lastPointX, this->m_lastPointY);
	return lastPoint;
}

void myPath::addPoint(float x, float y)
{
	PointF aPoint(x, y);
	this->m_vectorPoints.push_back(aPoint);
}

void myPath::moveTo(float x, float y)
{
	this->setLastPoint(x, y);
	this->addPoint(x, y);
}

void myPath::drawL(vector<float>& v, CImg<unsigned char>& img)
{
	myLine* tmpLine = new myLine(dynamic_cast<Figure*>(this));
	for (int i = 0; i < v.size(); i += 2)
	{
		myPoint secondPoint(v[i], v[i + 1]);
		tmpLine->setPoints(this->getLastPoint(), secondPoint);
		tmpLine->draw(img);
		this->addPoint(secondPoint.x, secondPoint.y);
		this->setLastPoint(v[i], v[i + 1]);
	}
	delete tmpLine;
}

void myPath::drawH(vector<float>& v, CImg<unsigned char>& img)
{
	myLine* tmpLine = new myLine(dynamic_cast<Figure*>(this));
	myPoint secondPoint;
	secondPoint.y = this->getLastPoint().y;
	for (int i = 0; i < v.size(); ++i)
	{
		secondPoint.x = v[i];
		tmpLine->setPoints(this->getLastPoint(), secondPoint);
		tmpLine->draw(img);
		this->addPoint(secondPoint.x, secondPoint.y);
		this->setLastPoint(secondPoint.x, secondPoint.y);
	}
	delete tmpLine;
}

void myPath::drawV(vector<float>& v, CImg<unsigned char>& img)
{
	myLine* tmpLine = new myLine(dynamic_cast<Figure*>(this));
	myPoint secondPoint;
	secondPoint.x = this->getLastPoint().x;
	for (int i = 0; i < v.size(); ++i)
	{
		secondPoint.y = v[i];
		tmpLine->setPoints(this->getLastPoint(), secondPoint);
		tmpLine->draw(img);
		this->addPoint(secondPoint.x, secondPoint.y);
		this->setLastPoint(secondPoint.x, secondPoint.y);
	}
	delete tmpLine;
}

void myPath::drawZ(CImg<unsigned char>& img)
{
	myLine* tmpLine = new myLine(dynamic_cast<Figure*>(this));
	tmpLine->setPoints(this->getLastPoint(), this->getFirstPoint());
	tmpLine->draw(img);
	this->setLastPoint(this->getFirstPoint().x, this->getFirstPoint().y);
	delete tmpLine;
}

void myPath::drawC(vector<float>& v, CImg<unsigned char>& img)
{
	unsigned char color[3];
	convert_RGB_to_unsigned_char(color, this->getStroke());
	myPoint firstPoint = this->getLastPoint();
	vector<myPoint> t;
	t.push_back(firstPoint);
	for (int i = 0; i < v.size(); i +=2)
	{
		myPoint tmp(v[i], v[i + 1]);
		this->addPoint(tmp.x, tmp.y);
		t.push_back(tmp);
	}
	for (int i = 0; i < t.size(); ++i)
		t[i] = t[i].transform(this->getTransform());

	for (int i = 0; i < this->getStrokeWidth(); ++i)
	{
		img.draw_spline(t[0].x + i, t[0].y + i,	t[1].x - t[0].x, t[1].y - t[0].y,
			t[3].x + i, t[3].y + i, t[3].x - t[2].x, t[3].y - t[2].y,
			color, this->getStrokeOpacity());
	}
	this->setLastPoint(v[4], v[5]);
}

void myPath::drawL(vector<float>& v, HDC& hdc)
{
	myLine* tmpLine = new myLine(dynamic_cast<Figure*>(this));
	for (int i = 0; i < v.size(); i += 2)
	{
		myPoint secondPoint(v[i], v[i + 1]);
		tmpLine->setPoints(this->getLastPoint(), secondPoint);
		tmpLine->draw(hdc);
		this->addPoint(secondPoint.x, secondPoint.y);
		this->setLastPoint(v[i], v[i + 1]);
	}
	delete tmpLine;
}

void myPath::drawH(vector<float>& v, HDC& hdc)
{
	myLine* tmpLine = new myLine(dynamic_cast<Figure*>(this));
	myPoint secondPoint;
	secondPoint.y = this->getLastPoint().y;
	for (int i = 0; i < v.size(); ++i)
	{
		secondPoint.x = v[i];
		tmpLine->setPoints(this->getLastPoint(), secondPoint);
		tmpLine->draw(hdc);
		this->addPoint(secondPoint.x, secondPoint.y);
		this->setLastPoint(secondPoint.x, secondPoint.y);
	}
	delete tmpLine;
}

void myPath::drawV(vector<float>& v, HDC& hdc)
{
	myLine* tmpLine = new myLine(dynamic_cast<Figure*>(this));
	myPoint secondPoint;
	secondPoint.x = this->getLastPoint().x;
	for (int i = 0; i < v.size(); ++i)
	{
		secondPoint.y = v[i];
		tmpLine->setPoints(this->getLastPoint(), secondPoint);
		tmpLine->draw(hdc);
		this->addPoint(secondPoint.x, secondPoint.y);
		this->setLastPoint(secondPoint.x, secondPoint.y);
	}
	delete tmpLine;
}

void myPath::drawZ(HDC& hdc)
{
	myLine* tmpLine = new myLine(dynamic_cast<Figure*>(this));
	tmpLine->setPoints(this->getLastPoint(), this->getFirstPoint());
	tmpLine->draw(hdc);
	this->setLastPoint(this->getFirstPoint().x, this->getFirstPoint().y);
	delete tmpLine;
}

void myPath::drawC(vector<float>& v, HDC& hdc)
{
	Graphics graphics(hdc);
	Pen pen(Color(BYTE(this->getStrokeOpacity() * 255), this->getStroke().red, this->getStroke().green, this->getStroke().blue), this->getStrokeWidth());

	Matrix* rTransMatrix = dynamic_cast<ListTransform*>(this->m_attributes["transform"])->getReverseMatrix();
	Matrix* transMatrix = dynamic_cast<ListTransform*>(this->m_attributes["transform"])->getMatrix();

	graphics.SetTransform(transMatrix);
	graphics.DrawBezier(&pen, this->getLastPoint().x, this->getLastPoint().y, v[0], v[1], v[2], v[3], v[4], v[5]);
	this->setLastPoint(v[4], v[5]);

	for (int i = 0; i < 6; i += 2)
	{
		this->addPoint(v[i], v[i + 1]);
	}

	graphics.SetTransform(rTransMatrix);
	delete rTransMatrix;
	delete transMatrix;
}

void myPath::fillPath(HDC& hdc)
{
	Graphics graphics(hdc);
	SolidBrush solidBrush(Color(BYTE(this->getFillOpacity() * 255), this->getFill().red, this->getFill().green, this->getFill().blue));
	Matrix* rTransMatrix = dynamic_cast<ListTransform*>(this->m_attributes["transform"])->getReverseMatrix();
	Matrix* transMatrix = dynamic_cast<ListTransform*>(this->m_attributes["transform"])->getMatrix();
	graphics.SetTransform(transMatrix);
	graphics.FillClosedCurve(&solidBrush, &this->m_vectorPoints[0], this->m_vectorPoints.size());
	graphics.SetTransform(rTransMatrix);
	delete rTransMatrix;
	delete transMatrix;
	this->m_vectorPoints.clear();
}

Figure* myPath::clone() { return new myPath(this); }
char* myPath::className() { return "path"; }
void myPath::setAttribute(char* attr_name, char* attr_value)
{
	map<char*, Attribute*>::iterator it1;

	it1 = this->m_attributes.find(attr_name);
	if (it1 != this->m_attributes.end())
	{
		it1->second->setValue(attr_value);
	}
	else
	{
		this->setPath(attr_value);
	}
}

void myPath::setByNode(xml_node<>* node)
{
	for (xml_attribute<> *attr = node->first_attribute();
		attr; attr = attr->next_attribute())
	{
		this->setAttribute(attr->name(), attr->value());
	}
}

void myPath::setByNodeAndAddTransform(xml_node<>* node)
{
	for (xml_attribute<> *attr = node->first_attribute();
		attr; attr = attr->next_attribute())
	{
		if (strcmp(attr->name(), "transform") != 0)
			this->setAttribute(attr->name(), attr->value());
		else
		{
			Figure* pFig = Figure::createObject("line");
			pFig->setAttribute(attr->name(), attr->value());
			this->addTransform(pFig->getTransform());
			delete pFig;
		}
	}
}

myPath::~myPath() { this->m_Path.clear(); }