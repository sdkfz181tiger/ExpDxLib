//==========
// Vec2
#include "Vec2.h"

//==========
// C++
#include <algorithm>
#include <ctime>
#include <chrono>
#include <functional>
#include <locale>
#include <map>
#include <math.h>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>

//==========
// Library
#include "android/log.h"
#include "DxLib.h"
//#include "json11/json11.hpp"
//#include "tweeny/tweeny.h"

//==========
// Namespace
using namespace std;
//using namespace json11;
//using tweeny::easing;

//==========
// Define
#ifndef PI
#define PI         3.141592653f
#endif

#ifndef RAD_TO_DEG
#define RAD_TO_DEG 57.29577951f
#endif

#ifndef DEG_TO_RAD
#define DEG_TO_RAD 0.017453293f
#endif

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