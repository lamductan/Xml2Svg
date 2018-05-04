#include "stdafx.h"
#include "Transformer.h"
#include "RGB.h"

//Transformer
Transformer::Transformer(char transformOrder, myPoint translate, char rotate)
{
	this->m_translate.clear();
	this->m_rotate.clear();
	this->m_transformOrder.clear();

	if ((translate.x != 0 || translate.y != 0) && (rotate != char(0)))
	{
		this->m_translate.push_back(translate);
		this->m_rotate.push_back((char)rotate);
		
		if (transformOrder == TRANSLATE_FIRST)
		{
			this->m_transformOrder.push_back(TRANSLATE);
			this->m_transformOrder.push_back(ROTATE);
		}
		else
		{
			this->m_transformOrder.push_back(ROTATE);
			this->m_transformOrder.push_back(TRANSLATE);
		}
	}
	else if ((translate.x == 0 && translate.y == 0) && rotate == char(0))
	{
		
	}
	else if (translate.x == 0 && translate.y == 0)
	{
		this->m_rotate.push_back(rotate);
		this->m_transformOrder.push_back(ROTATE);
	}
	else
	{
		this->m_transformOrder.push_back(TRANSLATE);
		this->m_translate.push_back(translate);
	}
}

Transformer::Transformer(const vector<char>& transformOrder, const vector<myPoint>& translate, const vector<char>& rotate)
{
	this->m_transformOrder = transformOrder;
	this->m_translate = translate;
	this->m_rotate = rotate;
}

vector<myPoint> Transformer::getTranslate() { return this->m_translate; }

void Transformer::addTranslate(int x, int y)
{
	myPoint newTranslate(x, y);
	this->m_translate.push_back(newTranslate);
	this->m_transformOrder.push_back(TRANSLATE);
}

void Transformer::setTranslate(const vector<myPoint>& translate) { this->m_translate = translate; }

vector<char> Transformer::getRotate() { return this->m_rotate; }

void Transformer::addRotate(char rotate)
{
	this->m_rotate.push_back(rotate); 
	this->m_transformOrder.push_back(ROTATE);
}

void Transformer::setRotate(const vector<char>& rotate) { this->m_rotate = rotate; }

vector<char> Transformer::getTransformOrder() { return this->m_transformOrder; }

bool Transformer::setTransformerOrder(const vector<char>& transformOrder)
{
	if (transformOrder.size() != this->m_translate.size() + this->m_rotate.size())
		return false;

	int count1 = 0;
	for (int i = 0; i < transformOrder.size(); ++i)
		if (transformOrder[i] == 1) ++count1;
	if (count1 == this->m_rotate.size())
	{
		this->m_transformOrder = transformOrder;
		return true;
	}
	else return false;
}

void Transformer::resetTransformer()
{
	this->m_translate.clear();
	this->m_rotate.clear();
	this->m_transformOrder.clear();
}

string Transformer::getTransformerCode()
{
	string Code;
	if (!this->m_translate.empty() || !this->m_rotate.empty())
	{
		Code += "transform= \"";
		ostringstream buffer;
		int j = this->m_translate.size() - 1, k = this->m_rotate.size() - 1;
		for (int i = this->m_transformOrder.size() - 1; i >= 0; --i)
		{
			if (this->m_transformOrder[i] == 0)
			{
				Code += "translate(";
				buffer << this->m_translate[j].x;
				Code += buffer.str();
				buffer.str("");
				Code += ",";
				buffer << this->m_translate[j].y;
				Code += buffer.str();
				buffer.str("");
				Code += ") ";
				--j;
			}
			else
			{
				Code += "rotate(";
				buffer << (int) this->m_rotate[k--];
				Code += buffer.str();
				buffer.str("");
				Code += ") ";
			}
		}
		Code += "\" ";
	}
	return Code;
}

Transformer* Transformer::setTransformer(char* charTransform, const char order)
{
	this->m_transformOrder.clear();
	this->m_rotate.clear();
	this->m_translate.clear();

	int len = strlen(charTransform);
	char* mCharTransform = new char[len + 1];
	strcpy(mCharTransform, charTransform);

	int nTransforms = 0;
	for (int i = 0; i < len; ++i)
		if (charTransform[i] == '(') ++nTransforms;

	char** cTransforms = new char*[nTransforms];
	for (int i = 0; i < nTransforms; ++i)
		cTransforms[i] = new char[20];

	char* token;
	token = strtok(mCharTransform, ")");
	strcpy(cTransforms[0], token);
	int cur = 1;
	while (token != NULL)
	{
		token = strtok(NULL, ")");
		if (token != NULL && cur < nTransforms)
			strcpy(cTransforms[cur++], token);
	}

	myPoint vectorTranslate;
	int x, y;
	for (int i = 0; i < nTransforms; ++i)
	{
		if (cTransforms[i][0] == 't' || cTransforms[i][1] == 't')
		{
			int commaPos = 0;
			for (int j = 0; j < strlen(cTransforms[i]); ++j)
				if (cTransforms[i][j] == ',') commaPos = j;
			vectorTranslate.x = convert_char_to_int(cTransforms[i], strchr(cTransforms[i], '(') - cTransforms[i] + 1, commaPos, ',');
			vectorTranslate.y = convert_char_to_int(cTransforms[i], commaPos + 1, 30);
			this->addTranslate(vectorTranslate.x, vectorTranslate.y);
		}
		else
		{
			this->addRotate(convert_char_to_int(cTransforms[i], strchr(cTransforms[i], '(') - cTransforms[i] + 1, 15));
		}
	}

	for (int i = 0; i < nTransforms; ++i)
		delete[] cTransforms[i];
	delete[] cTransforms;
	delete[] mCharTransform;

	if (order == INVERSE_ORDER)
	{
		reverse(this->m_transformOrder.begin(), this->m_transformOrder.end());
		reverse(this->m_translate.begin(), this->m_translate.end());
		reverse(this->m_rotate.begin(), this->m_rotate.end());
	}

	return this;
}

Transformer::~Transformer() {}