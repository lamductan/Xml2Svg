#include "stdafx.h"
#include "Figure.h"

class myPath : public FillFigure
{
protected:
	vector<pair<char, vector<float>>> m_Path;
	vector<PointF> m_vectorPoints;
	float m_firstPointX;
	float m_firstPointY;
	float m_lastPointX;
	float m_lastPointY;
public:
	myPath();
	myPath(myPath*);

	void init();
	vector<pair<char, vector<float>>>& getPath();
	void setPath(vector<pair<char, vector<float>>>&);
	void setPath(char*);

	virtual void draw(CImg<unsigned char>&);
	virtual void draw(HDC&);

	void setFirstPoint(float, float);
	myPoint getFirstPoint();
	void setLastPoint(float, float);
	myPoint getLastPoint();

	void addPoint(float, float);
	void moveTo(float, float);

	void drawL(vector<float>&, CImg<unsigned char>&);
	void drawH(vector<float>&, CImg<unsigned char>&);
	void drawV(vector<float>&, CImg<unsigned char>&);
	void drawC(vector<float>&, CImg<unsigned char>&);
	void drawZ(CImg<unsigned char>&);

	void drawL(vector<float>&, HDC&);
	void drawH(vector<float>&, HDC&);
	void drawV(vector<float>&, HDC&);
	void drawC(vector<float>&, HDC&);
	void fillPath(HDC&);
	void drawZ(HDC&);

	virtual Figure* clone();
	virtual char* className();
	void setAttribute(char*, char*);
	void setByNode(xml_node<>*);
	void setByNodeAndAddTransform(xml_node<>*);

	//virtual string getXmlCode();
	virtual ~myPath();
};
