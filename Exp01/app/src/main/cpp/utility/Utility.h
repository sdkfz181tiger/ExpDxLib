//==========
// C++
#include <algorithm>
#include <ctime>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <locale>
#include <map>
#include <random>
#include <string>
#include <sstream>

//==========
// Library
#include "DxLib.h"
#include "android/log.h"
#include "nlohmann/json.hpp"
#include "tweeny/tweeny.h"

//==========
// Utility
#include "UtilDebug.h"
#include "UtilDx.h"
#include "UtilGraph.h"
#include "UtilJNI.h"
#include "UtilJson.h"
#include "UtilLabel.h"
#include "UtilLocalSave.h"
#include "UtilMath.h"
#include "UtilSound.h"
#include "Vec2.h"

//==========
// Namespace
using namespace std;
using json = nlohmann::json;
using easing = tweeny::easing;

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

#ifndef DX_SAFE_DELETE
#define DX_SAFE_DELETE(p) do { if(p) { delete (p); (p) = 0; } } while(0)
#endif

#ifndef DX_SAFE_DELETE_ARRAY
#define DX_SAFE_DELETE_ARRAY(p) do { if(p) { delete[] (p); (p) = 0; } } while(0)
#endif

#ifndef DX_SAFE_DELETE_VECTOR
#define DX_SAFE_DELETE_VECTOR(v) { auto it = v.end(); while (it-- != v.begin()) { delete (*it); v.erase(it); } }
#endif