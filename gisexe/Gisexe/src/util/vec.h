#ifndef _VEC_H_
#define _VEC_H_

#include <math.h>
#include "common.h"

_GIS_BEGIN
//类模版
template <class T = float, int N = 3>
class Vec
{
public:
	Vec() 
	{
		for (int i = 0; i < N; i++)
		{
			_v[i] = 0; // 默认都构造为0
		}
	}

	Vec(const T t[])
	{
		for (int i = 0; i < N; i++)
		{
			_v[i] = t[i];
		}
	}

	T& operator[](int i)
	{
		return _v[i];
	}

	const T& operator[](int i) const
	{
		return _v[i];
	}

	Vec<T, N>& operator-=(const Vec<T, N>& vec)
	{
		for (int i = 0; i < N; i++)
		{
			_v[i] -= vec[i];
		}
		return (*this);
	}

	Vec<T, N>& operator+=(const Vec<T, N>& vec)
	{
		for (int i = 0; i < N; i++)
		{
			_v[i] += vec[i];
		}
		return (*this);
	}

	Vec<T, N>& operator-=(const T& t)
	{
		for (int i = 0; i < N; i++)
		{
			_v[i] -= t;
		}
		return (*this);
	}

	Vec<T, N> operator+(const Vec<T, N>& vec)
	{
		Vec<T, N> tmp;
		for (int i = 0; i < N; i++)
		{
			tmp[i] = _v[i] + vec[i];
		}
		return (tmp);
	}

	Vec<T, N> operator+(const Vec<T, N>& vec) const
	{
		Vec<T, N> tmp;
		for (int i = 0; i < N; i++)
		{
			tmp[i] = _v[i] + vec[i];
		}
		return (tmp);
	}

	Vec<T, N> operator-(const Vec<T, N>& vec)
	{
		Vec<T, N> tmp;
		for (int i = 0; i < N; i++)
		{
			tmp[i] = _v[i] - vec[i];
		}
		return (tmp);
	}

	Vec<T, N> operator-(const Vec<T, N>& vec) const
	{
		Vec<T, N> tmp;
		for (int i = 0; i < N; i++)
		{
			tmp[i] = _v[i] - vec[i];
		}
		return (tmp);
	}

	Vec<T, N> operator/(const T& t)
	{
		Vec<T, N> tmp;
		for (int i = 0; i < N; i++)
		{
			tmp[i] = _v[i] / t;
		}
		return (tmp);
	}

	Vec<T, N> operator*(const T& t)
	{
		Vec<T, N> tmp;
		for (int i = 0; i < N; i++)
		{
			tmp[i] = _v[i] * t;
		}
		return (tmp);
	}

	Vec<T, N>& operator*=(const T& t)
	{
		for (int i = 0; i < N; i++)
		{
			_v[i] *= t;
		}
		return (*this);
	}

	Vec<T, N>& operator/=(const T& t)
	{
		for (int i = 0; i < N; i++)
		{
			_v[i] /= t;
		}
		return (*this);
	}

	Vec<T, N>& operator*=(const Vec<T, N>& vec)
	{
		for (int i = 0; i < N; i++)
		{
			_v[i] *= vec[i];
		}
		return (*this);
	}

	T sqrtMagnitude() const
	{
		T sum = 0;
		for (int i = 0; i < N; i++)
		{
			sum += _v[i] * _v[i];
		}
		return sum;
	}

	T magnitude() const
	{
		return sqrt(sqrtMagnitude());
	}

	Vec<T, N> normalize() const//归一化
	{
		Vec<T, N> tmp;
		T mag = magnitude();
		for (int i = 0; i < N; i++)
		{
			tmp[i] = mag ? _v[i] / mag : 0;
		}
		return tmp;
	}

	bool operator<(const Vec<T, N>& vec) const
	{
		for (int i = 0; i < N; i++) // 遍历
		{
			if (_v[i] < vec[i]) // 在前面的优先
			{
				return true;
			}
			else if (_v[i] > vec[i])
			{
				return false;
			}
		}
		return false;
	}

	template<int M>
	Vec<T, M> sub() const // 没测试
	{
		Vec<T, M> tmp;
		for (int i = 0; i < M; i++)
		{
			tmp[i] = _v[i];
		}
		return tmp;
	}

	const T* c_ptr() const
	{
		return _v;
	}

protected:
	T _v[N];
};

typedef Vec<float, 6> BBox;

typedef Vec<double, 2> double2;

typedef Vec<float, 4> float4;
typedef Vec<float, 3> float3;
typedef Vec<float, 2> float2;

typedef Vec<int, 4> int4;
typedef Vec<int, 3> int3;
typedef Vec<int, 2> int2;

_GIS_END

#endif
