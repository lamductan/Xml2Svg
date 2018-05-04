#include "stdafx.h"
#include "Test.h"

//Main test function 1
VOID foo(HDC& hdc)
{
	FILE *f = fopen("a.svg", "w");
	fputs("<svg xmlns=\"http://www.w3.org/2000/svg\">\n", f);
	fputs("</svg>", f);
	fclose(f);

	CImg<unsigned char> img(1500, 1000, 1, 3);
	img.fill(255);

	//Test Line
	myPoint point1(100, 300), point2(300, 100);
	RGB_Color lineColor1(0, 0, 255);
	Figure* l1 = new myLine(point1, point2, lineColor1, 5, 0.7f);
	l1->drawToFile("a.svg");
	l1->draw(img);
	l1->draw(hdc);

	myPoint point3(300, 300), point4(500, 100);
	RGB_Color lineColor2(0, 0, 255);
	Figure* l2 = new myLine(point3, point4, lineColor2, 10, 0.8f);
	l2->drawToFile("a.svg");
	l2->draw(img);
	l2->draw(hdc);

	myPoint point5(500, 300), point6(700, 100);
	RGB_Color lineColor3(0, 0, 255);
	Figure* l3 = new myLine(point5, point6, lineColor3, 15, 0.9f);
	l3->drawToFile("a.svg");
	l3->draw(img);
	l3->draw(hdc);

	//Test Rectangle
	RGB_Color rectStroke(0, 0, 255);
	RGB_Color rectFill(255, 0, 0);
	myPoint rectTopLeft1(1, 1), rectTopLeft2(150, 150);
	myRectangle* r1 = new myRectangle(rectTopLeft1, 1200, 600, rectStroke, 10, 0.7f, rectFill, 0.5f);
	myPoint rectTranslate(-100, 200);
	myRectangle* r2 = new myRectangle(rectTopLeft2, 200, 200, rectStroke, 10, 0.7f, rectFill, 0.5f, ROTATE_FIRST, rectTranslate, -45);
	r1->drawToFile("a.svg");
	r1->draw(img);
	r1->draw(hdc);

	r2->drawToFile("a.svg");
	r2->draw(img);
	r2->draw(hdc);
	//end test

	//Test Circle
	myPoint cCenter1(100, 200);
	RGB_Color cStroke1(0, 255, 255);
	RGB_Color cFill1(255, 255, 0);
	myPoint cTranslate1(550, -100);
	myCircle* c1 = new myCircle(cCenter1, 100, cStroke1, 10, 0.7f, cFill1, 0.5f, TRANSLATE_FIRST, cTranslate1);
	c1->drawToFile("a.svg");
	c1->draw(img);
	c1->draw(hdc);

	myCircle* c2 = new myCircle(cCenter1, 200, cStroke1, 10, 0.7f, cFill1, 0.5f);
	c2->drawToFile("a.svg");
	c2->draw(img);
	c2->draw(hdc);
	//end test

	//Test Ellipse
	myPoint eCenter(150, 100);
	RGB_Color eStroke(255, 255, 0);
	RGB_Color eFill(0, 255, 0);
	myPoint eTranslate(-200, -30);
	myEllipse* e1 = new myEllipse(eCenter, 200, 100, eStroke, 3, 0.7, eFill, 0.5, TRANSLATE_FIRST, eTranslate, -30);
	e1->drawToFile("a.svg");
	e1->draw(img);
	e1->draw(hdc);
	//end test

	//Test Polyline
	RGB_Color plfillColor(0, 255, 255);
	RGB_Color plstrokeColor(255, 0, 0);
	myPoint plTranslate(0, 120);
	vector<myPoint> vectorPoint;
	for (int i = 0; i < 22; ++i)
	{
		myPoint a(x[i], y[i]);
		vectorPoint.push_back(a);
	}
	myPolyline* pl1 = new myPolyline(vectorPoint, plstrokeColor, 3, 0.7f, plfillColor, 0.5f, TRANSLATE_FIRST, plTranslate);
	pl1->drawToFile("a.svg");
	pl1->draw(img);
	pl1->draw(hdc);
	//end test

	//Test Polygon
	myPolygon* pg1 = new myPolygon;
	RGB_Color pgStroke(255, 0, 102);
	RGB_Color pgFill(153, 204, 255);
	myPoint pgTranslate(-180, -70);

	vectorPoint.clear();
	for (int i = 0; i < 6; ++i)
	{
		myPoint a(xx[i], yy[i]);
		vectorPoint.push_back(a);
	}
	pg1->setPointsData(vectorPoint);
	pg1->setStrokeWidth(10);
	pg1->setStroke(pgStroke);
	pg1->setFill(pgFill);
	pg1->setFillOpacity(0.5f);
	pg1->setStrokeOpacity(0.7f);
	pg1->addTranslate(-180, -70);
	pg1->drawToFile("a.svg");
	pg1->draw(img);
	pg1->draw(hdc);
	//end test

	delete l1;
	delete l2;
	delete l3;

	delete e1;

	delete c1;
	delete c2;

	delete r1;
	delete r2;

	delete pl1;
	delete pg1;

	img.display("Demo CImg");
}


//Main test function 2
INT readXML(CImg<unsigned char>& img, HDC& hdc)
{
	string input_xml;
	string line;
	ifstream in("sample.svg");

	if (!in)
		return 1;				// không mở được file sample.svg

								// đọc toàn bộ nội dung file vào string input_xml
	while (getline(in, line))
		input_xml += line;

	in.close();

	// tạo một mảng (vector) char từ input_xml
	vector<char> xml_copy(input_xml.begin(), input_xml.end());
	xml_copy.push_back('\0');	// thêm kí tự kết thúc chuỗi

								// dùng doc để dọc trên xml_copy
	xml_document<> doc;
	doc.parse<parse_declaration_node | parse_no_data_nodes>(&xml_copy[0]);

	// lấy thẻ svg đầu tiên, gán vào node
	xml_node<> *node = doc.first_node("svg");

	// node->first_node() lấy thẻ (tag) con đầu tiên của svg

	node = node->first_node();
	do
	{
		if (strcmp(node->name(), "line") == 0)
		{
			Figure* l5 = new myLine(node);
			l5->draw(img);
			l5->draw(hdc);
			delete l5;
		}
		else if (strcmp(node->name(), "rect") == 0)
		{
			Figure* r5 = new myRectangle(node);
			r5->draw(img);
			r5->draw(hdc);
			delete r5;
		}
		else if (strcmp(node->name(), "ellipse") == 0)
		{
			Figure* e5 = new myEllipse(node);
			e5->draw(img);
			e5->draw(hdc);
			delete e5;
		}
		else if (strcmp(node->name(), "circle") == 0)
		{
			Figure* c5 = new myCircle(node);
			c5->draw(img);
			c5->draw(hdc);
			delete c5;
		}
		else if (strcmp(node->name(), "polyline") == 0)
		{
			Figure* pl5 = new myPolyline(node);
			pl5->draw(img);
			pl5->draw(hdc);
			delete pl5;
		}
		else if (strcmp(node->name(), "polygon") == 0)
		{
			Figure* pg5 = new myPolygon(node);
			pg5->draw(img);
			pg5->draw(hdc);
			delete pg5;
		}
		else
		{
			/*for (xml_attribute<> *attr = node->first_attribute();
			attr; attr = attr->next_attribute())
			{
			cout << "Node " << node->name() << " has attribute " << attr->name() << " ";
			cout << "with value " << attr->value() << "\n";
			}*/
		}

		// sau khi duyệt xong tag hiện tại, đi đến tag tiếp theo ngang cấp
		// bằng node->next_sibling()
		// nếu muốn lấy con thì node->first_node()
		node = node->next_sibling();
	} while (node);		// cho đến khi không lấy được tag tiếp theo (giống như linked list)

						// không cần giải phóng gì cả (*node hay *attribute) vì dữ liệu do doc (xml_document<>)
						// quản lý, mà doc sẽ tự động giải phóng.

	img.display("demo");

	return 0;
}
//End test function