#pragma once
#include <preconfig.h>
#include <object.h>

#include <geodatabase.h> 
#include <timer.h>

KERNEL_NS
/// \brief 时相查询方式,通过给GsTemporalTileClass 设置不同的查询方式得到不同的时相浏览效果
enum GsTemporalQueryType
{
	/// \brief 查看当前时相
	eOnTime,

	/// \brief 追溯方式查看当前时相
	eFromTime,
};


/// \brief 时相信息
struct GS_API GsTemporalItem
{
	/// \brief 时相名称
	Utility::GsString	TemporalName;
	/// \brief 开始时间
	Utility::GsDateTime	StartTime;
	/// \brief 结束时间
	Utility::GsDateTime	EndTime;

	/// \brief 注册的数据集名称
	Utility::GsString			TileClassName;
	/// \brief 范围索引
	Kernel::GsIndexGeometryPtr	GeometryIndex;
	/// \brief 范围
	Kernel::GsGeometryPtr		Geometry;
	/// \brief 瓦片数据集
	Kernel::GsTileClassPtr		TileClass;

	/// \brief 默认构造函数
	GsTemporalItem();
	/// \brief 通过名称搜索一个已经注册的瓦片数据集
	/// \param const char* Name 时相名称
	/// \param StartTime 开始时间
	/// \param EndTime 结束时间
	/// \param Name 
	GsTemporalItem(const char* Name, const Utility::GsDateTime & StartTime, const Utility::GsDateTime & EndTime);

	/// \brief 通过名称搜索一个已经注册的瓦片数据集
	/// \param const char* Name 时相名称
	/// \param StartTime 开始时间
	/// \param EndTime 结束时间
	/// \param Name 
	/// \param Utility::GsString 
	GsTemporalItem(const char* Name, const Utility::GsDateTime & StartTime
		, const Utility::GsDateTime & EndTime, Utility::GsString, Kernel::GsIndexGeometry*, Kernel::GsTileClass*) {}

	/// \brief 拷贝构造
	/// \param other 
	GsTemporalItem(const  GsTemporalItem & other);
};

typedef Utility::GsVector<GsTemporalItem> TemporalItemV;
typedef Utility::GsPair<Utility::GsString, TemporalItemV> TemporalItemVP;
typedef Utility::GsVector<TemporalItemVP>  TemporalColltion;

/// \brief 时相数据元信息
struct GS_API GsTemporalTileClassInfo
{
	long long OID;
	Utility::GsString Name;
	Kernel::GsFeatureType FeatureType;
	TemporalColltion TemporalList;

	GsTemporalTileClassInfo();
	/// \brief 
	/// \param id 
	/// \param strName 
	/// \param eType 
	GsTemporalTileClassInfo(long long id, const Utility::GsString & strName, Kernel::GsFeatureType eType);
	/// \brief 
	/// \param other 
	GsTemporalTileClassInfo(const GsTemporalTileClassInfo& other);
	~GsTemporalTileClassInfo();
};
/// \brief 多时相数据库类厂
class GS_API GsTemporalDatabaseFactory :public GsGeoDatabaseFactory
{
public:
	GsTemporalDatabaseFactory();
	~GsTemporalDatabaseFactory();
	/// \brief 根据数据库连接信息打开一个空间数据库
	/// \param connProperty 数据库连接信息
	/// \return 返回空间数据库对象实例或者空
	virtual GsGeoDatabasePtr Open(const GsConnectProperty & connProperty) override;
};
GS_SMARTER_PTR(GsTemporalDatabaseFactory);
/// \brief 多时相瓦片数据集接口类
class GS_API GsTemporalTileClass :public GsTileClass
{
protected:
	/// \brief 查询时间点
	Utility::GsDateTime m_QueryTimePoint;
	/// \brief 查询方式,追索还是查看当前时相
	GsTemporalQueryType m_QueryType;

protected:
	/// \brief 
	/// \param pDB 
	GsTemporalTileClass(GsGeoDatabase* pDB);
public:
	/// \brief 析构函数
	~GsTemporalTileClass();

	/// \brief 创建时相
	/// \param TemporalName 时相名称
	/// \param StartDate 开始时间
	/// \param EndDate 结束时间
	/// \return bool 是否创建成功
	virtual bool CreateTemporal(const char *TemporalName, const Utility::GsDateTime& StartDate, const  Utility::GsDateTime& EndDate) = 0;
	/// \brief 删除时相
	/// \param TemporalName 时相名称
	/// \return bool 是否删除成功
	virtual bool DeleteTemporal(const char *TemporalName) = 0;
	/// \brief 查询时相时间范围
	/// \param TemporalName 时相名称
	/// \param StartDate, 开始时间
	/// \param EndDate ,结束时间
	/// \return bool 是否查询成功
	virtual bool QueryTemporalDate(const char *TemporalName, Utility::GsDateTime& StartDate, Utility::GsDateTime &EndDate) = 0;
	/// \brief 注册瓦片数据集到指定时相
	/// \param TemporalName 时相名称
	/// \param TileClass 瓦片数据集
	/// \param pGeo 注册的范围,此范围将用于追溯查询
	/// \return bool 是否成功
	virtual bool RegisterTileClass(const char * TemporalName, GsTileClass * TileClass, GsGeometry* pGeo) = 0;
	/// \brief 注销瓦片数据集
	/// \param TileClass 瓦片数据集
	/// \param TemporalName 时相名称
	/// \return bool 是否成功
	virtual bool UnRegisterTileClass(GsTileClass * TileClass, const char * TemporalName) = 0;
	/// \brief 注销瓦片数据集
	/// \param TileClass 瓦片数据集名称
	/// \param TemporalName 时相名称
	/// \return bool 是否成功
	virtual bool UnRegisterTileClass(const char * TileClassName, const char * TemporalName) = 0;
	/// \brief 枚举时相名称
	/// \return GsVector<GsString> 
	virtual Utility::GsVector<Utility::GsString> EnumTemporalName() = 0;
	/// \brief 枚举时相下数据集名称
	/// \param TemporalName 时相名称
	/// \return GsVector<GsString> 
	virtual Utility::GsVector<Utility::GsString> EnumRegisterTileClassName(const char * TemporalName) = 0;
	/// \brief 设置查询类型
	/// \param eType 查询类型
	/// \return void
	virtual void QueryType(GsTemporalQueryType eType);
	/// \brief 获取查询类型
	/// \return void
	virtual GsTemporalQueryType QueryType();
	/// \brief 设置查询时间
	/// \param time 查询时间
	/// \return void
	virtual void QueryTimePoint(const Utility::GsDateTime & time);
	/// \brief 查询时间
	/// \return GsDateTime
	virtual Utility::GsDateTime QueryTimePoint();
	/// \brief 通过名称搜索一个已经注册的瓦片数据集
	/// \param strTlsName 瓦片数据集名称
	/// \return GsTileClass * 瓦片数据集
	virtual GsTileClassPtr FindTileClass(const char* strTlsName) = 0;

	/// \brief 获取瓦片数据集的范围索引
	/// \param TileClass 
	/// \return 
	virtual GsIndexGeometryPtr GeometryIndex(GsTileClass * TileClass) = 0;

	/// \brief 
	/// \return 
	virtual GsTemporalTileClassInfo TemporalTileClassInfo() = 0;
};
GS_SMARTER_PTR(GsTemporalTileClass);

KERNEL_ENDNS