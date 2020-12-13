#include "Vec2.h"

Vec2::Vec2(float x, float y) : x(x), y(y) {

}

Vec2::~Vec2() {

}

Vec2 Vec2::operator+(const Vec2 &vec) const {

	return Vec2(x + vec.x, y + vec.y);
}

Vec2 &Vec2::operator+=(const Vec2 &vec) {
	x += vec.x;
	y += vec.y;
	return *this;
}

Vec2 Vec2::operator-(const Vec2 &vec) const {

	return Vec2(x - vec.x, y - vec.y);
}

Vec2 &Vec2::operator-=(const Vec2 &vec) {
	x -= vec.x;
	y -= vec.y;
	return *this;
}

Vec2 Vec2::operator*(float num) const {

	return Vec2(x * num, y * num);
}

Vec2 &Vec2::operator*=(float num) {
	x *= num;
	y *= num;
	return *this;
}

Vec2 Vec2::operator/(float num) const {

	return Vec2(x / num, y / num);
}

Vec2 &Vec2::operator/=(float num) {
	x /= num;
	y /= num;
	return *this;
}

// purpose:呼び出しベクトルの正規化。これによって呼び出しベクトルが変わる
// input:無し
// output:無し
Vec2 Vec2::normalize() const {

	float mag = magnitude();
	return Vec2(x / mag, y / mag);
}

// purpose:ベクトルの大きさを計算
// input:none
// output:ベクトルの大きさ
float Vec2::magnitude() const {

	return sqrtf(x * x + y * y);
}

// purpose:2つのベクトルの内積
// input:vec 呼び出しベクトルを内積するベクトル
// output:2つのベクトルを内積した値
float Vec2::dot(const Vec2 &vec) const {

	return (x * vec.x + y * vec.y);
}

// purpose:2つのベクトルの外積
// input:vec 呼び出しベクトルを外積するベクトル
// output:2つのベクトルを内積した値
float Vec2::cross(const Vec2 &vec) const {

	return (x * vec.y - y * vec.x);
}

// purpose:2つのベクトルのなす角(-3.14 ~ +3.14)
// input:vec 対象のベクトル
// output:2つのベクトルのなす角
float Vec2::radian(const Vec2 &vec) const {

	Vec2 vA = normalize();
	Vec2 vB = vec.normalize();
	return atan2f(vA.cross(vB), vA.dot(vB));
}

// purpose:2つのベクトルのなす角(-180.0 ~ +180.0)
// input:vec 対象のベクトル
// output:2つのベクトルのなす角
float Vec2::degree(const Vec2 &vec) const {

	return radian(vec) * RAD_TO_DEG;
}

// purpose:2つのベクトル(vecIからvecFまで移動する)の平均速度(interval時間)
// input:vecA, vecB 対象ベクトル
// output:新しく出来た平均速度ベクトル
Vec2 Vec2::getAverageVelocity(const Vec2 &vecI, const Vec2 &vecF, float interval) {

	Vec2 vec = Vec2(vecF.x - vecI.x, vecF.y - vecI.y);
	vec = vec * (1 / interval);
	return vec;
}

// purpose:初速度、加速度、時間が与えられた時、最終速度を計算する
// velI:初速度
// accel:加速度
// time:時間
float Vec2::getSpeedIAT(float velI, float accel, float time) {

	return velI + accel * time;
}

// purpose:初速度、最終速度、時間が与えられた時、位置の変化を計算する
// velI:初速度
// velF:最終速度
// time:時間
float Vec2::getDistanceIFT(float velI, float velF, float time) {

	return (velI + velF) * 0.5f * time;
}

// purpose:初速度、加速度、時間が与えられた時、位置の変化を計算する
// velI:初速度
// accel:加速度
// time:時間
float Vec2::getDistanceIAT(float velI, float accel, float time) {

	return velI * time + 0.5f * accel * time * time;
}

// purpose:初速度、加速度、時間が与えられた時、位置の変化を計算する
// velI:初速度
// accel:加速度
// time:時間
float Vec2::getAccelIDT(float velI, float distance, float time) {

	return (distance - velI * time) * 2 / (time * time);
}