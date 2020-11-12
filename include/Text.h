#include "stdafx.h"
#include "Figure.h"

class myText: public FillFigure
{
protected:
	map<char*, string, cmp_str> m_charAttributes;
public:
	myText();
	myText(myText*);
	void init();

	void setX(float);
	float getX();
	float getY();
	void setY(float);
	float getFontSize();
	void setFontSize(float);

	string getFont();
	void setFont(string);
	string getText();
	void setText(string);
	string getTextAnchor();
	void setTextAnchor(string);

	virtual void draw(CImg<unsigned char>&);
	virtual void draw(HDC&);

	virtual Figure* clone();
	virtual char* className();
	void setAttribute(char*, char*);
	void setByNode(xml_node<>*);
	void setByNodeAndAddTransform(xml_node<>*);

	virtual string getXmlCode();
	virtual ~myText();
};