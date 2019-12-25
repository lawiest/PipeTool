#pragma once
#include "../utility/preconfig.h"
#include <object.h>  
#include <vectorhelp.h>
#include <geometry.h>
#include <model.h>
KERNEL_NS 

	
/// \brief 粗查空间索引对象抽象基类
class GS_API GsSpatialIndexQuery:public Utility::GsRefObject
{
public:
	virtual ~GsSpatialIndexQuery();
	/// \brief 根据矩形范围查询相交对象id
	/// \param box 要检索的矩形范围
	/// \param vecResult 返回和检索矩形相交的对象id
	/// \return 返回是否检索到对象
	virtual bool Query(const GsBox& box, Utility::GsVector<long long> &vecResult) = 0;
};
/// \brief GsSpatialIndexQueryPtr
GS_SMARTER_PTR(GsSpatialIndexQuery);

/// \brief 支持修改的空间索引抽象基类
class GS_API GsSpatialIndexEdit:public GsSpatialIndexQuery
{
public:
	virtual ~GsSpatialIndexEdit();
	/// \brief 增加一个对象到空间索引
	/// \param box 要增加对象的box
	/// \param nID 要增加对象的id
	/// \return 增加是否成功
	virtual bool Add(const GsBox& box,int nID) = 0;
	/// \brief 从空间索引移除一个对象
	/// \param nID 要移除对象的id
	/// \return 移除是否成功
	virtual bool Remove(int nID) = 0;
};
/// \brief GsSpatialIndexEditPtr
GS_SMARTER_PTR(GsSpatialIndexEdit);

 
/// \brief 基于本地QIX文件的只读R树空间索引
class GS_API GsQIXFileSpatialIndex:public GsSpatialIndexQuery
{
	void* m_pQIXHandle;
public:
	/// \brief 从QIX文件名构造
	/// \param strQIXFile 
	GsQIXFileSpatialIndex(const char* strQIXFile);
	~GsQIXFileSpatialIndex();

	/// \brief 根据矩形范围查询相交对象id
	/// \param box 要检索的矩形范围
	/// \param vecResult 返回和检索矩形相交的对象id
	/// \return 返回是否检索到对象
	virtual bool Query(const GsBox& box, UTILITY_NAME::GsVector<long long> &vecResult);
	 
	/// \brief 查询多个维度
	/// \param minBound 维度最小的值
	/// \param maxBound 维度最大的值
	/// \param nDim 要检索的维度
	/// \param vecResult 查询结果
	/// \return 返回是否检索到对象
	virtual bool QueryMultiDimension(const double* minBound,const double* maxBound,int nDim, UTILITY_NAME::GsVector<long long> &vecResult);
	
};
/// \brief GsQIXFileSpatialIndexPtr
GS_SMARTER_PTR(GsQIXFileSpatialIndex);


/// \brief Geohash计算
class GS_API GsGeohash
{
	double m_xmin, m_ymin, m_xmax, m_ymax;
	static const int m_maxlen = 18;
	static const unsigned long long m_mask = 1ULL << 45;
	static const Utility::GsString m_lcdigits_;
	static const Utility::GsString m_ucdigits_;
	
	double m_shift; 
	double m_dx;
	double m_dy;
	double m_loneps;
	double m_lateps;

public:
	/// \brief 
	/// \param xmin 
	/// \param ymin 
	/// \param xmax 
	/// \param ymax 
	GsGeohash(double xmin =  -180.0, double ymin= -90.0, double xmax=180.0, double ymax = 90.0);

	/// \brief Geohash正算
	/// \param x 
	/// \param y 
	/// \param len 
	/// \return 
	Utility::GsString Forward(double x, double y, int len);
	
	/// \brief Geohash反算。从字符串计算位置
	/// \param[in] geohash the geohash.
	/// \param[out] x 点的x坐标
	/// \param[out] y 点的y坐标
	/// \param[out] len geohash的长度.
	/// \param[in] centerp 如果真（缺省）则返回geohash位置的中心否则返回西南角坐标
	/// \return 
	bool Reverse(const char* geohash, double&x, double &y, int& len, bool centerp = true);
};

/// \brief 瓦片Key索引对象
class GS_API GsTileKeyIndex:public UTILITY_NAME::GsRefObject
{
protected:
	GsTileKeyIndex();
public:
	virtual ~GsTileKeyIndex();
	
	/// \brief 重置索引为空
	virtual void Reset() = 0;

	/// \brief 顶层级别
	/// \return 
	virtual int TopLevel() = 0;
	/// \brief 底层级别
	/// \return 
	virtual int BottomLevel() = 0;
	
	/// \brief 增加一个瓦片Key到索引
	/// \param key 
	virtual void Add(const UTILITY_NAME::GsQuadKey& key) = 0;
	/// \brief 增加一个范围内的瓦片Key到索引
	/// \param level 
	/// \param startrow 
	/// \param startcol 
	/// \param endrow 
	/// \param endcol 
	/// \return 
	virtual int Add(int level,int startrow,int startcol,int endrow,int endcol);

	/// \brief 判断一个瓦片Key是否存在
	/// \param key 
	/// \return 
	virtual bool Exist(const UTILITY_NAME::GsQuadKey& key) = 0;

	/// \brief 删除一个瓦片Key
	/// \param key 
	/// \return 
	virtual bool Remove(const UTILITY_NAME::GsQuadKey& key) = 0;
	/// \brief 删除一个范围内的瓦片Key
	/// \param level 
	/// \param startrow 
	/// \param startcol 
	/// \param endrow 
	/// \param endcol 
	/// \return 
	virtual int Remove(int level, int startrow, int startcol, int endrow, int endcol);
	
	/// \brief 删除一个级别的所有的瓦片
	/// \param level 
	/// \return 
	virtual int Remove(int level) = 0;
};
GS_SMARTER_PTR(GsTileKeyIndex);


/// \brief 基于（RLE，run-length encoding）存储技术的瓦片索引。
class GS_API GsRLETileKeyIndex:public GsTileKeyIndex
{
	void* m_RLE;
public:
	GsRLETileKeyIndex();
	~GsRLETileKeyIndex();

	/// \brief 重置索引为空
	virtual void Reset();

	/// \brief 顶层级别
	/// \return 
	virtual int TopLevel();
	/// \brief 底层级别
	/// \return 
	virtual int BottomLevel();

	/// \brief 增加一个瓦片Key到索引
	/// \param key 
	virtual void Add(const UTILITY_NAME::GsQuadKey& key); 

	/// \brief 判断一个瓦片Key是否存在
	/// \param key 
	/// \return 
	virtual bool Exist(const UTILITY_NAME::GsQuadKey& key);

	/// \brief 删除一个瓦片Key
	/// \param key 
	/// \return 
	virtual bool Remove(const UTILITY_NAME::GsQuadKey& key); 

	/// \brief 删除一个级别的所有的瓦片
	/// \param level 
	/// \return 
	virtual int Remove(int level);

};
GS_SMARTER_PTR(GsRLETileKeyIndex);

KERNEL_ENDNS
