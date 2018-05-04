#include "stdafx.h"
#include "Polygon.h"

//myPolygon
myPolygon::myPolygon() : myPolyline() {}

myPolygon::myPolygon(const vector<myPoint>& vectorPoint,
	RGB_Color stroke,
	int strokeWidth,
	float strokeOpacity,
	RGB_Color fill,
	float fillOpacity,
	int transformOrder,
	myPoint translate,
	int rotate) : myPolyline(vectorPoint, stroke, strokeWidth, strokeOpacity, fill, fillOpacity, transformOrder, translate, rotate) {}

myPolygon::myPolygon(const vector<myPoint>& vectorPoint,
	const vector<char>& transformOrder,
	const vector<myPoint>& translate,
	const vector<char>& rotate,
	RGB_Color stroke,
	int strokeWidth,
	float strokeOpacity,
	RGB_Color fill,
	float fillOpacity) : myPolyline(vectorPoint, transformOrder, translate, rotate, stroke, strokeWidth, strokeOpacity, fill, fillOpacity) {}

myPolygon::myPolygon(xml_node<>* node): myPolyline(node) {}

void myPolygon::setPointsData(const vector<myPoint>& v) { myPolyline::setPointsData(v); }

void myPolygon::setPointsData(char* cPoints) { myPolyline::setPointsData(cPoints); }

void myPolygon::convertFromCString(xml_attribute<>* attr) { myPolyline::convertFromCString(attr); }

void myPolygon::draw(CImg<unsigned char>& img)
{
	myLine* tmpLine = new myLine(this->m_pointData[0], this->m_pointData[1], this->m_transformOrder, this->m_translate, this->m_rotate, this->m_stroke, this->m_strokeWidth, this->m_strokeOpacity);
	for (int i = 0; i < this->m_pointData.size() - 1; ++i)
	{
		tmpLine->setPoints(this->m_pointData[i], this->m_pointData[i + 1]);
		tmpLine->draw(img);
	}
	tmpLine->setPoints(this->m_pointData.back(), this->m_pointData[0]);
	tmpLine->draw(img);
	delete tmpLine;

	CImg<int> myPoints(this->m_pointData.size(), 2);
	myPoint tmp;
	cimg_forX(myPoints, i)
	{
		tmp = this->m_pointData[i].transform(this->m_translate, this->m_rotate, this->m_transformOrder);
		myPoints(i, 0) = tmp.x;
		myPoints(i, 1) = tmp.y;
	}
	unsigned char fillColor[3];
	convert_RGB_to_unsigned_char(fillColor, this->m_fill);
	img.draw_polygon(myPoints, fillColor, this->m_fillOpacity);
}

void myPolygon::draw(HDC& hdc)
{
	Graphics graphics(hdc);
	Pen pen(Color(BYTE(this->m_strokeOpacity * 255), this->m_stroke.red, this->m_stroke.green, this->m_stroke.blue), this->m_strokeWidth);

	Point* points = new Point[this->m_pointData.size()];
	myPoint tmp;
	for (int i = 0; i < this->m_pointData.size(); ++i)
	{
		tmp = this->m_pointData[i].transform(this->m_translate, this->m_rotate, this->m_transformOrder);
		points[i].X = tmp.x;
		points[i].Y = tmp.y;
	}
	graphics.DrawPolygon(&pen, points, this->m_pointData.size());
	SolidBrush solidBrush(Color(BYTE(this->m_fillOpacity * 255), this->m_fill.red, this->m_fill.green, this->m_fill.blue));
	graphics.FillPolygon(&solidBrush, points, this->m_pointData.size());
	delete points;
}

string myPolygon::getXmlCode()
{
	ostringstream buffer;
	string Code = "<polygon ";
	Code += FillFigure::getXmlCode();

	Code += "points=\"";
	for (int i = 0; i < this->m_pointData.size(); ++i)
	{
		buffer << this->m_pointData[i].x;
		Code += buffer.str();
		buffer.str("");
		Code += ",";
		buffer << this->m_pointData[i].y;
		Code += buffer.str();
		buffer.str("");
		Code += " ";
	}

	Code.back() = '\"';
	Code += " />\n";
	return Code;
}

myPolygon::~myPolygon() {}