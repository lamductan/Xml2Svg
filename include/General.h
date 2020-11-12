#pragma once

#include "stdafx.h"
#include "RGB.h"
#include "Transformer.h"

#define MAXLENGTH 5000

const char commandLetters[] = { 'L', 'H', 'V', 'C', 'M', 'Z' };

void convert_RGB_to_unsigned_char(unsigned char*, const RGB_Color&);
void removeLastCharacters(char* fileName, int charsToDelete = 7);
bool isNewCommand(char*);
WCHAR* convertStringToWCHAR(string);