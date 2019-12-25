#pragma once
#include "pyramid.h"
#include "geometry.h"
#include "vectorhelp.h"
KERNEL_NS
class GsPlaceNameStyleExtensionData;
/// \brief Web服务地址解析类
class GS_API GsWebUriParser : public UTILITY_NAME::GsRefObject
{
	bool m_bSuccess;
protected:
	/// \brief 格式化请求字符串时允许用户添加的额外KV参数
	UTILITY_NAME::GsStringMap m_mapUserParameter;

	/// \brief 版本
	UTILITY_NAME::GsString m_strVersion;
	/// \brief URI地址
	UTILITY_NAME::GsString m_strUri;
	/// \brief capability字符串
	UTILITY_NAME::GsString m_strCapInfo;
	
	Utility::GsVector<UTILITY_NAME::GsString> m_vecNull;

	/// \brief 
	/// \param strUri 
	GsWebUriParser(const char* strUri = NULL);
public:
	
	virtual ~GsWebUriParser() {}

	/// \brief 创建格式化的URL字符串
	/// \return 
	virtual UTILITY_NAME::GsString FormatUri() = 0;

	/// \brief 获取Uri字符串
	/// \return 
	UTILITY_NAME::GsString UriString() { return m_strUri; }

	/// \brief 解析描述信息
	/// \return 
	bool ParseCapability();


	/// \brief 格式化请求字符串时允许用户添加的额外KV参数
	/// \return 
	UTILITY_NAME::GsStringMap& UserParameter();


protected:
	/// \brief 描述信息URL地址
	/// \return 
	virtual UTILITY_NAME::GsString CapabilityUri();

	/// \brief 解析描述字符串
	/// \param strXml 
	/// \return 
	virtual bool ParseCapabilityString(const UTILITY_NAME::GsString& strXml);
	
};
GS_SMARTER_PTR(GsWebUriParser);

/// \brief 瓦片地图服务解析器
class GS_API GsTMSUriParser : public GsWebUriParser
{
protected:
	/// \brief 
	/// \param strUri 
	GsTMSUriParser(const char* strUri);
public:
	/// \brief 获取图层名
	/// \return 
	virtual UTILITY_NAME::GsString LayerName() = 0;

	/// \brief 获取图层范围
	/// \return 
	virtual GsBox LayerExtent() = 0;

	/// \brief 顶层瓦片级别
	/// \return 
	virtual int TopLevel() = 0;

	/// \brief 底层瓦片级别
	/// \return 
	virtual int BottomLevel() = 0;

	/// \brief 金字塔
	/// \return 
	virtual GsPyramid* Pyramid() = 0;

	/// \brief 空间参考
	/// \return 
	virtual GsSpatialReference* SpatialReference() = 0;
};
GS_SMARTER_PTR(GsTMSUriParser);

/// \brief 公众瓦片地图
enum GsWellknownWebTileService {
	/// \brief 天地图地理坐标系矢量瓦片WMTS服务
	eTiandituVectorGeographicWMTS,
	/// \brief 天地图地理坐标系影像瓦片WMTS服务
	eTiandituImageGeographicWMTS,
	/// \brief 天地图地理坐标系矢量瓦片Geo瓦片服务
	eTiandituVectorGeographicGeoTile,
	/// \brief 天地图地理坐标系影像瓦片Geo瓦片服务
	eTiandituImageGeographicGeoTile,
	/// \brief 天地图地理坐标地形瓦片Geo瓦片服务
	eTiandituTerrainGeographicGeoTile,
	/// \brief 天地图地理坐标地形瓦片WMTS服务
	eTiandituTerrainGeographicWMTS,

	/// \brief 天地图Web墨卡托坐标系矢量瓦片WMTS服务
	eTiandituVectorWebMercatorWMTS,
	/// \brief 天地图Web墨卡托坐标系影像瓦片WMTS服务
	eTiandituImageWebMercatorWMTS,

	/// \brief 天地图地理坐标系影像标注瓦片WMTS服务
	eTiandituImageAnnotationGeographicWMTS,
	/// \brief 天地图地理坐标系影像标注瓦片Geo瓦片服务
	eTiandituImageAnnotationGeographicGeoTile,
	/// \brief 天地图Web墨卡托坐标系影像标注瓦片WMTS服务
	eTiandituImageAnnotationWebMercatorWMTS, 


	
	
	/// \brief 高德
	eAmapVectorWebMercator = 100,
	eAmapImageWebMercator,
	
	/// \brief 谷歌地图
	eGoogleVectorWebMercator = 200,
	eGoogleImageWebMercator,
	
	/// \brief 必应地图
	eBingVectorWebMercator = 300,
	eBingImageWebMercator,
	
	/// \brief OSM
	eOSMVectorWebMercator = 400,
	eOSMImageWebMercator,
	
	/// \brief Arcgis
	eArcgisOnlineVectorWebMercator = 500,
	eArcgisOnlineImageWebMercator,
};

/// \brief 公众瓦片地图解析
class GS_API GsWellknownTMSUriParser:public GsTMSUriParser
{
	UTILITY_NAME::GsString m_strFormat;
	UTILITY_NAME::GsString m_Name;
	GsBox m_Extent;
	int m_Top, m_Bottom;
	GsPyramidPtr m_ptrPyramid;

	GsSpatialReferencePtr m_ptrSR;
public:
	/// \brief 
	/// \param web 
	GsWellknownTMSUriParser(GsWellknownWebTileService web);

	/// \brief 创建格式化的URL字符串
	/// \return 
	virtual UTILITY_NAME::GsString FormatUri();

	/// \brief 获取图层名
	/// \return 
	virtual UTILITY_NAME::GsString LayerName();

	/// \brief 获取图层范围
	/// \return 
	virtual GsBox LayerExtent();

	/// \brief 顶层瓦片级别
	/// \return 
	virtual int TopLevel();

	/// \brief 底层瓦片级别
	/// \return 
	virtual int BottomLevel();

	/// \brief 金字塔
	/// \return 
	virtual GsPyramid* Pyramid();

	/// \brief 空间参考
	/// \return 
	virtual GsSpatialReference* SpatialReference();
};
GS_SMARTER_PTR(GsWellknownTMSUriParser);

/// \brief WMTS服务解析类
class GS_API GsWMTSUriParser : public GsTMSUriParser
{
	/// \brief 图层属性
	struct GsLayerProperty
	{
		/// \brief 图层名
		UTILITY_NAME::GsString strLayerName;
		/// \brief 图层样式
		UTILITY_NAME::GsVector<UTILITY_NAME::GsString> vecLayerStyle;
		/// \brief 瓦片矩阵集
		UTILITY_NAME::GsVector<UTILITY_NAME::GsString> vecTileMatrixSets;
		/// \brief 图片格式
		UTILITY_NAME::GsVector<UTILITY_NAME::GsString> vecImageFormat;

		GsBox extent;
	};

	/// 瓦片矩阵集
	struct GsTileMatrixSet
	{
		int nTopLevel;
		int nBottomLevel;
		GsPyramidPtr m_ptrPyramid;
		GsSpatialReferencePtr m_ptrRef;
	};

	/// \brief 所有图层名
	UTILITY_NAME::GsVector<UTILITY_NAME::GsString> m_vecLayers;
	/// \brief 图层名对应的图层属性信息<图层名，属性对象>
	UTILITY_NAME::GsStlMap<UTILITY_NAME::GsString, GsLayerProperty> m_mapLayerProp;
	/// \brief 所有矩阵名称
	UTILITY_NAME::GsVector<UTILITY_NAME::GsString> m_vecTileMatrixSet;
	UTILITY_NAME::GsStlMap<UTILITY_NAME::GsString, GsTileMatrixSet> m_mapTileMatrixSet;

	UTILITY_NAME::GsString m_strCurLayerName;
	UTILITY_NAME::GsString m_strCurTileMatrixSet;
	
protected:
	/// \brief 描述信息URL地址
	/// \return 
	virtual UTILITY_NAME::GsString CapabilityUri();

	/// \brief 解析描述字符串
	/// \param strXml 
	/// \return 
	virtual bool ParseCapabilityString(const UTILITY_NAME::GsString& strXml);

	/// \biref 解析图层节点
	/// \brief 
	/// \param pNode 
	/// \return 
	bool ParseLayerNode(tinyxml2::XMLElement* pNode);

	/// \brief 解析矩阵集节点
	/// \param pNode 
	/// \return 
	bool ParseMatrixSetNode(tinyxml2::XMLElement* pNode);
	 
public:
	/// \brief 
	/// \param strUri 
	GsWMTSUriParser(const char* strUri);
	virtual ~GsWMTSUriParser();

	/// \brief 创建格式化的URL字符串
	/// \return 
	virtual UTILITY_NAME::GsString FormatUri();

	/// \brief 获取图层名
	/// \return 
	virtual UTILITY_NAME::GsString LayerName();

	/// \brief 获取图层范围
	/// \return 
	virtual GsBox LayerExtent();

	/// \brief 顶层瓦片级别
	/// \return 
	virtual int TopLevel();

	/// \brief 底层瓦片级别
	/// \return 
	virtual int BottomLevel();

	/// \brief 金字塔
	/// \return 
	virtual GsPyramid* Pyramid();

	/// \brief 空间参考
	virtual	GsSpatialReference* SpatialReference();

public:
	/// \brief 获取所有图层名
	/// \return 
	const UTILITY_NAME::GsVector<UTILITY_NAME::GsString>& AllLayerName() { return m_vecLayers; }

	/// \brief 设置当前图层名（服务中可能有多个图层）
	bool LayerName(const char* strLayerName);	

	/// \brief 获取当前图层所有样式类型
	/// \return 
	const UTILITY_NAME::GsVector<UTILITY_NAME::GsString>& Style();

	/// \brief 获取当前图层所有图片格式
	/// \return 
	const UTILITY_NAME::GsVector<UTILITY_NAME::GsString>& ImageFormat();

	/// \brief 获取当前图层所有瓦片矩阵集名称
	/// \return 
	const UTILITY_NAME::GsVector<UTILITY_NAME::GsString>& TileMatrixSet();

	/// \brief 设置当前瓦片矩阵集
	/// \param strTileMatrixSet 
	/// \return 
	bool CurrentTileMatrixSet(const char* strTileMatrixSet);
	/// \brief 获取当前瓦片矩阵集
	/// \return 
	UTILITY_NAME::GsString CurrentTileMatrixSet();
};
GS_SMARTER_PTR(GsWMTSUriParser);

/// \brief 吉奥瓦片服务解析类
class GS_API GsGeoTileUriParser : public GsTMSUriParser
{
protected:
	/// \brief 瓦片数据类型
	UTILITY_NAME::GsString m_strTileDataType;
	/// \brief 图层名
	UTILITY_NAME::GsString m_strLayerName;
	/// \brief 图层范围
	GsBox m_LayerExtent;
	
	/// \brief 顶层瓦片级别
	int m_nTopLevel;
	/// \brief 底层瓦片级别
	int m_nBottomLevel;
	/// \brief 金字塔对象
	GsPyramidPtr m_ptrPyramid;
	/// \brief 空间参考对象
	GsSpatialReferencePtr m_ptrRef;

	/// \brief 瓦片格式
	Utility::GsVector<UTILITY_NAME::GsString> m_vecTileFormat;

	/// \brief 节点名称
	UTILITY_NAME::GsString m_strNodeTileFormat;
	/// \brief 节点名称
	UTILITY_NAME::GsString m_strNodeData;
protected:
	/// \brief 描述信息URI地址
	/// \return 
	virtual UTILITY_NAME::GsString CapabilityUri();

	/// \brief 解析描述字符串
	/// \param strXml 
	/// \return 
	virtual bool ParseCapabilityString(const UTILITY_NAME::GsString& strXml);

	/// \brief 解析TileData节点
	/// \param pTileData 
	/// \return 
	virtual bool ParseTileData(tinyxml2::XMLElement* pTileData);

public:
	/// \brief 
	/// \param strUri 
	GsGeoTileUriParser(const char* strUri);
	virtual ~GsGeoTileUriParser();

	/// \brief 创建格式化的URL字符串
	/// \return 
	virtual UTILITY_NAME::GsString FormatUri();

public:
	/// \brief 图层名
	/// \return 
	virtual UTILITY_NAME::GsString LayerName() { return m_strLayerName; }

	/// \brief 获取图层范围
	/// \return 
	virtual GsBox LayerExtent() { return m_LayerExtent; }

	/// \brief 顶层瓦片级别
	/// \return 
	virtual int TopLevel() { return m_nTopLevel; }

	/// \brief 底层瓦片级别
	/// \return 
	virtual int BottomLevel() { return m_nBottomLevel; }

	/// \brief 金字塔
	/// \return 
	virtual GsPyramid* Pyramid() { return m_ptrPyramid.p; }

	/// \brief 空间参考
	/// \return 
	virtual GsSpatialReference* SpatialReference() { return m_ptrRef.p; }

	/// \brief 瓦片数据类型
	/// \reutrn image-影像数据、terrain-地形数据、wtfs-地名数据
	/// \return 
	UTILITY_NAME::GsString TileDataType() { return m_strTileDataType; }
};
GS_SMARTER_PTR(GsGeoTileUriParser);


/// \brief 地名服务解析类
class GS_API GsWTFSUriParser : public GsGeoTileUriParser
{
public:
	/// \brief 
	/// \param strUri 
	GsWTFSUriParser(const char* strUri);
	virtual ~GsWTFSUriParser();

	/// \brief 创建格式化的URL字符串
	/// \return 
	virtual UTILITY_NAME::GsString FormatUri();

	/// \brief 创建格式化的请求ICON字符串
	/// \return 
	UTILITY_NAME::GsString FormatIconUri();

	/// \brief 请求图标辅助数据对象
	/// \return 
	Utility::GsSmarterPtr<GsPlaceNameStyleExtensionData> IconExtensionData();
protected:
	/// \brief 解析TileData节点
	/// \param pTileData 
	/// \return 
	virtual bool ParseTileData(tinyxml2::XMLElement* pTileData);
};



/// \brief WMS服务解析类
class GS_API GsWMSUriParser : public GsTMSUriParser
{
public:

	/// \brief WMS图层基本信息
	struct WMSLayerInformation
	{
		UTILITY_NAME::GsString							Name;
		UTILITY_NAME::GsString							Title;
		GsBox											Extent;
		UTILITY_NAME::GsVector<UTILITY_NAME::GsString>	Styles;
		UTILITY_NAME::GsString							CRS;
	};
private:
	GsPyramidPtr m_ptrPyramid;
	GsSpatialReferencePtr m_ptrSR;
	GsBox m_Extent;
	UTILITY_NAME::GsString m_LayerName;
	UTILITY_NAME::GsString m_Styles; 
	UTILITY_NAME::GsString m_Format;
	UTILITY_NAME::GsString m_FormatUrl;
	UTILITY_NAME::GsString m_CRS;
	UTILITY_NAME::GsVector<UTILITY_NAME::GsString> m_vecFormat;
	UTILITY_NAME::GsVector<WMSLayerInformation> m_vecLayers;
	/// \brief 
	void CreateFormatURI();
public:
	/// \brief 
	/// \param url 
	/// \param pyramid 
	GsWMSUriParser(const char* url, GsPyramid* pyramid = NULL);
	/// \brief getmap方法支持的格式
	/// \return 
	virtual const UTILITY_NAME::GsVector<UTILITY_NAME::GsString>& GetMapFormat()const;

	/// \brief getmap方法使用的格式
	/// \return 
	virtual UTILITY_NAME::GsString Format()const;
	/// \brief getmap方法使用的格式
	/// \param format 
	virtual void Format(const char* format);

	/// \brief getmap方法使用的坐标
	/// \return 
	virtual UTILITY_NAME::GsString CRS()const;
	/// \brief getmap方法使用的坐标
	/// \param crs 
	virtual void CRS(const char* crs);


	/// \brief 版本号
	/// \return 
	virtual UTILITY_NAME::GsString Version();
	/// \brief 设置要请求的版本号
	/// \param ver 
	virtual void Version(const char* ver);

	/// \brief 图层信息列表
	/// \return 
	const UTILITY_NAME::GsVector<WMSLayerInformation>& Layers()const;

	/// \brief 获取图层名列表，多个图层用半角逗号分隔
	/// \return 
	virtual UTILITY_NAME::GsString LayerName();
	/// \brief 设置图层名，多个图层用半角逗号分隔
	/// \param names 
	virtual void LayerName(const char* names);

	/// \brief 获取式样名列表，多个式样用半角逗号分隔
	/// \return 
	virtual UTILITY_NAME::GsString StyleName();
	/// \brief 设置式样名，多个式样用半角逗号分隔
	/// \param names 
	virtual void StyleName(const char* names);


	/// \brief 获取图层范围
	/// \return 
	virtual GsBox LayerExtent();

	/// \brief 顶层瓦片级别
	/// \return 
	virtual int TopLevel();

	/// \brief 底层瓦片级别
	/// \return 
	virtual int BottomLevel();

	/// \brief 金字塔
	/// \return 
	virtual GsPyramid* Pyramid();

	/// \brief 空间参考
	/// \return 
	virtual GsSpatialReference* SpatialReference();
	
	/// \brief 创建格式化的URL字符串
	/// \return 
	virtual UTILITY_NAME::GsString FormatUri();
	 

protected:
	/// \brief 解析描述字符串
	/// \param strXml 
	/// \return 
	virtual bool ParseCapabilityString(const UTILITY_NAME::GsString& strXml);
	/// \brief 描述信息URL地址
	/// \return 
	virtual UTILITY_NAME::GsString CapabilityUri();

};
GS_SMARTER_PTR(GsWMSUriParser);


KERNEL_ENDNS