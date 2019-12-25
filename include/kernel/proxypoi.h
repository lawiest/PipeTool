#pragma once
#include <geodatabase.h>
#include <poi.h>

KERNEL_NS
class GsProxyPOIDatabase;

class GS_API GsProxyPOIDataRoom : public GsRefObject
{
public:
	/// \brief  获得数据库
	virtual Utility::GsSmarterPtr<GsProxyPOIDatabase> ProxyPOIDatabase() = 0;

	/// \brief  获得关联的矢量点数据
	virtual GsFeatureClassPtr FeatureClass() = 0;

	/// \brief  获得发布的瓦片数据
	virtual GsTileClassPtr PublishTileClass() = 0;

	/// \brief  获得元数据信息
	virtual GsPlaceNameMetadata Metadata() = 0;

	/// \brief  设置元数据信息
	virtual void Metadata(const GsPlaceNameMetadata& data) = 0;

	/// \brief  数量
	virtual int Count() = 0;

	/// \brief  根据索引查询
	virtual bool QueryClassify(int nIndex, GsPlaceNameClassify& data) = 0;

	/// \brief  根据分类值
	virtual bool QueryClassify(const char* value, GsPlaceNameClassify& data) = 0;

	/// \brief 增加或替换分类值
	virtual bool SaveClassify(GsPlaceNameClassify& data) = 0;

	/// \brief 删除分类值
	virtual bool DeleteClassify(const char* value) = 0;

	/// \brief 删除数据集
	virtual bool Delete() = 0;
};
GS_SMARTER_PTR(GsProxyPOIDataRoom)

class GS_API GsProxyPOIDatabase : public GsRefObject
{
public:
	/// \brief 枚举POI数据集名称
	virtual void DataRoomNames(UTILITY_NAME::GsVector<Utility::GsString>& vecName) = 0;

	/// \brief  打开POI数据
	virtual GsProxyPOIDataRoomPtr Open(const char* name) = 0;

	/// \brief  创建数据集
	virtual GsProxyPOIDataRoomPtr Create(GsPlaceNameMetadata& metadata) = 0;

	/// \brief  获取图标库
	virtual GsIconLibrary* IconLibrary() = 0;

	/// \brief  获取符号库
	virtual GsPlaceNameSymbolLibrary* SymbolLibrary() = 0;

};
GS_SMARTER_PTR(GsProxyPOIDatabase);

/// \brief Oracle POI数据库实现
class GS_API GsOracleProxyPOIDatabase :public GsProxyPOIDatabase
{
private :
	Utility::GsSmarterPtr<GsProxyPOIDatabase> m_PtrProxyPOIDatabaseImpl;
public:
	GsOracleProxyPOIDatabase(GsGeoDatabase* oracleDatabase);
	virtual ~GsOracleProxyPOIDatabase();

	virtual void DataRoomNames(UTILITY_NAME::GsVector<Utility::GsString>& vecName);
	/// \brief  打开POI数据
	virtual GsProxyPOIDataRoomPtr Open(const char* name);

	/// \brief  获取图标库
	virtual GsIconLibrary* IconLibrary();

	/// \brief  获取符号库
	virtual GsPlaceNameSymbolLibrary* SymbolLibrary();

	/// \brief  创建数据集
	virtual GsProxyPOIDataRoomPtr Create(GsPlaceNameMetadata& metadata);
};
KERNEL_ENDNS