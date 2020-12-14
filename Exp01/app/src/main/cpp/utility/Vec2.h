#ifndef _VEC2_H_
#define _VEC2_H_

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
// C++
#include <math.h>

class Vec2 {

public:

	float x, y;

public:

	Vec2(float x = 0.0f, float y = 0.0f) {};

	~Vec2() {};

	Vec2 operator+(const Vec2 &vec) const; // 和

	Vec2 &operator+=(const Vec2 &vec);

	Vec2 operator-(const Vec2 &vec) const; // 差

	Vec2 &operator-=(const Vec2 &vec);

	Vec2 operator*(float num) const;       // 積

	Vec2 &operator*=(float num);

	Vec2 operator/(float num) const;       // 商

	Vec2 &operator/=(float num);

	Vec2 normalize() const;                // 正規化

	float magnitude() const;               // スカラー

	float dot(const Vec2 &vec) const;      // 内積

	float cross(const Vec2 &vec) const;    // 外積

	float radian(const Vec2 &vec) const;   // 角度(ラジアン)

	float degree(const Vec2 &vec) const;   // 角度(デグリ)

	// 平均速度を算出
	static Vec2 getAverageVelocity(const Vec2 &vecA, const Vec2 &vecB, float interval);

	// 最終速度を算出
	static float getSpeedIAT(float velI, float accel, float time);

	// 位置の変化を算出
	static float getDistanceIFT(float velI, float velF, float time);

	// 位置の変化を算出
	static float getDistanceIAT(float velI, float accel, float time);

	// 加速度を算出
	static float getAccelIDT(float velI, float distance, float time);
};

#endif // _VEC2_H_