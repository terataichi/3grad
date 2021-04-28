#include "..\Vector2.h"
#include <cmath>
#include <cassert>

template<class T>
Vector2Template<T>::Vector2Template()
{
	x_ = 0;
	y_ = 0;
}

template<class T>
Vector2Template<T>::Vector2Template(T x, T y)
{
	this-> x_ = x;
	this-> y_ = y;
}

template<class T>
Vector2Template<T>::~Vector2Template()
{

}

// ë„ì¸
template<class T>
Vector2Template<T> & Vector2Template<T>::operator=(const Vector2Template<T> & vec)
{
	x_ = vec.x_;
	y_ = vec.y_;
	return *this;
}

// î‰ärââéZéq
template<class T>
bool Vector2Template<T>::operator==(const Vector2Template<T> & vec) const
{
	return ((x_ == vec.x_) && (y_ == vec.y_));
}

template<class T>
bool Vector2Template<T>::operator!=(const Vector2Template<T> & vec) const
{
	return !((x_ == vec.x_) && (y_ == vec.y_));
}

template<class T>
bool Vector2Template<T>::operator>(const Vector2Template<T> & vec) const
{
	return ((x_ > vec.x_ )&&(y_ > vec.y_));
}

template<class T>
bool Vector2Template<T>::operator>=(const Vector2Template<T> & vec) const
{
	return ((x_ >= vec.x_) && (y_ >= vec.y_));
}

template<class T>
bool Vector2Template<T>::operator<(const Vector2Template<T> & vec) const
{
	return ((x_ > vec.x_) && (y_ > vec.y_));
}

template<class T>
bool Vector2Template<T>::operator<=(const Vector2Template<T> & vec) const
{
	return ((x_ <= vec.x_) && (y_ <= vec.y_));
}

// ìYÇ¶éöââéZ
template<class T>
int & Vector2Template<T>::operator[](int i)
{
	if (i == 0)
	{
		return x_;
	}
	else if (i == 1)
	{
		return y_;
	}
	else
	{
		assert(!"error");
		return x_;	// ó·äOèàóù
	}
}

// ---íPçÄââéZéq
template<class T>
Vector2Template<T> & Vector2Template<T>::operator+=(const Vector2Template<T> & vec)
{
	x_ += vec.x_;
	y_ += vec.y_;
	return *this;
}

template<class T>
Vector2Template<T> & Vector2Template<T>::operator-=(const Vector2Template<T> & vec)
{
	x_ -= vec.x_;
	y_ -= vec.y_;
	return *this;
}

template<class T>
Vector2Template<T>& Vector2Template<T>::operator*=(const Vector2Template& vec)
{
	x_ *= vec.x_;
	y_ *= vec.y_;
	return *this;
}

template<class T>
Vector2Template<T>& Vector2Template<T>::operator/=(const Vector2Template& vec)
{
	if (vec.x_ != 0)
	{
		x_ /= vec.x_;
	}
	else
	{
		x_ = 0;
	}
	if (vec.y_ != 0)
	{
		y_ /= vec.y_;
	}
	else
	{
		x_ = 0;
	}
	return *this;
}

template<class T>
Vector2Template<T>& Vector2Template<T>::operator%=(const Vector2Template& vec)
{
	Vector2 tmp{ 0,0 };
	if (vec.x_ != 0)
	{
		tmp.x_ = static_cast<int>(x_) % static_cast<int>(vec.x_);
	}
	if (vec.y_ != 0)
	{
		tmp.y_ = static_cast<int>(y_) % static_cast<int>(vec.y_);
	}
	this->x_ = static_cast<T>(tmp.x_);
	this->y_ = static_cast<T>(tmp.y_);
	return *this;
}

template<class T>
Vector2Template<T> & Vector2Template<T>::operator*=(T k)
{
	x_ *= k;
	y_ *= k;
	return *this;
}

template<class T>
Vector2Template<T> & Vector2Template<T>::operator/=(T k)
{
	x_ /= k;
	y_ /= k;
	return *this;
}

template<class T>
Vector2Template<T> Vector2Template<T>::operator+() const
{
	return *this;
}

template<class T>
Vector2Template<T> Vector2Template<T>::operator-() const
{
	return {-x_, -y_};
}

// ---Õﬁ∏ƒŸÇÃââéZ
template<class T>
Vector2Template<T> operator+(const Vector2Template<T>& u, const T& k)
{
	return { u.x_ + k ,u.y_ + k };
}
template<class T>
Vector2Template<T> operator-(const Vector2Template<T> & u, const T & k)
{
	return { u.x_ - k ,u.y_ - k };
}
template<class T>
Vector2Template<T> operator%(const Vector2Template<T> & u, const T & k)
{
	return { u.x_ % k ,u.y_ % k };
}
template<class T>
Vector2Template<T> operator*(const Vector2Template<T> & u, const T & k)
{
	return { u.x_ * k ,u.y_ * k };
}
template<class T>
Vector2Template<T> operator/(const Vector2Template<T> & u, const T & k)
{
	return { u.x_ / k ,u.y_ / k };
}

template<class T>
Vector2Template<T> operator+(const Vector2Template<T> & u, const Vector2Template<T> & v)
{
	return { u.x_ + v.x_,u.y_ + v.y_ };
}
template<class T>
Vector2Template<T> operator-(const Vector2Template<T> & u, const Vector2Template<T> & v)
{
	return { u.x_ - v.x_,u.y_ - v.y_ };
}
template<class T>
Vector2Template<T> operator*(const Vector2Template<T> & u, const Vector2Template<T> & v)
{
	return { u.x_ * v.x_,u.y_ * v.y_ };
}
template<class T>
Vector2Template<T> operator/(const Vector2Template<T> & u, const Vector2Template<T> & v)
{
	return { u.x_ / v.x_,u.y_ / v.y_ };
}
template<class T>
Vector2Template<T> operator%(const Vector2Template<T> & u, const Vector2Template<T> & v)
{
	return { u.x_ % v.x_,u.y_ % v.y_ };
}

template<class T>
Vector2Template<T> operator*(const T & k, const Vector2Template<T> & u)
{
	return { k * u.x_ ,k * u.y_ };
}

template<class T>
Vector2Template<T> abs(const Vector2Template<T>& u)
{
	return { abs(u.x_), abs(u.y_) };
}
