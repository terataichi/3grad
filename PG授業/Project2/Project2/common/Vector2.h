#pragma once

#define GRAVITY 10

// ﾃﾝﾌﾟﾚｰﾄ化しま
template<class T> class Vector2Template
{
public:
	Vector2Template();
	Vector2Template(T x, T y);
	~Vector2Template();
	T x_;
	T y_;

	operator Vector2Template<int>()
	{
		return Vector2Template<int>{ static_cast<int>(x_), static_cast<int>(y_) };
	};
	operator Vector2Template<float>()
	{
		return Vector2Template<float>{ static_cast<float>(x_), static_cast<float>(y_) };
	};

	Vector2Template operator + ()const;
	Vector2Template operator - ()const;

	// 代入演算子
	Vector2Template& operator = (const Vector2Template& vec);
	// 比較演算子
	bool operator == (const Vector2Template& vec)const;
	bool operator != (const Vector2Template& vec)const;
	bool operator > (const Vector2Template& vec)const;
	bool operator >= (const Vector2Template& vec)const;
	bool operator < (const Vector2Template& vec)const;
	bool operator <= (const Vector2Template& vec)const;

	// 添え字演算子
	int& operator [] (int i);

	// 単項演算子
	Vector2Template& operator += (const Vector2Template& vec);
	Vector2Template& operator -= (const Vector2Template& vec);
	Vector2Template& operator *= (const Vector2Template& vec);
	Vector2Template& operator /= (const Vector2Template& vec);
	Vector2Template& operator %= (const Vector2Template& vec);

	Vector2Template& operator *= (T k);
	Vector2Template& operator /= (T k);

	float Magnitude()const;
	static Vector2Template ZERO;
	Vector2Template<float> Normalized(void);
};

// 単項演算子　Vector2 ・ int
template<class T>
Vector2Template<T> operator +(const Vector2Template<T>& u, const T& k);
template<class T>
Vector2Template<T> operator -(const Vector2Template<T>& u, const T& k);
template<class T>
Vector2Template<T> operator *(const Vector2Template<T>& u, const T& k);
template<class T>
Vector2Template<T> operator /(const Vector2Template<T>& u, const T& k);
template<class T>
Vector2Template<T> operator %(const Vector2Template<T>& u, const T& k);

// 単項演算子　Vector2 ・ Vector2
template<class T>
Vector2Template<T> operator +(const Vector2Template<T>& u, const Vector2Template<T>& v);
template<class T>
Vector2Template<T> operator -(const Vector2Template<T>& u, const Vector2Template<T>& v);
template<class T>
Vector2Template<T> operator *(const Vector2Template<T>& u, const Vector2Template<T>& v);
template<class T>
Vector2Template<T> operator /(const Vector2Template<T>& u, const Vector2Template<T>& v);
template<class T>
Vector2Template<T> operator %(const Vector2Template<T>& u, const Vector2Template<T>& v);

// int * Vector2
template<class T>
Vector2Template<T> operator *(const T& k, const Vector2Template<T>& u);

// 内積
template<class T>
float Dot(const Vector2Template<T>& u, const Vector2Template<T>& v);

// 外積
template<class T>
float Cross(const Vector2Template<T>& u, const Vector2Template<T>& v);

// 法線ベクトル
template<class T>
Vector2Template<T> Normal(const Vector2Template<T>& u);

// 絶対値
template<class T>
Vector2Template<T> abs(const Vector2Template<T>& u);

using Vector2 = Vector2Template<int>;
using Vector2d = Vector2Template<double>;
using Vector2f = Vector2Template<float>;

using Potision2 = Vector2;
using Potision2f = Vector2f;

using Size = Vector2;
using Sizef = Vector2f;

#include "details/Vector2.h"