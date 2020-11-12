#include "stdafx.h"
#include "ListFigure.h"

ListFigure::ListFigure() {}

INT ListFigure::readXML(char* fileName)
{
	string input_xml;
	string line;
	ifstream in(fileName);

	if (!in)
		return 1;
	while (getline(in, line))
		input_xml += line;

	in.close();

	vector<char> xml_copy(input_xml.begin(), input_xml.end());
	xml_copy.push_back('\0');	
	xml_document<> doc;
	doc.parse<parse_declaration_node | parse_no_data_nodes>(&xml_copy[0]);

	xml_node<> *node = doc.first_node("svg");

	node = node->first_node();
	do
	{
		Figure* pFig = Figure::createObject(node->name());
		if (pFig)
		{
			pFig->setByNode(node);
			this->m_figures.push_back(pFig);
		}
		node = node->next_sibling();
	} while (node);	

	return 0;
}

void ListFigure::draw(CImg<unsigned char>& img)
{
	for (int i = 0; i < this->m_figures.size(); ++i)
	{
		this->m_figures[i]->draw(img);
	}
}

void ListFigure::draw(HDC& hdc)
{
	for (int i = 0; i < this->m_figures.size(); ++i)
	{
		this->m_figures[i]->draw(hdc);
	}
}

ListFigure::~ListFigure()
{
	for (int i = 0; i < this->m_figures.size(); ++i)
	{
		delete this->m_figures[i];
	}
	this->m_figures.clear();
}