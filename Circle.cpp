#include "stdafx.h"
#include "Circle.h"

//myCircle
myCircle::myCircle() : FillFigure() {}

myCircle::myCircle(myPoint center, int r,
	RGB_Color stroke,
	int strokeWidth,
	float strokeOpacity,
	RGB_Color fill,
	float fillOpacity,
	int transformOrder,
	myPoint translate,
	int rotate) : FillFigure(stroke, strokeWidth, strokeOpacity, fill, fillOpacity, transformOrder, translate, rotate)
{
	this->m_center = center;
	this->m_r = r;
}

myCircle::myCircle(myPoint center, int r,
	const vector<char>& transformOrder,
	const vector<myPoint>& translate,
	const vector<char>& rotate,
	RGB_Color stroke,
	int strokeWidth,
	float strokeOpacity,
	RGB_Color fill,
	float fillOpacity) : FillFigure(transformOrder, translate, rotate, stroke, strokeWidth, strokeOpacity, fill, fillOpacity)
{
	this->m_center = center;
	this->m_r = r;
}

myCircle::myCircle(xml_node<>* node)
{
	for (xml_attribute<> *attr = node->first_attribute();
		attr; attr = attr->next_attribute())
	{
		this->convertFromCString(attr);
	}
}

myPoint myCircle::getCenter() { return this->m_center; }
void myCircle::setCenter(myPoint center) { this->m_center = center; }
void myCircle::setCenter(int x, int y)
{
	this->m_center.x = x;
	this->m_center.y = y;
}

int myCircle::getR() { return this->m_r; }
void myCircle::setR(int r) { this->m_r = r; }

void myCircle::draw(CImg<unsigned char>& img)
{
	unsigned char fillColor[3];
	convert_RGB_to_unsigned_char(fillColor, this->m_fill);

	unsigned char strokeColor[3];
	convert_RGB_to_unsigned_char(strokeColor, this->m_stroke);

	myPoint center(this->m_center.transform(this->m_translate, this->m_rotate, this->m_transformOrder));

	img.draw_circle(center.x, center.y, this->m_r - this->m_strokeWidth, fillColor, this->m_fillOpacity);
	for (int i = 0; i < this->m_strokeWidth; ++i)
		img.draw_circle(center.x, center.y, this->m_r - i, strokeColor, this->m_strokeOpacity, 1);
}

void myCircle::draw(HDC& hdc)
{
	Graphics graphics(hdc);
	Pen pen(Color(BYTE(this->m_strokeOpacity * 255), this->m_stroke.red, this->m_stroke.green, this->m_stroke.blue), this->m_strokeWidth);
	SolidBrush solidBrush(Color(BYTE(this->m_fillOpacity * 255), this->m_fill.red, this->m_fill.green, this->m_fill.blue));

	myPoint topLeft = this->m_center.transform(this->m_translate, this->m_rotate, this->m_transformOrder).translate(-this->m_r, -this->m_r);
	graphics.DrawEllipse(&pen, topLeft.x, topLeft.y, 2 * this->m_r, 2 * this->m_r);
	graphics.FillEllipse(&solidBrush, topLeft.x, topLeft.y, 2 * this->m_r, 2 * this->m_r);
}

string myCircle::getXmlCode()
{
	ostringstream buffer;
	string Code = "<circle cx=\"";
	buffer << this->m_center.x;
	Code += buffer.str();
	buffer.str("");
	Code += "\" cy=\"";
	buffer << this->m_center.y;
	Code += buffer.str();
	buffer.str("");

	Code += "\" r=\"";
	buffer << this->m_r;
	Code += buffer.str();
	buffer.str("");
	Code += "\" ";
	Code += FillFigure::getXmlCode();

	Code += "/>\n";
	return Code;
}

void myCircle::convertFromCString(xml_attribute<>* attr)
{
	if (strcmp(attr->name(), "cx") == 0)
		this->m_center.x = convert_char_to_int(attr->value(), 0, 10);
	else if (strcmp(attr->name(), "cy") == 0)
		this->m_center.y = convert_char_to_int(attr->value(), 0, 10);
	else if (strcmp(attr->name(), "r") == 0)
		this->m_r = convert_char_to_int(attr->value(), 0, 10);
	else
		FillFigure::convertFromCString(attr);
}

myCircle::~myCircle() {}