#include "stdafx.h"
#include "Figure.h"
#include "Line.h"
#include "Rectagle.h"
#include "Ellipse.h"
#include "Circle.h"
#include "Polyline.h"
#include "Polygon.h"

const int x[] = { 50, 150, 150, 250, 250, 350, 350, 450, 450, 550, 550, 650, 650, 750, 750, 850, 850, 950, 950, 1050, 1050, 1150 };
const int y[] = { 375, 375, 325, 325, 375, 375, 250, 250, 375, 375, 175, 175, 375, 375, 100, 100, 375, 375, 25, 25, 375, 375 };

const int xx[] = { 850, 958, 958, 850, 742, 742 };
const int yy[] = { 75, 137, 262, 325, 262, 137 };

VOID foo(HDC&);
INT readXML(CImg<unsigned char>&, HDC&);