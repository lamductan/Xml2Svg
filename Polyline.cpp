#include "stdafx.h"
#include "Polyline.h"

//myPolyline
myPolyline::myPolyline() {}

myPolyline::myPolyline(const vector<myPoint>& vectorPoint,
	RGB_Color stroke,
	int strokeWidth,
	float strokeOpacity,
	RGB_Color fill,
	float fillOpacity,
	int transformOrder,
	myPoint translate,
	int rotate) : FillFigure(stroke, strokeWidth, strokeOpacity, fill, fillOpacity, transformOrder, translate, rotate)
{
	this->m_pointData.clear();
	for (int i = 0; i < vectorPoint.size(); ++i)
		this->m_pointData.push_back(vectorPoint[i]);
}

myPolyline::myPolyline(const vector<myPoint>& vectorPoint,
	const vector<char>& transformOrder,
	const vector<myPoint>& translate,
	const vector<char>& rotate,
	RGB_Color stroke,
	int strokeWidth,
	float strokeOpacity,
	RGB_Color fill,
	float fillOpacity) : FillFigure(transformOrder, translate, rotate, stroke, strokeWidth, strokeOpacity, fill, fillOpacity)
{
	this->m_pointData.clear();
	for (int i = 0; i < vectorPoint.size(); ++i)
		this->m_pointData.push_back(vectorPoint[i]);
}

myPolyline::myPolyline(xml_node<>* node)
{
	for (xml_attribute<> *attr = node->first_attribute();
		attr; attr = attr->next_attribute())
	{
		this->convertFromCString(attr);
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
	int len = strlen(charPoints);
	char* mCharPoints = new char[len + 1];
	strcpy(mCharPoints, charPoints);

	int nPoints = 0;
	for (int i = 0; i < len; ++i)
		if (charPoints[i] == ',') ++nPoints;

	char** cPoints = new char*[nPoints];
	for (int i = 0; i < nPoints; ++i)
		cPoints[i] = new char[10];

	char* token;
	token = strtok(mCharPoints, " ");
	strcpy(cPoints[0], token);
	int cur = 1;
	while (token != NULL)
	{
		token = strtok(NULL, " ");
		if (token != NULL) 
			strcpy(cPoints[cur++], token);
	}

	char* tmp = new char[10];
	myPoint newPoint;
	int x, y;
	for (int i = 0; i < nPoints; ++i)
	{
		int commaPos = 0;
		for (int j = 0; j < strlen(cPoints[i]); ++j)
			if (cPoints[i][j] == ',') commaPos = j;
		newPoint.x = convert_char_to_int(cPoints[i], 0, commaPos, ',');
		newPoint.y = convert_char_to_int(cPoints[i], commaPos + 1, 20);
		this->m_pointData.push_back(newPoint);
	}

	delete[] tmp;
	for (int i = 0; i < nPoints; ++i)
		delete[] cPoints[i];
	delete[] cPoints;
	delete[] mCharPoints;
}

void myPolyline::draw(CImg<unsigned char>& img)
{
	myLine* tmpLine = new myLine(this->m_pointData[0], this->m_pointData[1], this->m_transformOrder, this->m_translate, this->m_rotate, this->m_stroke, this->m_strokeWidth, this->m_strokeOpacity);
	for (int i = 0; i < this->m_pointData.size() - 1; ++i)
	{
		tmpLine->setPoints(this->m_pointData[i], this->m_pointData[i + 1]);
		tmpLine->draw(img);
	}
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

void myPolyline::draw(HDC& hdc)
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
	graphics.DrawLines(&pen, points, this->m_pointData.size());
	SolidBrush solidBrush(Color(BYTE(this->m_fillOpacity * 255), this->m_fill.red, this->m_fill.green, this->m_fill.blue));
	graphics.FillPolygon(&solidBrush, points, this->m_pointData.size());
	delete points;
}

string myPolyline::getXmlCode()
{
	ostringstream buffer;
	string Code = "<polyline ";
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

void myPolyline::convertFromCString(xml_attribute<>* attr)
{
	if (strcmp(attr->name(), "points") == 0)
	{
		this->setPointsData(attr->value());
	}
	else
		FillFigure::convertFromCString(attr);
}

myPolyline::~myPolyline() {}

ostream& operator<<(ostream& out, const myPolyline& p)
{
	out << "Point-data: ";
	for (int i = 0; i < p.m_pointData.size(); ++i)
		out << "(" << p.m_pointData[i].x << ", " << p.m_pointData[i].y << ") ";
	out << endl;
	return out;
}