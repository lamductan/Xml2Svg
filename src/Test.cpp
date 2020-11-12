#include "stdafx.h"
#include "Test.h"

//Main test function 1

Figure* s_line, *s_rectangle, *s_polyline, *s_polygon, *s_circle, *s_ellipse, *s_path, *s_text, *s_group;

VOID initialize()
{
	s_line = new myLine;
	s_rectangle = new myRectangle;
	s_polygon = new myPolygon;
	s_polyline = new myPolyline;
	s_circle = new myCircle;
	s_ellipse = new myEllipse;
	s_path = new myPath;
	s_text = new myText;
	s_group = new myGroup;
}

VOID endProgram()
{
	delete s_line;
	delete s_rectangle;
	delete s_polygon;
	delete s_polyline;
	delete s_circle;
	delete s_ellipse;
	delete s_path;
	delete s_text;
	delete s_group;
}

VOID test(char* fileName, HDC& hdc)
{
	initialize();
	ListFigure listFigure;
	//CImg<unsigned char> img(1500, 1000, 1, 3);
	//img.fill(255);

	listFigure.readXML(fileName);
	//listFigure.draw(img);
	listFigure.draw(hdc);

	//img.display("Demo CImg");
	endProgram();
}