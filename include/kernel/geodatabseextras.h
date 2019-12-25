#pragma once
#include <preconfig.h>
#include <object.h>

#include <geodatabase.h> 
#include <timer.h>

KERNEL_NS
/// \brief 时相查询方式,通过给GsTemporalTileClass 设置不同的查询方式得到不同的时相浏览效果
enum GsTemporalQueryType
{
	eOnTime,//查看当前时相
	eFromTime,//追溯方式查看当前时相
};
/// \brief 多时相数据库类厂
class GS_API GsTemporalDatabaseFactory :public GsGeoDatabaseFactory
{
public:
	GsTemporalDatabaseFactory();
	~GsTemporalDatabaseFactory();
	/// \brief 根据数据库连接信息打开一个空间数据库
	///\param connProperty 数据库连接信息
	///\return 返回空间数据库对象实例或者空
	virtual GsGeoDatabasePtr Open(const GsConnectProperty & connProperty) override;
};
GS_SMARTER_PTR(GsTemporalDatabaseFactory);
/// \brief 多时相瓦片数据集接口类
class GS_API GsTemporalTileClass :public GsTileClass
{
protected:
	///\brief 查询时间点
	Utility::GsDateTime m_QueryTimePoint;
	///\brief 查询方式,追索还是查看当前时相
	GsTemporalQueryType m_QueryType;

protected:
	GsTemporalTileClass(GsGeoDatabase* pDB);
public:
	///\brief 析构函数
	~GsTemporalTileClass();

	///\brief 创建时相
	///\param const char * 时相名称
	///\param GsDateTime& StartDate, 开始时间
	///\param GsDateTime& EndDate ,结束时间
	///\return bool 是否创建成功
	virtual bool CreateTemporal(const char *TemporalName, const Utility::GsDateTime& StartDate, const  Utility::GsDateTime& EndDate) = 0;
	///\brief 删除时相
	///\param const char * 时相名称
	///\return bool 是否删除成功
	virtual bool DeleteTemporal(const char *TemporalName) = 0;
	///\brief 查询时相时间范围
	///\param const char * 时相名称
	///\param GsDateTime& StartDate, 开始时间
	///\param GsDateTime& EndDate ,结束时间
	///\return bool 是否查询成功
	virtual bool QueryTemporalDate(const char *TemporalName, Utility::GsDateTime& StartDate, Utility::GsDateTime &EndDate) = 0;
	///\brief 注册瓦片数据集到指定时相
	///\param const char * TemporalName 时相名称
	///\param GsTileClass * TileClass 瓦片数据集
	///\param GsGeometry* pGeo 注册的范围,此范围将用于追溯查询
	///\return bool 是否成功
	virtual bool RegisterTileClass(const char * TemporalName, GsTileClass * TileClass, GsGeometry* pGeo) = 0;
	///\brief 注销瓦片数据集
	///\param GsTileClass * TileClass 瓦片数据集
	///\param const char * TemporalName 时相名称
	///\return bool 是否成功
	virtual bool UnRegisterTileClass(GsTileClass * TileClass, const char * TemporalName) = 0;
	///\brief 注销瓦片数据集
	///\param GsTileClass * TileClass 瓦片数据集名称
	///\param const char * TemporalName 时相名称
	///\return bool 是否成功
	virtual bool UnRegisterTileClass(const char * TileClassName, const char * TemporalName) = 0;
	///\brief 枚举时相名称
	///\return GsVector<GsString> 
	virtual Utility::GsVector<Utility::GsString> EnumTemporalName() = 0;
	///\brief 枚举时相下数据集名称
	///\param const char * TemporalName 时相名称
	///\return GsVector<GsString> 
	virtual Utility::GsVector<Utility::GsString> EnumRegisterTileClassName(const char * TemporalName) = 0;
	/// \brief 设置查询类型
	///\param enumQueryType 查询类型
	///\return void
	virtual void QueryType(GsTemporalQueryType eType);
	/// \brief 获取查询类型
	///\return void
	virtual GsTemporalQueryType QueryType();
	/// \brief 设置查询时间
	///\param enumQueryType 查询时间
	///\return void
	virtual void QueryTimePoint(const Utility::GsDateTime & time);
	/// \brief 查询时间
	///\return GsDateTime
	virtual Utility::GsDateTime QueryTimePoint();
	/// \brief 通过名称搜索一个已经注册的瓦片数据集
	///\param const char* strTlsName 瓦片数据集名称
	///\return GsTileClass * 瓦片数据集
	virtual GsTileClassPtr FindTileClass(const char* strTlsName) = 0;

	/// \brief 获取瓦片数据集的范围索引
	virtual GsIndexGeometryPtr GeometryIndex(GsTileClass * TileClass) = 0;
};
GS_SMARTER_PTR(GsTemporalTileClass);
KERNEL_ENDNS