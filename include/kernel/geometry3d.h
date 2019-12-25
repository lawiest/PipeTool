#pragma once
#include "../utility/preconfig.h"
#include "geometry.h"
KERNEL_NS
  

/// \brief 二维矢量对象
template<class T>
struct GsVec2T
{
public:

	/// \brief 数据类型
	typedef T value_type;
	/// \brief 数据类型
	value_type m_v[2];


	/// \brief 缺省构造
	GsVec2T() { m_v[0] = 0.0; m_v[1] = 0.0; }
	/// \brief 值构造
	GsVec2T(value_type x, value_type y) { m_v[0] = x; m_v[1] = y; }

	/// \brief 等于
	bool operator == (const GsVec2T<T>& v) const { return m_v[0] == v.m_v[0] && m_v[1] == v.m_v[1]; }
	/// \brief 不等
	bool operator != (const GsVec2T<T>& v) const { return m_v[0] != v.m_v[0] || m_v[1] != v.m_v[1]; }
	/// \brief 小于
	bool operator <  (const GsVec2T<T>& v) const
	{
		if (m_v[0]<v.m_v[0]) return true;
		else if (m_v[0]>v.m_v[0]) return false;
		else return (m_v[1]<v.m_v[1]);
	}
	/// \brief 数据指针
	value_type * Ptr() { return m_v; }
	/// \brief 数据指针
	const value_type * Ptr() const { return m_v; }

	/// \brief 设置值
	void Set(value_type x, value_type y) { m_v[0] = x; m_v[1] = y; }
	/// \brief 设置值
	void Set(const GsVec2T<T>& rhs) { m_v[0] = rhs.m_v[0]; m_v[1] = rhs.m_v[1]; }

	/// \brief []访问符
	value_type & operator [] (int i) { return m_v[i]; }
	/// \brief []访问符
	value_type operator [] (int i) const { return m_v[i]; }

	/// \brief  获取x
	value_type & X() { return m_v[0]; }
	/// \brief  获取y
	value_type & Y() { return m_v[1]; }

	/// \brief  获取x
	value_type X() const { return m_v[0]; }
	/// \brief  获取y
	value_type Y() const { return m_v[1]; }

	/// \brief  是否有效
	bool Valid() const { return !IsNaN(); }
	/// \brief  是否无效
	bool IsNaN() const { return Utility::GsMath::IsNaN(m_v[0]) || Utility::GsMath::IsNaN(m_v[1]); }
	/// \brief  是否有效
	operator bool()const { return Valid(); }

	/// \brief  点积
	value_type Dot(const GsVec2T<T>& rhs) const
	{
		return m_v[0] * rhs.m_v[0] + m_v[1] * rhs.m_v[1];
	}
	/// \brief  点积
	value_type operator * (const GsVec2T<T>& rhs) const
	{
		return Dot(rhs);
	}


	//// \brief  乘
	const GsVec2T<T> operator * (value_type rhs) const
	{
		return GsVec2T<T>(m_v[0] * rhs, m_v[1] * rhs);
	} 

	//// \brief  乘
	GsVec2T<T>& operator *= (value_type rhs)
	{
		m_v[0] *= rhs;
		m_v[1] *= rhs;
		return *this;
	}

	//// \brief  乘
	GsVec2T<T>& operator *= (const GsVec2T<T>& rhs)
	{
		m_v[0] *= rhs[0];
		m_v[1] *= rhs[1];
		return *this;
	}

	//// \brief  除
	const GsVec2T<T> operator / (value_type rhs) const
	{
		return GsVec2T<T>(m_v[0] / rhs, m_v[1] / rhs);
	}
	//// \brief  除
	const GsVec2T<T> operator / (const  GsVec2T<T>& rhs) const
	{
		return GsVec2T<T>(m_v[0] / rhs[1], m_v[1] / rhs[1]);
	}


	//// \brief  除
	GsVec2T<T>& operator /= (value_type rhs)
	{
		m_v[0] /= rhs;
		m_v[1] /= rhs;
		return *this;
	}
	//// \brief  除
	GsVec2T<T>& operator /= (const GsVec2T<T>& rhs)
	{
		m_v[0] /= rhs[0];
		m_v[1] /= rhs[1];
		return *this;
	}


	//// \brief  加
	const GsVec2T<T> operator + (const GsVec2T<T>& rhs) const
	{
		return Vec2f(m_v[0] + rhs.m_v[0], m_v[1] + rhs.m_v[1]);
	}

	//// \brief  加
	GsVec2T<T>& operator += (const GsVec2T<T>& rhs)
	{
		m_v[0] += rhs.m_v[0];
		m_v[1] += rhs.m_v[1];
		return *this;
	}

	//// \brief  减
	const GsVec2T<T> operator - (const GsVec2T<T>& rhs) const
	{
		return GsVec2T<T>(m_v[0] - rhs.m_v[0], m_v[1] - rhs.m_v[1]);
	}

	//// \brief  减
	GsVec2T<T> & operator -= (const GsVec2T<T> & rhs)
	{
		m_v[0] -= rhs.m_v[0];
		m_v[1] -= rhs.m_v[1];
		return *this;
	}

	//// \brief  减
	const GsVec2T<T>  operator - () const
	{
		return GsVec2T<T>(-_v[0], -_v[1]);
	}

	//// \brief  长度
	value_type Length() const
	{
		return sqrt(m_v[0] * m_v[0] + m_v[1] * m_v[1]);
	}

	//// \brief  长度的平方
	value_type Length2(void) const
	{
		return m_v[0] * m_v[0] + m_v[1] * m_v[1];
	}
	//// \brief  正规化
	value_type Normalize()
	{
		value_type norm = Length();
		if (norm>0.0)
		{
			value_type inv = 1.0f / norm;
			m_v[0] *= inv;
			m_v[1] *= inv;
		}
		return(norm);
	}

	//// \brief  复合
	GsVec2T<T> Multiply(const GsVec2T<T>& rhs)
	{
		return GsVec2T<T>(m_v[0] * rhs[0], m_v[1] * rhs[1]);
	}

	GsVec2T<T> Divide(const GsVec2T<T>& rhs)
	{
		return GsVec2T<T>(m_v[0] / rhs[0], m_v[1] / rhs[1]);
	}
};   

/// \brief 双精度矢量点
typedef GsVec2T<double> GsVec2D;
/// \brief 单精度矢量点
typedef GsVec2T<float> GsVec2F;

/// \brief 缺省矢量点为单精度点
typedef GsVec2T<float> GsVec2;


template<class T>
struct GsVec3T
{
	/// \brief 矢量数据类型
	typedef T value_type;

	/// \brief 矢量数据成员
	value_type m_v[3];

	/// \brief 缺省构造
	GsVec3T() { m_v[0] = 0.0f; m_v[1] = 0.0f; m_v[2] = 0.0f; }
	/// \brief 构造
	GsVec3T(value_type x, value_type y, value_type z) { m_v[0] = x; m_v[1] = y; m_v[2] = z; }

	/// \brief 从面的三个点构造，计算法线
	GsVec3T(const GsVec3T<T>& a, const GsVec3T<T>& b, const GsVec3T<T>& c) 
	{
		*this = (b - a).Cross(c - b);
		Normalize();
	}

	/// \brief 二维构造
	GsVec3T(const GsRawPoint& v2, value_type zz)
	{
		m_v[0] = v2.X;
		m_v[1] = v2.Y;
		m_v[2] = zz;
	}

	/// \brief 相等
	bool operator == (const GsVec3T<T>& v) const { return m_v[0] == v.m_v[0] && m_v[1] == v.m_v[1] && m_v[2] == v.m_v[2]; }
	/// \brief 不等
	bool operator != (const GsVec3T<T>& v) const { return m_v[0] != v.m_v[0] || m_v[1] != v.m_v[1] || m_v[2] != v.m_v[2]; }
	/// \brief 小于
	bool operator <  (const GsVec3T<T>& v) const
	{
		if (m_v[0]<v.m_v[0]) return true;
		else if (m_v[0]>v.m_v[0]) return false;
		else if (m_v[1]<v.m_v[1]) return true;
		else if (m_v[1]>v.m_v[1]) return false;
		else return (m_v[2]<v.m_v[2]);
	}
	/// \brief 数据指针
	value_type* Ptr() { return m_v; }
	/// \brief 常数数据指针
	const value_type* Ptr() const { return m_v; }
	/// \brief 设置值
	void Set(value_type x, value_type y, value_type z)
	{
		m_v[0] = x; m_v[1] = y; m_v[2] = z;
	}
	/// \brief 赋值
	void Set(const GsVec3T<T>& rhs)
	{
		m_v[0] = rhs.m_v[0]; m_v[1] = rhs.m_v[1]; m_v[2] = rhs.m_v[2];
	}
	/// \brief []操作操作符
	value_type& operator [] (int i) { return m_v[i]; }
	/// \brief []操作操作符
	value_type operator [] (int i) const { return m_v[i]; }
	/// \brief X值
	value_type& X() { return m_v[0]; }
	/// \brief Y值
	value_type& Y() { return m_v[1]; }
	/// \brief Z值
	value_type& Z() { return m_v[2]; }

	/// \brief X值
	value_type X() const { return m_v[0]; }
	/// \brief Y值
	value_type Y() const { return m_v[1]; }
	/// \brief Z值
	value_type Z() const { return m_v[2]; }

	/// \brief 是否有效
	bool Valid() const { return !IsNaN(); }
	/// \brief 是否无效
	bool IsNaN() const { return Utility::GsMath::IsNaN(m_v[0]) || Utility::GsMath::IsNaN(m_v[1]) || Utility::GsMath::IsNaN(m_v[2]); }
	operator bool()const { return Valid(); }

	/// \brief 点积
	value_type Dot(const GsVec3T<T>& rhs) const
	{
		return m_v[0] * rhs.m_v[0] + m_v[1] * rhs.m_v[1] + m_v[2] * rhs.m_v[2];
	}
	/// \brief 点积
	value_type operator * (const GsVec3T<T>& rhs) const
	{
		return Dot(rhs);
	}

	/// \brief 叉积
	const GsVec3T<T> Cross(const GsVec3T<T>& rhs) const
	{
		return GsVec3T<T>(m_v[1] * rhs.m_v[2] - m_v[2] * rhs.m_v[1],
			m_v[2] * rhs.m_v[0] - m_v[0] * rhs.m_v[2],
			m_v[0] * rhs.m_v[1] - m_v[1] * rhs.m_v[0]);
	}


	/// \brief 叉积
	const GsVec3T<T> operator ^ (const GsVec3T<T>& rhs) const
	{
		return Cross(rhs);
	}

	/// \brief 乘
	const GsVec3T<T> operator * (value_type rhs) const
	{
		return GsVec3T<T>(m_v[0] * rhs, m_v[1] * rhs, m_v[2] * rhs);
	} 

	/// \brief *=
	GsVec3T<T>& operator *= (value_type rhs)
	{
		m_v[0] *= rhs;
		m_v[1] *= rhs;
		m_v[2] *= rhs;
		return *this;
	}
	/// \brief *=
	GsVec3T<T>& operator *= (const GsVec3T<T>& rhs)
	{
		m_v[0] *= rhs[0];
		m_v[1] *= rhs[1];
		m_v[2] *= rhs[2];
		return *this;
	}

	/// \brief 除
	const GsVec3T<T> operator / (value_type rhs) const
	{
		return GsVec3T<T>(m_v[0] / rhs, m_v[1] / rhs, m_v[2] / rhs);
	}
	/// \brief 除
	const GsVec3T<T> operator / (const GsVec3T<T>& rhs) const
	{
		return GsVec3T<T>(m_v[0] / rhs[0], m_v[1] / rhs[1], m_v[2] / rhs[2]);
	}
	/// \brief 除
	GsVec3T<T>& operator /= (value_type rhs)
	{
		m_v[0] /= rhs;
		m_v[1] /= rhs;
		m_v[2] /= rhs;
		return *this;
	}
	/// \brief 除
	GsVec3T<T>& operator /= (const GsVec3T<T>& rhs)
	{
		m_v[0] /= rhs[0];
		m_v[1] /= rhs[1];
		m_v[2] /= rhs[2];
		return *this;
	}

	/// \brief 加
	const GsVec3T<T> operator + (const GsVec3T<T>& rhs) const
	{
		return GsVec3T<T>(m_v[0] + rhs.m_v[0], m_v[1] + rhs.m_v[1], m_v[2] + rhs.m_v[2]);
	}

	/// \brief 加
	GsVec3T<T>& operator += (const GsVec3T<T>& rhs)
	{
		m_v[0] += rhs.m_v[0];
		m_v[1] += rhs.m_v[1];
		m_v[2] += rhs.m_v[2];
		return *this;
	}

	/// \brief 减
	const GsVec3T<T> operator - (const GsVec3T<T>& rhs) const
	{
		return GsVec3T<T>(m_v[0] - rhs.m_v[0], m_v[1] - rhs.m_v[1], m_v[2] - rhs.m_v[2]);
	}

	/// \brief 减
	GsVec3T<T>& operator -= (const GsVec3T<T>& rhs)
	{
		m_v[0] -= rhs.m_v[0];
		m_v[1] -= rhs.m_v[1];
		m_v[2] -= rhs.m_v[2];
		return *this;
	}

	/// \brief 取反
	const GsVec3T<T> operator - () const
	{
		return GsVec3T<T>(-_v[0], -_v[1], -_v[2]);
	}

	/// \brief 长度
	value_type Length() const
	{
		return sqrt(m_v[0] * m_v[0] + m_v[1] * m_v[1] + m_v[2] * m_v[2]);
	}

	/// \brief 长度平方
	value_type Length2() const
	{
		return m_v[0] * m_v[0] + m_v[1] * m_v[1] + m_v[2] * m_v[2];
	}

	/// \brief 正规化
	value_type Normalize()
	{
		value_type norm = Length();
		if (norm>0.0)
		{
			value_type inv = 1.0 / norm;
			m_v[0] *= inv;
			m_v[1] *= inv;
			m_v[2] *= inv;
		}
		return(norm);
	}

	/// \brief 复合乘
	GsVec3T<T> Multiply(const GsVec3T<T>& rhs)
	{
		return GsVec3T<T>(m_[0] * rhs[0], m_[1] * rhs[1], m_[2] * rhs[2]);
	}
	/// \brief 复合除 
	GsVec3T<T> Divide(const GsVec3T<T>& rhs)
	{
		return GsVec3T<T>(m_[0] / rhs[0], m_[1] / rhs[1], m_[2] / rhs[2]);
	}

};

/// \brief 双精度矢量点
typedef GsVec3T<double> GsVec3D;
/// \brief 单精度矢量点
typedef GsVec3T<float> GsVec3F;

/// \brief 缺省矢量点为单精度点
typedef GsVec3T<float> GsVec3;
KERNEL_ENDNS