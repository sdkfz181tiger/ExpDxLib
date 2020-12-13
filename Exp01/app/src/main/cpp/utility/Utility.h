//==========
// C++
#include <algorithm>
#include <ctime>
#include <chrono>
#include <functional>
#include <locale>
#include <map>
#include <iomanip>
#include <iostream>
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
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, "TAG", __VA_ARGS__)
#endif

#ifndef LOGW
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, "TAG", __VA_ARGS__)
#endif

#ifndef LOGE
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, "TAG", __VA_ARGS__)
#endif