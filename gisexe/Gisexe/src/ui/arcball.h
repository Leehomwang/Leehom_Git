#ifndef _ARCBALL_H
#define _ARCBALL_H

#include <math.h>
#include <stdlib.h>

#ifdef _DEBUG
# include "assert.h"
#else
# define assert(x) { }
#endif

//2维点
typedef union Tuple2f_t
{
	struct
	{
		float X, Y;
	} s;

	float T[2];
} Tuple2fT;     

//3维点
typedef union Tuple3f_t
{
	struct
	{
		float X, Y, Z;
	} s;

	float T[3];
} Tuple3fT;      

//4维点
typedef union Tuple4f_t
{
	struct
	{
		float X, Y, Z, W;
	} s;

	float T[4];
} Tuple4fT;      


//3x3矩阵
typedef union Matrix3f_t
{
	struct
	{
		//column major
		union { float M00; float XX; float SX; };  
		union { float M10; float XY;             };  
		union { float M20; float XZ;             };  
		union { float M01; float YX;             };  
		union { float M11; float YY; float SY; };  
		union { float M21; float YZ;             };  
		union { float M02; float ZX;             };  
		union { float M12; float ZY;             };  
		union { float M22; float ZZ; float SZ; };  
	} s;

	float M[9];
} Matrix3fT;    

//4x4矩阵
typedef union Matrix4f_t
{
	struct
	{
		//column major
		union { float M00; float XX; float SX; };  
		union { float M10; float XY;             };  
		union { float M20; float XZ;             };  
		union { float M30; float XW;             };  
		union { float M01; float YX;             };  
		union { float M11; float YY; float SY; };  
		union { float M21; float YZ;             };  
		union { float M31; float YW;             };  
		union { float M02; float ZX;             };  
		union { float M12; float ZY;             };  
		union { float M22; float ZZ; float SZ; };  
		union { float M32; float ZW;             };  
		union { float M03; float TX;             };  
		union { float M13; float TY;             };  
		union { float M23; float TZ;             };  
		union { float M33; float TW; float SW; };  
	} s;

	float M[16];
} Matrix4fT;    

//定义类型的别名
#define Point2fT    Tuple2fT   
#define Quat4fT     Tuple4fT   
#define Vector2fT   Tuple2fT   
#define Vector3fT   Tuple3fT   
#define FuncSqrt    sqrtf
# define Epsilon 1.0e-5

//2维点相加
inline
static void Point2fAdd(Point2fT* NewObj, const Tuple2fT* t1)
{
	assert(NewObj && t1);

	NewObj->s.X += t1->s.X;
	NewObj->s.Y += t1->s.Y;
}

//2维点相减
inline
static void Point2fSub(Point2fT* NewObj, const Tuple2fT* t1)
{
	assert(NewObj && t1);

	NewObj->s.X -= t1->s.X;
	NewObj->s.Y -= t1->s.Y;
}

//3维点矢积
inline
static void Vector3fCross(Vector3fT* NewObj, const Vector3fT* v1, const Vector3fT* v2)
{
	Vector3fT Result; 

	assert(NewObj && v1 && v2);

	Result.s.X = (v1->s.Y * v2->s.Z) - (v1->s.Z * v2->s.Y);
	Result.s.Y = (v1->s.Z * v2->s.X) - (v1->s.X * v2->s.Z);
	Result.s.Z = (v1->s.X * v2->s.Y) - (v1->s.Y * v2->s.X);

	*NewObj = Result;
}

//3维点点积
inline
static float Vector3fDot(const Vector3fT* NewObj, const Vector3fT* v1)
{
	assert(NewObj && v1);

	return  (NewObj->s.X * v1->s.X) +
		(NewObj->s.Y * v1->s.Y) +
		(NewObj->s.Z * v1->s.Z);
}

//3维点的长度的平方
inline
static float Vector3fLengthSquared(const Vector3fT* NewObj)
{
	assert(NewObj);

	return  (NewObj->s.X * NewObj->s.X) +
		(NewObj->s.Y * NewObj->s.Y) +
		(NewObj->s.Z * NewObj->s.Z);
}

//3维点的长度
inline
static float Vector3fLength(const Vector3fT* NewObj)
{
	assert(NewObj);

	return FuncSqrt(Vector3fLengthSquared(NewObj));
}

//设置3x3矩阵为0矩阵
inline
static void Matrix3fSetZero(Matrix3fT* NewObj)
{
	NewObj->s.M00 = NewObj->s.M01 = NewObj->s.M02 = 
		NewObj->s.M10 = NewObj->s.M11 = NewObj->s.M12 = 
		NewObj->s.M20 = NewObj->s.M21 = NewObj->s.M22 = 0.0f;
}

//设置3x3矩阵为单位矩阵
inline
static void Matrix3fSetIdentity(Matrix3fT* NewObj)
{
	Matrix3fSetZero(NewObj);

	NewObj->s.M00 = 
		NewObj->s.M11 = 
		NewObj->s.M22 = 1.0f;
}

//从四元数设置旋转矩阵
inline
static void Matrix3fSetRotationFromQuat4f(Matrix3fT* NewObj, const Quat4fT* q1)
{
	float n, s;
	float xs, ys, zs;
	float wx, wy, wz;
	float xx, xy, xz;
	float yy, yz, zz;

	assert(NewObj && q1);

	n = (q1->s.X * q1->s.X) + (q1->s.Y * q1->s.Y) + (q1->s.Z * q1->s.Z) + (q1->s.W * q1->s.W);
	s = (n > 0.0f) ? (2.0f / n) : 0.0f;

	xs = q1->s.X * s;  ys = q1->s.Y * s;  zs = q1->s.Z * s;
	wx = q1->s.W * xs; wy = q1->s.W * ys; wz = q1->s.W * zs;
	xx = q1->s.X * xs; xy = q1->s.X * ys; xz = q1->s.X * zs;
	yy = q1->s.Y * ys; yz = q1->s.Y * zs; zz = q1->s.Z * zs;

	NewObj->s.XX = 1.0f - (yy + zz); NewObj->s.YX =         xy - wz;  NewObj->s.ZX =         xz + wy;
	NewObj->s.XY =         xy + wz;  NewObj->s.YY = 1.0f - (xx + zz); NewObj->s.ZY =         yz - wx;
	NewObj->s.XZ =         xz - wy;  NewObj->s.YZ =         yz + wx;  NewObj->s.ZZ = 1.0f - (xx + yy);
}

//3x3矩阵相乘
inline
static void Matrix3fMulMatrix3f(Matrix3fT* NewObj, const Matrix3fT* m1)
{
	Matrix3fT Result; 

	assert(NewObj && m1);

	Result.s.M00 = (NewObj->s.M00 * m1->s.M00) + (NewObj->s.M01 * m1->s.M10) + (NewObj->s.M02 * m1->s.M20);
	Result.s.M01 = (NewObj->s.M00 * m1->s.M01) + (NewObj->s.M01 * m1->s.M11) + (NewObj->s.M02 * m1->s.M21);
	Result.s.M02 = (NewObj->s.M00 * m1->s.M02) + (NewObj->s.M01 * m1->s.M12) + (NewObj->s.M02 * m1->s.M22);

	Result.s.M10 = (NewObj->s.M10 * m1->s.M00) + (NewObj->s.M11 * m1->s.M10) + (NewObj->s.M12 * m1->s.M20);
	Result.s.M11 = (NewObj->s.M10 * m1->s.M01) + (NewObj->s.M11 * m1->s.M11) + (NewObj->s.M12 * m1->s.M21);
	Result.s.M12 = (NewObj->s.M10 * m1->s.M02) + (NewObj->s.M11 * m1->s.M12) + (NewObj->s.M12 * m1->s.M22);

	Result.s.M20 = (NewObj->s.M20 * m1->s.M00) + (NewObj->s.M21 * m1->s.M10) + (NewObj->s.M22 * m1->s.M20);
	Result.s.M21 = (NewObj->s.M20 * m1->s.M01) + (NewObj->s.M21 * m1->s.M11) + (NewObj->s.M22 * m1->s.M21);
	Result.s.M22 = (NewObj->s.M20 * m1->s.M02) + (NewObj->s.M21 * m1->s.M12) + (NewObj->s.M22 * m1->s.M22);

	*NewObj = Result;
}

//4x4矩阵相乘
inline
static void Matrix4fSetRotationScaleFromMatrix4f(Matrix4fT* NewObj, const Matrix4fT* m1)
{
	assert(NewObj && m1);

	NewObj->s.XX = m1->s.XX; NewObj->s.YX = m1->s.YX; NewObj->s.ZX = m1->s.ZX;
	NewObj->s.XY = m1->s.XY; NewObj->s.YY = m1->s.YY; NewObj->s.ZY = m1->s.ZY;
	NewObj->s.XZ = m1->s.XZ; NewObj->s.YZ = m1->s.YZ; NewObj->s.ZZ = m1->s.ZZ;
}

//进行矩阵的奇异值分解，旋转矩阵被保存到rot3和rot4中，返回矩阵的缩放因子
inline
static float Matrix4fSVD(const Matrix4fT* NewObj, Matrix3fT* rot3, Matrix4fT* rot4)
{
	float s, n;

	assert(NewObj);

	s = FuncSqrt(
		( (NewObj->s.XX * NewObj->s.XX) + (NewObj->s.XY * NewObj->s.XY) + (NewObj->s.XZ * NewObj->s.XZ) + 
		(NewObj->s.YX * NewObj->s.YX) + (NewObj->s.YY * NewObj->s.YY) + (NewObj->s.YZ * NewObj->s.YZ) +
		(NewObj->s.ZX * NewObj->s.ZX) + (NewObj->s.ZY * NewObj->s.ZY) + (NewObj->s.ZZ * NewObj->s.ZZ) ) / 3.0f );

	if (rot3)   
	{
		rot3->s.XX = NewObj->s.XX; rot3->s.XY = NewObj->s.XY; rot3->s.XZ = NewObj->s.XZ;
		rot3->s.YX = NewObj->s.YX; rot3->s.YY = NewObj->s.YY; rot3->s.YZ = NewObj->s.YZ;
		rot3->s.ZX = NewObj->s.ZX; rot3->s.ZY = NewObj->s.ZY; rot3->s.ZZ = NewObj->s.ZZ;

		n = 1.0f / FuncSqrt( (NewObj->s.XX * NewObj->s.XX) +
			(NewObj->s.XY * NewObj->s.XY) +
			(NewObj->s.XZ * NewObj->s.XZ) );
		rot3->s.XX *= n;
		rot3->s.XY *= n;
		rot3->s.XZ *= n;

		n = 1.0f / FuncSqrt( (NewObj->s.YX * NewObj->s.YX) +
			(NewObj->s.YY * NewObj->s.YY) +
			(NewObj->s.YZ * NewObj->s.YZ) );
		rot3->s.YX *= n;
		rot3->s.YY *= n;
		rot3->s.YZ *= n;

		n = 1.0f / FuncSqrt( (NewObj->s.ZX * NewObj->s.ZX) +
			(NewObj->s.ZY * NewObj->s.ZY) +
			(NewObj->s.ZZ * NewObj->s.ZZ) );
		rot3->s.ZX *= n;
		rot3->s.ZY *= n;
		rot3->s.ZZ *= n;
	}

	if (rot4)  
	{
		if (rot4 != NewObj)
		{
			Matrix4fSetRotationScaleFromMatrix4f(rot4, NewObj); 
		}


		n = 1.0f / FuncSqrt( (NewObj->s.XX * NewObj->s.XX) +
			(NewObj->s.XY * NewObj->s.XY) +
			(NewObj->s.XZ * NewObj->s.XZ) );
		rot4->s.XX *= n;
		rot4->s.XY *= n;
		rot4->s.XZ *= n;

		n = 1.0f / FuncSqrt( (NewObj->s.YX * NewObj->s.YX) +
			(NewObj->s.YY * NewObj->s.YY) +
			(NewObj->s.YZ * NewObj->s.YZ) );
		rot4->s.YX *= n;
		rot4->s.YY *= n;
		rot4->s.YZ *= n;

		n = 1.0f / FuncSqrt( (NewObj->s.ZX * NewObj->s.ZX) +
			(NewObj->s.ZY * NewObj->s.ZY) +
			(NewObj->s.ZZ * NewObj->s.ZZ) );
		rot4->s.ZX *= n;
		rot4->s.ZY *= n;
		rot4->s.ZZ *= n;
	}

	return s;
}

//从3x3矩阵变为4x4的旋转矩阵
inline
static void Matrix4fSetRotationScaleFromMatrix3f(Matrix4fT* NewObj, const Matrix3fT* m1)
{
	assert(NewObj && m1);

	NewObj->s.XX = m1->s.XX; NewObj->s.YX = m1->s.YX; NewObj->s.ZX = m1->s.ZX;
	NewObj->s.XY = m1->s.XY; NewObj->s.YY = m1->s.YY; NewObj->s.ZY = m1->s.ZY;
	NewObj->s.XZ = m1->s.XZ; NewObj->s.YZ = m1->s.YZ; NewObj->s.ZZ = m1->s.ZZ;
}

//4x4矩阵的与标量的乘积
inline
static void Matrix4fMulRotationScale(Matrix4fT* NewObj, float scale)
{
	assert(NewObj);

	NewObj->s.XX *= scale; NewObj->s.YX *= scale; NewObj->s.ZX *= scale;
	NewObj->s.XY *= scale; NewObj->s.YY *= scale; NewObj->s.ZY *= scale;
	NewObj->s.XZ *= scale; NewObj->s.YZ *= scale; NewObj->s.ZZ *= scale;
}

//设置旋转矩阵
inline
static void Matrix4fSetRotationFromMatrix3f(Matrix4fT* NewObj, const Matrix3fT* m1)
{
	float scale;

	assert(NewObj && m1);

	scale = Matrix4fSVD(NewObj, NULL, NULL);

	Matrix4fSetRotationScaleFromMatrix3f(NewObj, m1);
	Matrix4fMulRotationScale(NewObj, scale);
}



typedef class ArcBall_t
{
protected:
	//把二维点映射到三维点
	inline
		void _mapToSphere(const Point2fT* NewPt, Vector3fT* NewVec) const;

public:
	//构造/析构函数
	ArcBall_t(float NewWidth = 640.0f, float NewHeight = 480.0f);
	~ArcBall_t() { };

	//设置边界
	inline
		void    setBounds(float NewWidth, float NewHeight)
	{
		assert((NewWidth > 1.0f) && (NewHeight > 1.0f));

		//设置长宽的调整因子
		this->AdjustWidth  = 1.0f / ((NewWidth  - 1.0f) * 0.5f);
		this->AdjustHeight = 1.0f / ((NewHeight - 1.0f) * 0.5f);
	}

	//鼠标点击
	void    click(const Point2fT* NewPt);

	//鼠标拖动计算旋转
	void    drag(const Point2fT* NewPt, Quat4fT* NewRot);

protected:
	Vector3fT   StVec;          //保存鼠标点击的坐标
	Vector3fT   EnVec;          //保存鼠标拖动的坐标
	float     AdjustWidth;    //宽度的调整因子
	float     AdjustHeight;   //长度的调整因子

} ArcBall;

#endif