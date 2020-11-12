// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

//#include "targetver.h"

// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <ObjIdl.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")
using namespace Gdiplus;

#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <utility>
#include <string>
#include <vector>
#include <map>
#include <set>
using namespace std;

#include "CImg.h"
using namespace cimg_library;

#define DELIMITER ", ()\n"

// TODO: reference additional headers your program requires here
