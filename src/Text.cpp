#include "stdafx.h"
#include "Text.h"
#include "General.h"

myText::myText() : FillFigure() { this->init(); addSample(this); }
myText::myText(myText* p): FillFigure(p)
{
	this->m_ownAttributes = p->m_ownAttributes;
	this->m_charAttributes = p->m_charAttributes;
}

void myText::init()
{
	this->m_ownAttributes.insert(pair<char*, float>{"x", 0.0f});
	this->m_ownAttributes.insert(pair<char*, float>{"y", 0.0f});
	this->m_ownAttributes.insert(pair<char*, float>{"font-size", 10.0f});
	this->m_charAttributes.insert(pair<char*, char*>{"text", ""});
	this->m_charAttributes.insert(pair<char*, char*>{"text-anchor", ""});
	this->m_charAttributes.insert(pair<char*, char*>{"font-family", ""});
}

void myText::setX(float x)
{
	this->m_ownAttributes["x"] = x;
}

float myText::getX()
{
	return this->m_ownAttributes["x"];
}

void myText::setY(float y)
{
	this->m_ownAttributes["y"] = y;
}

float myText::getFontSize()
{
	return this->m_ownAttributes["font-size"];
}

void myText::setFontSize(float fontSize)
{
	this->m_ownAttributes["font-size"] = fontSize;
}

float myText::getY()
{
	return this->m_ownAttributes["y"];
}

string myText::getText() { return this->m_charAttributes["text"]; }
void myText::setText(string text)
{
	this->m_charAttributes["text"] = text;
}

string myText::getTextAnchor() { return this->m_charAttributes["text-anchor"]; }
void myText::setTextAnchor(string textAnchor)
{
	this->m_charAttributes["text-anchor"] = textAnchor;
}

string myText::getFont() { return this->m_charAttributes["font"]; }
void myText::setFont(string font)
{
	this->m_charAttributes["font-family"] = font;
}

void myText::draw(CImg<unsigned char>& img)
{
	unsigned char fillColor[3];
	convert_RGB_to_unsigned_char(fillColor, this->getFill());

	img.draw_text(this->getX(), this->getY() - this->getFontSize(), this->getText().c_str(), fillColor, 0, this->getFillOpacity(), (int)this->getFontSize());
}

void myText::draw(HDC& hdc)
{
	Graphics graphics(hdc);
	WCHAR* text = convertStringToWCHAR(this->getText());
	WCHAR* font = convertStringToWCHAR(this->getFont());

	int size = this->getFontSize()*3/4;
	Font myFont(font, size);
	PointF origin(this->getX(), this->getY() - size + 1);
	SolidBrush solidBrush(Color(BYTE(this->getFillOpacity() * 255), this->getFill().red, this->getFill().green, this->getFill().blue));
	StringFormat format;
	if (this->getTextAnchor() == "start")
		format.SetAlignment(StringAlignmentNear);
	else if (this->getTextAnchor() == "center")
		format.SetAlignment(StringAlignmentCenter);
	else format.SetAlignment(StringAlignmentNear);

	Matrix* rTransMatrix = dynamic_cast<ListTransform*>(this->m_attributes["transform"])->getReverseMatrix();
	Matrix* transMatrix = dynamic_cast<ListTransform*>(this->m_attributes["transform"])->getMatrix();

	graphics.SetTransform(transMatrix);
	graphics.DrawString(text, this->getText().length(), &myFont, origin, &format, &solidBrush);
	graphics.SetTransform(rTransMatrix);

	delete[]text;
	delete[]font;
	delete rTransMatrix;
	delete transMatrix;

}

Figure* myText::clone() { return new myText(this); }
char* myText::className() { return "text"; }

void myText::setAttribute(char* attr_name, char* attr_value)
{
	map<char*, Attribute*>::iterator it1;
	map<char*, float>::iterator      it2;
	map<char*, string>::iterator     it3;

	it1 = this->m_attributes.find(attr_name);
	if (it1 != this->m_attributes.end())
	{
		it1->second->setValue(attr_value);
	}
	else
	{
		it2 = this->m_ownAttributes.find(attr_name);
		if (it2 != this->m_ownAttributes.end())
		{
			it2->second = atof(attr_value);
		}
		else
		{
			it3 = this->m_charAttributes.find(attr_name);
			if (it3 != this->m_charAttributes.end())
			{
				it3->second = string(attr_value);
			}
		}
	}
}

void myText::setByNode(xml_node<>* node)
{
	this->setText(string(node->value()));
	for (xml_attribute<> *attr = node->first_attribute();
		attr; attr = attr->next_attribute())
	{
		this->setAttribute(attr->name(), attr->value());
	}
}

void myText::setByNodeAndAddTransform(xml_node<>* node)
{
	this->setText(string(node->value()));
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

myText::~myText() {}