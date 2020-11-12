#include "stdafx.h"
#include "Group.h"
#include <stack>

myGroup::myGroup() : FillFigure() { this->m_listFigure.clear(); addSample(this); }
myGroup::myGroup(myGroup* p): FillFigure(p)
{
	for (int i = 0; i < this->m_listFigure.size(); ++i)
		delete this->m_listFigure[i];
	this->m_listFigure.clear();

	for (int i = 0; i < p->m_listFigure.size(); ++i)
	{
		Figure* pFig = p->m_listFigure[i]->clone();
		this->m_listFigure.push_back(pFig);
	}
}

void myGroup::draw(CImg<unsigned char>& img)
{
	for (int i = 0; i < this->m_listFigure.size(); ++i)
		this->m_listFigure[i]->draw(img);
}

void myGroup::draw(HDC& hdc)
{
	for (int i = 0; i < this->m_listFigure.size(); ++i)
		this->m_listFigure[i]->draw(hdc);
}

Figure* myGroup::clone() { return new myGroup(this); }
char* myGroup::className() { return "g"; }

void myGroup::addElement(Figure* pFig) { this->m_listFigure.push_back(pFig); }
void myGroup::setAttribute(char* attr_name, char* attr_value)
{
	map<char*, Attribute*>::iterator it1;
	it1 = this->m_attributes.find(attr_name);
	if (it1 != this->m_attributes.end())
	{
		it1->second->setValue(attr_value);
	}
}

void myGroup::setByNodeAndAddTransform(xml_node<>* node)
{
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

	xml_node<>* cnode = node->first_node();
	while (cnode)
	{
		Figure* pFig = Figure::createObject(cnode->name());
		pFig->setAttribute(this);
		pFig->setByNodeAndAddTransform(cnode);
		this->addElement(pFig);
		cnode = cnode->next_sibling();
	}
}

void myGroup::setByNode(xml_node<>* node)
{
	this->setByNodeAndAddTransform(node);
}

myGroup::~myGroup()
{
	for (int i = 0; i < this->m_listFigure.size(); ++i)
		delete this->m_listFigure[i];
	this->m_listFigure.clear();
}
