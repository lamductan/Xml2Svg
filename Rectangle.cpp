#include "stdafx.h"
#include "Rectagle.h"

//myRectangle
myRectangle::myRectangle() : FillFigure()
{
	this->m_topLeft = 0;
	this->m_height = this->m_width = 50;
}

myRectangle::myRectangle(myPoint topLeft, int width, int height,
	RGB_Color stroke,
	int strokeWidth,
	float strokeOpacity,
	RGB_Color fill,
	float fillOpacity,
	int transformOrder,
	myPoint translate,
	int rotate) : FillFigure(stroke, strokeWidth, strokeOpacity, fill, fillOpacity, transformOrder, translate, rotate)
{
	this->m_topLeft = topLeft;
	this->m_height = height;
	this->m_width = width;
}

myRectangle::myRectangle(myPoint topLeft, int width, int height,
	const vector<char>& transformOrder,
	const vector<myPoint>& translate,
	const vector<char>& rotate,
	RGB_Color stroke,
	int strokeWidth,
	float strokeOpacity,
	RGB_Color fill,
	float fillOpacity) : FillFigure(transformOrder, translate, rotate, stroke, strokeWidth, strokeOpacity, fill, fillOpacity)
{
	this->m_topLeft = topLeft;
	this->m_height = height;
	this->m_width = width;
}

myRectangle::myRectangle(xml_node<>* node)
{
	for (xml_attribute<> *attr = node->first_attribute();
		attr; attr = attr->next_attribute())
	{
		this->convertFromCString(attr);
	}
}

myPoint myRectangle::getTopLeft() { return this->m_topLeft; }
void myRectangle::setTopLeft(myPoint topLeft) { this->m_topLeft = topLeft; }
void myRectangle::setTopLeft(int x, int y)
{
	this->m_topLeft.x = x;
	this->m_topLeft.y = y;
}

void myRectangle::draw(CImg<unsigned char>& img)
{
	vector<myPoint> v;
	v.push_back(this->m_topLeft);
	v.push_back(v.back().translate(this->m_width, 0));
	v.push_back(v.back().translate(0, this->m_height));
	v.push_back(v.back().translate(-this->m_width, 0));

	myPolygon* tmpPolygon = new myPolygon(v, this->m_transformOrder, this->m_translate, this->m_rotate, this->m_stroke, this->m_strokeWidth, this->m_strokeOpacity, this->m_fill, this->m_fillOpacity);
	tmpPolygon->draw(img);
	delete tmpPolygon;
}

void myRectangle::draw(HDC& hdc)
{
	vector<myPoint> v;
	v.push_back(this->m_topLeft);
	v.push_back(v.back().translate(this->m_width, 0));
	v.push_back(v.back().translate(0, this->m_height));
	v.push_back(v.back().translate(-this->m_width, 0));

	myPolygon* tmpPolygon = new myPolygon(v, this->m_transformOrder, this->m_translate, this->m_rotate, this->m_stroke, this->m_strokeWidth, this->m_strokeOpacity, this->m_fill, this->m_fillOpacity);
	tmpPolygon->draw(hdc);
	delete tmpPolygon;
}

string myRectangle::getXmlCode()
{
	ostringstream buffer;
	string Code = "<rect x=\"";
	buffer << this->m_topLeft.x;
	Code += buffer.str();
	buffer.str("");
	Code += "\" y=\"";
	buffer << this->m_topLeft.y;
	Code += buffer.str();
	buffer.str("");

	Code += "\" width=\"";
	buffer << this->m_width;
	Code += buffer.str();
	buffer.str("");
	Code += "\" height=\"";
	buffer << this->m_height;
	Code += buffer.str();
	buffer.str("");
	Code += "\" ";
	Code += FillFigure::getXmlCode();

	Code += "/>\n";
	return Code;
}

void myRectangle::convertFromCString(xml_attribute<>* attr)
{
	if (strcmp(attr->name(), "x") == 0)
		this->m_topLeft.x = convert_char_to_int(attr->value(), 0, 5);
	else if (strcmp(attr->name(), "y") == 0)
		this->m_topLeft.y = convert_char_to_int(attr->value(), 0, 10);
	else if (strcmp(attr->name(), "width") == 0)
		this->m_width = convert_char_to_int(attr->value(), 0, 10);
	else if (strcmp(attr->name(), "height") == 0)
		this->m_height = convert_char_to_int(attr->value(), 0, 10);
	else
		FillFigure::convertFromCString(attr);
}

myRectangle::~myRectangle() {}