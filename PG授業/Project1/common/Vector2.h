#pragma once

// √›Ãﬂ⁄∞ƒâªÇµÇ‹
template<class T> class Vector2Template
{
public:
	Vector2Template();
	Vector2Template(T x, T y);
	~Vector2Template();
	T x_;
	T y_;

	//void operator Vector2Tmplate<int>()
	//{
	//	return Vector2Tmplate<int>{ static_cast<int>(x_),static_cast<int>(y_) };
	//};

	operator Vector2Template<int>()
	{
		return Vector2Template<int>{ static_cast<int>(x_),static_cast<int>(y_) };
	};
	operator Vector2Template<float>()
	{
		return Vector2Template<float>{ static_cast<float>(x_),static_cast<float>(y_) };
	};


	// ë„ì¸ââéZéq
	Vector2Template& operator = (const Vector2Template& vec);
	// î‰ärââéZéq
	bool operator == (const Vector2Template& vec)const;
	bool operator != (const Vector2Template& vec)const;
	bool operator > (const Vector2Template& vec)const;
	bool operator >= (const Vector2Template& vec)const;
	bool operator < (const Vector2Template& vec)const;
	bool operator <= (const Vector2Template& vec)const;
	
	// ìYÇ¶éöââéZéq
	int& operator [] (int i);

	// íPçÄââéZéq
	Vector2Template& operator += (const Vector2Template& vec);
	Vector2Template& operator -= (const Vector2Template& vec);
	Vector2Template& operator *= (const Vector2Template& vec);
	Vector2Template& operator /= (const Vector2Template& vec);
	Vector2Template& operator %= (const Vector2Template& vec);

	Vector2Template& operator *= (T k);
	Vector2Template& operator /= (T k);

	Vector2Template operator + ()const;
	Vector2Template operator - ()const;
};

// Õﬁ∏ƒŸÇÃââéZ

// íPçÄââéZéqÅ@Vector2 ÅE int
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

// íPçÄââéZéqÅ@Vector2 ÅE Vector2
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

// ê‚ëŒíl
template<class T>
Vector2Template<T> abs(const Vector2Template<T>& u);

using Vector2 = Vector2Template<int>;
using Vector2d = Vector2Template<double>;
using Vector2f = Vector2Template<float>;

using Potision2 = Vector2;
using Potision2f = Vector2f;

using Size = Vector2;
using Sizef = Vector2f;

#include "./details/Vector2.h"