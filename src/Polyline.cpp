#include "stdafx.h"
#include "Polyline.h"
#include "General.h"

//myPolyline
myPolyline::myPolyline() : FillFigure() { addSample(this); }

myPolyline::myPolyline(myPolyline* p) : FillFigure(p)
{
	this->m_pointData = p->m_pointData;
}

myPolyline::myPolyline(xml_node<>* node)
{
	FillFigure::init();
	init();

	for (xml_attribute<> *attr = node->first_attribute();
		attr; attr = attr->next_attribute())
	{
		this->setAttribute(attr->name(), attr->value());
	}
}

void myPolyline::setPointsData(const vector<myPoint>& vectorPoint)
{
	this->m_pointData.clear();
	for (int i = 0; i < vectorPoint.size(); ++i)
		this->m_pointData.push_back(vectorPoint[i]);
}

void myPolyline::setPointsData(char* charPoints)
{
	this->m_pointData.clear();
	char* tmp = new char[strlen(charPoints) + 1];
	strcpy(tmp, charPoints);

	myPoint newPoint;
	float x[2];

	char* token = strtok(tmp, DELIMITER);
	x[0] = atof(token);
	token = strtok(NULL, DELIMITER);
	x[1] = atof(token);
	newPoint.x = x[0];
	newPoint.y = x[1];
	this->m_pointData.push_back(newPoint);

	while (token != NULL)
	{
		for (int i = 0; i < 2; ++i)
		{
			token = strtok(NULL, DELIMITER);
			if (token != NULL)
				x[i] = atof(token);
		}
		newPoint.x = x[0];
		newPoint.y = x[1];
		this->m_pointData.push_back(newPoint);
	}

	delete[] tmp;
}

void myPolyline::draw(CImg<unsigned char>& img)
{
	CImg<float> myPoints(this->m_pointData.size(), 2);
	myPoint tmp;
	cimg_forX(myPoints, i)
	{
		tmp = this->m_pointData[i].transform(this->getTransform());
		myPoints(i, 0) = tmp.x;
		myPoints(i, 1) = tmp.y;
	}
	unsigned char fillColor[3];
	convert_RGB_to_unsigned_char(fillColor, this->getFill());
	img.draw_polygon(myPoints, fillColor, this->getFillOpacity());

	myLine* tmpLine = new myLine;
	tmpLine->setTransform(this->getTransform());
	tmpLine->setStroke(this->getStroke());
	tmpLine->setStrokeOpacity(this->getStrokeOpacity());
	tmpLine->setStrokeWidth(this->getStrokeWidth());

	for (int i = 0; i < this->m_pointData.size() - 1; ++i)
	{
		tmpLine->setPoints(this->m_pointData[i], this->m_pointData[i + 1]);
		tmpLine->draw(img);
	}
	delete tmpLine;
}

void myPolyline::draw(HDC& hdc)
{
	Graphics graphics(hdc);
	Pen pen(Color(BYTE(this->getStrokeOpacity() * 255), this->getStroke().red, this->getStroke().green, this->getStroke().blue), this->getStrokeWidth());

	PointF* points = new PointF[this->m_pointData.size()];
	myPoint tmp;
	for (int i = 0; i < this->m_pointData.size(); ++i)
	{
		tmp = this->m_pointData[i].transform(this->getTransform());
		points[i].X = tmp.x;
		points[i].Y = tmp.y;
	}
	
	SolidBrush solidBrush(Color(BYTE(this->getFillOpacity() * 255), this->getFill().red, this->getFill().green, this->getFill().blue));
	graphics.FillPolygon(&solidBrush, points, this->m_pointData.size());
	if (this->getStrokeWidth() != 0.0f)	
		graphics.DrawLines(&pen, points, this->m_pointData.size());
	delete[] points;
}

void myPolyline::setAttribute(char* attr_name, char* attr_value)
{
	map<char*, Attribute*>::iterator it1;

	it1 = this->m_attributes.find(attr_name);
	if (it1 != this->m_attributes.end())
	{
		it1->second->setValue(attr_value);
	}
	else
	{
		this->setPointsData(attr_value);
	}
}

void myPolyline::setByNode(xml_node<>* node)
{
	for (xml_attribute<> *attr = node->first_attribute();
		attr; attr = attr->next_attribute())
	{
		this->setAttribute(attr->name(), attr->value());
	}
}

void myPolyline::setByNodeAndAddTransform(xml_node<>* node)
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

char* myPolyline::className() { return "polyline"; }

Figure* myPolyline::clone() { return new myPolyline(this); }

myPolyline::~myPolyline() {}

ostream& operator<<(ostream& out, const myPolyline& p)
{
	out << "Point-data: ";
	for (int i = 0; i < p.m_pointData.size(); ++i)
		out << "(" << p.m_pointData[i].x << ", " << p.m_pointData[i].y << ") ";
	out << endl;
	return out;
}