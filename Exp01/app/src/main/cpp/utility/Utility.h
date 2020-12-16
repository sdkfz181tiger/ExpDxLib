//==========
// C++
#include <algorithm>
#include <ctime>
#include <chrono>
#include <functional>
#include <iomanip>
#include <iostream>
#include <locale>
#include <map>
#include <random>
#include <string>

//==========
// Library
#include "DxLib.h"
#include "android/log.h"
//#include "json11/json11.hpp"
//#include "tweeny/tweeny.h"

//==========
// Utility
#include "UtilDebug.h"
#include "UtilLabel.h"
#include "UtilMath.h"
#include "Vec2.h"

//==========
// Namespace
using namespace std;
//using namespace json11;
//using tweeny::easing;

//==========
// Macro
#ifndef LOGD
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, __VA_ARGS__)
#endif

#ifndef LOGW
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, __VA_ARGS__)
#endif

#ifndef LOGE
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, __VA_ARGS__)
#endif