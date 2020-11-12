#include "stdafx.h"
#include "Polygon.h"
#include "General.h"

//myPolygon
myPolygon::myPolygon() : myPolyline() { addSample(this); }

myPolygon::myPolygon(myPolygon* p) : myPolyline(p) {}

myPolygon::myPolygon(xml_node<>* node): myPolyline(node) {}

void myPolygon::setPointsData(const vector<myPoint>& v) { myPolyline::setPointsData(v); }

void myPolygon::setPointsData(char* cPoints) { myPolyline::setPointsData(cPoints); }

void myPolygon::draw(CImg<unsigned char>& img)
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
	tmpLine->setPoints(this->m_pointData.back(), this->m_pointData[0]);
	tmpLine->draw(img);
	delete tmpLine;
}

void myPolygon::draw(HDC& hdc)
{
	Graphics graphics(hdc);
	Pen pen(Color(BYTE(this->getStrokeOpacity() * 255), this->getStroke().red, this->getStroke().green, this->getStroke().blue), this->getStrokeWidth());

	PointF* points = new PointF[this->m_pointData.size()];
	for (int i = 0; i < this->m_pointData.size(); ++i)
	{
		points[i].X = this->m_pointData[i].x;
		points[i].Y = this->m_pointData[i].y;
	}
	Matrix* rTransMatrix = dynamic_cast<ListTransform*>(this->m_attributes["transform"])->getReverseMatrix();
	Matrix* transMatrix = dynamic_cast<ListTransform*>(this->m_attributes["transform"])->getMatrix();

	graphics.SetTransform(transMatrix);
	
	SolidBrush solidBrush(Color(BYTE(this->getFillOpacity() * 255), this->getFill().red, this->getFill().green, this->getFill().blue));
	graphics.FillPolygon(&solidBrush, points, this->m_pointData.size());
	if (this->getStrokeWidth() != 0.0f)
		graphics.DrawPolygon(&pen, points, this->m_pointData.size());
	graphics.SetTransform(rTransMatrix);

	delete rTransMatrix;
	delete transMatrix;
	delete[] points;
}

char* myPolygon::className() { return "polygon"; }

Figure* myPolygon::clone() { return new myPolygon(this); }

myPolygon::~myPolygon() {}