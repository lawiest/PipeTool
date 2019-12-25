#pragma once
#include "../utility/preconfig.h"
#include "map.h" 
KERNEL_NS

/// \brief 地图定义文件读写类
class GS_API GsMapDefine
{
	/// \brief 地图定义文件的文件路径
	Utility::GsString m_strFile;
	GsMapPtr m_ptrMap;
public:
	GsMapDefine();
	~GsMapDefine();

	/// \brief 从地图定义文件打开
	/// \param strFilePath 
	GsMapDefine(const char* strFilePath);
	
	/// \brief 设置地图定义文件的路径
	/// \param strFilePath 
	void FilePath(const char* strFilePath);
	
	/// \brief 获取地图定义文件的路径
	/// \return 
	Utility::GsString FilePath();

	/// \brief 解析地图定义文件为地图
	/// \param pMap 
	/// \return 
	bool ParserMap(GsMap* pMap);

	/// \brief 解析地图定义文件为地图
	/// \param strFilePath 
	/// \param pMap 
	/// \return 
	bool ParserMap(const char* strFilePath,GsMap* pMap);

	/// \brief 解析地图定义文件为地图
	/// \param strGmdXML 
	/// \param strSymXML 
	/// \param pMap 
	/// \return 
	bool ParserMap(const char* strGmdXML,const char* strSymXML,GsMap* pMap);

	/// \brief 保存到文件
	/// \param pMap 
	/// \param strFilePath 
	/// \return 
	bool SaveMap(GsMap* pMap, const char* strFilePath);

	/// \brief 打开地物类
	/// \details 参数1 
	/// \details 参数2 
	Utility::GsDelegate<GsFeatureClassPtr(const GsConnectProperty&, const char*)> OnOpenFeatureClass;
	/// \brief 打开瓦片数据集
	/// \details 参数1 
	/// \details 参数2 
	Utility::GsDelegate<GsTileClassPtr(const GsConnectProperty&, const char*)> OnOpenTileClass;
	/// \brief 打开栅格类
	/// \details 参数1 
	/// \details 参数2 
	Utility::GsDelegate<GsRasterClassPtr(const GsConnectProperty&, const char*)> OnOpenRasterClass;

	/// \brief 设置与地图定义文件相同样式的layer
	/// \param pLayer 
	/// \return 
	bool ApplyStyleLayer(GsLayer* pLayer);

	/// \brief 找到与class同源的层
	/// \param pClass 
	/// \return 
	Utility::GsVector<GsLayerPtr> FindLayers(GsGeoDataRoom* pClass);
private:
	/// \brief 
	/// \param pLayer 
	/// \param pApplyLayer 
	/// \return 
	bool ApplyLayerByLayer(GsLayer* pLayer, GsLayer* pApplyLayer);
	/// \brief 
	/// \param pLayer 
	/// \param pClass 
	/// \param vecLayers 
	void FindLayerByClass(GsLayer* pLayer, GsGeoDataRoom* pClass, Utility::GsVector<GsLayerPtr>& vecLayers);
};

KERNEL_ENDNS