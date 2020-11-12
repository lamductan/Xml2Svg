#include "stdafx.h"
#include "Figure.h"

class myGroup: public FillFigure
{
protected:
	vector<Figure*> m_listFigure;
public:
	myGroup();
	myGroup(myGroup*);

	virtual void draw(CImg<unsigned char>&);
	virtual void draw(HDC&);

	virtual Figure* clone();
	virtual char* className();
	
	void addElement(Figure*);
	void setAttribute(char*, char*);
	void setByNode(xml_node<>*);
	void setByNodeAndAddTransform(xml_node<>*);

	virtual string getXmlCode();
	virtual ~myGroup();
};