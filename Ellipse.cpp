#include "stdafx.h"
#include "Ellipse.h"

//myEllipse
myEllipse::myEllipse() : FillFigure()
{
	this->m_center = 0;
	this->m_rx = this->m_ry = 50;
}

myEllipse::myEllipse(myPoint center, int rx, int ry,
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
	this->m_rx = rx;
	this->m_ry = ry;
}

myEllipse::myEllipse(myPoint center, int rx, int ry,
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
	this->m_rx = rx;
	this->m_ry = ry;
}

myEllipse::myEllipse(xml_node<>* node)
{
	for (xml_attribute<> *attr = node->first_attribute();
		attr; attr = attr->next_attribute())
	{
		this->convertFromCString(attr);
	}
}

myPoint myEllipse::getCenter() { return this->m_center; }
void myEllipse::setCenter(myPoint center) { this->m_center = center; }
void myEllipse::setCenter(int x, int y)
{
	this->m_center.x = x;
	this->m_center.y = y;
}

int myEllipse::getRx() { return this->m_rx; }
void myEllipse::setRx(int rx) { this->m_rx = rx; }
int myEllipse::getRy() { return this->m_ry; }
void myEllipse::setRy(int ry) { this->m_ry = ry; }

void myEllipse::draw(CImg<unsigned char>& img)
{
	unsigned char fillColor[3];
	convert_RGB_to_unsigned_char(fillColor, this->m_fill);

	unsigned char strokeColor[3];
	convert_RGB_to_unsigned_char(strokeColor, this->m_stroke);

	myPoint center(this->m_center.transform(this->m_translate, this->m_rotate, this->m_transformOrder));
	myPoint A(this->m_center.translate(-this->m_rx, 0).transform(this->m_translate, this->m_rotate, this->m_transformOrder));
	
	float angle = atan((1.0*(center.y - A.y)) / (1.0*(center.x - A.x))) * 180.0/acos(-1);

	img.draw_ellipse(center.x, center.y, this->m_rx - this->m_strokeWidth, this->m_ry - this->m_strokeWidth, angle, fillColor, this->m_fillOpacity);
	for (int i = 0; i < this->m_strokeWidth; ++i)
		img.draw_ellipse(center.x, center.y, this->m_rx - i, this->m_ry - i, angle, strokeColor, this->m_strokeOpacity, 1);
}

void myEllipse::draw(HDC& hdc)
{
	Graphics graphics(hdc);
	Pen pen(Color(BYTE(this->m_strokeOpacity * 255), this->m_stroke.red, this->m_stroke.green, this->m_stroke.blue), this->m_strokeWidth);
	SolidBrush solidBrush(Color(BYTE(this->m_fillOpacity * 255), this->m_fill.red, this->m_fill.green, this->m_fill.blue));

	myPoint topLeft = this->m_center.translate(-this->m_rx, -this->m_ry);
		
	int j = this->m_translate.size() - 1, k = this->m_rotate.size() - 1;
	
	for (int i = this->m_transformOrder.size() - 1; i >= 0; --i)
	{
		if (this->m_transformOrder[i] == 0)
		{
			graphics.TranslateTransform(this->m_translate[j].x, this->m_translate[j].y);
			j--;
		}
		else graphics.RotateTransform(this->m_rotate[k--]);
	}

	graphics.DrawEllipse(&pen, topLeft.x, topLeft.y, 2 * this->m_rx, 2 * this->m_ry);
	graphics.FillEllipse(&solidBrush, topLeft.x, topLeft.y, 2 * this->m_rx, 2 * this->m_ry);
	
	j = k = 0;
	
	for (int i = 0; i < this->m_transformOrder.size(); ++i)
	{
		if (this->m_transformOrder[i] == 0)
		{
			graphics.TranslateTransform(this->m_translate[j].x, this->m_translate[j].y);
			j++;
		}
		else graphics.RotateTransform(this->m_rotate[k++]);
	}
}

string myEllipse::getXmlCode()
{
	ostringstream buffer;
	string Code = "<ellipse cx=\"";
	buffer << this->m_center.x;
	Code += buffer.str();
	buffer.str("");
	Code += "\" cy=\"";
	buffer << this->m_center.y;
	Code += buffer.str();
	buffer.str("");

	Code += "\" rx=\"";
	buffer << this->m_rx;
	Code += buffer.str();
	buffer.str("");
	Code += "\" ry=\"";
	buffer << this->m_ry;
	Code += buffer.str();
	buffer.str("");
	Code += "\" ";
	Code += FillFigure::getXmlCode();

	Code += "/>\n";
	return Code;
}

void myEllipse::convertFromCString(xml_attribute<>* attr)
{
	if (strcmp(attr->name(), "cx") == 0)
		this->m_center.x = convert_char_to_int(attr->value(), 0, 10);
	else if (strcmp(attr->name(), "cy") == 0)
		this->m_center.y = convert_char_to_int(attr->value(), 0, 10);
	else if (strcmp(attr->name(), "rx") == 0)
		this->m_rx = convert_char_to_int(attr->value(), 0, 10);
	else if (strcmp(attr->name(), "ry") == 0)
		this->m_ry = convert_char_to_int(attr->value(), 0, 10);
	else
		FillFigure::convertFromCString(attr);
}

myEllipse::~myEllipse() {}