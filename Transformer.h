#pragma once
#include "stdafx.h"
#include "Point.h"

#define ORDER         1
#define INVERSE_ORDER 0

class Transformer
{
protected:
	vector<myPoint> m_translate;
	vector<char> m_rotate;
	vector<char> m_transformOrder;
public:
	Transformer(char transform_Order = 0, myPoint translate = 0, char rotate = 0);
	Transformer(const vector<char>&, const vector<myPoint>&, const vector<char>&);
	
	vector<myPoint> getTranslate();
	void addTranslate(int, int);
	void setTranslate(const vector<myPoint>&);

	vector<char> getRotate();
	void addRotate(char);
	void setRotate(const vector<char>&);

	vector<char> getTransformOrder();
	bool setTransformerOrder(const vector<char>&);

	string getTransformerCode();
	void resetTransformer();

	Transformer* setTransformer(char*, const char order = ORDER);

	virtual ~Transformer();
};