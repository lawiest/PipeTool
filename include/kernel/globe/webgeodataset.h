#pragma once
#include "kernel.h"
#include "utility.h"
#include "utility3d.h"
#include "weburiparser.h"
#include "workthread.h"

class USmallScene;
class GsGtsDataSource;
GLOBE_NS

/// \brief 数据集类型
enum GsDatasetType
{
	/// \brief 卫星、航拍影像数据集
	eDatasetImage,
	/// \brief 地形数据集
	eDatasetTerrain,
	/// \brief 屏幕元素数据集
	eDatasetElement,
	/// \brief 矢量数据集
	eDatasetVector,
	/// \brief 动态矢量数据集
	eDatasetDynamicVector,

	/// \brief 地名数据集
	eDatasetPlacename,
	/// \brief 倾斜影像数据集
	eDatasetOblique,
	/// \brief 精细模型数据集
	eDatasetUModel,
	/// \brief 精细小场景模型数据集
	eDatasetUWorld,
	eDatasetMax,
	
};

enum GsRequestResult
{
	eRRInit,
	eRRError,
	eRRBase,
	eRROutOfRange,
	eRRSendOut,
	eRRNotRender,
	eRROK
};
 


/// \brief 瓦片任务跟踪，避免任务重复添加或执行
class GS_API GsTileTaskTracker:public UTILITY_NAME::GsRefObject
{
	int m_nFaild;
	int m_nDarkPeriod;
	Utility::GsStopWatch m_Watch;
	Utility::GsSafeObject < Utility::GsStlMap < UTILITY_NAME::GsDataSetQuadKey, Utility::GsPair<long long,int>  > > m_BlackList;
	Utility::GsSafeObject<Utility::GsStlMap<UTILITY_NAME::GsDataSetQuadKey, bool > > m_TaskKey;
public:
	GsTileTaskTracker();

	/// \brief 判断一个任务是否已经列入黑名单
	bool IsBlack(const UTILITY_NAME::GsDataSetQuadKey& k);

	/// \brief 执行任务前增加一个任务到列表
	void Add(const UTILITY_NAME::GsDataSetQuadKey& k);

	/// \brief 判断任务是否存在
	bool Exists(const UTILITY_NAME::GsDataSetQuadKey& k);
	
	/// \brief 判断一个任务是否正在执行
	bool IsWorking(const UTILITY_NAME::GsDataSetQuadKey& k);
	
	/// \brief 判断一个任务是否正在等待
	bool IsWaiting(const UTILITY_NAME::GsDataSetQuadKey& k);

	/// \brief 判断一个任务是否正在执行
	/// \details 如果任务不存在则返回false
	bool Begin(const UTILITY_NAME::GsDataSetQuadKey& k);
	
	/// \brief 标识一个任务已经解决
	/// \param k 任务的Key
	/// \param bSucceed 任务是否执行成功了,执行失败的任务会列入黑名单
	bool Finish(const UTILITY_NAME::GsDataSetQuadKey& k, bool bSucceed);
	
	/// \brief 删除一个任务Key
	void RemoveForce(const UTILITY_NAME::GsDataSetQuadKey& k);
};
/// \brief GsTileTaskTrackerPtr
GS_SMARTER_PTR(GsTileTaskTracker);

/// \brief 对于从数据源获取的数据进行预
class GS_API GsRequestDataPreprocess :public UTILITY_NAME::GsRefObject
{
public:
	virtual ~GsRequestDataPreprocess() {}
	virtual bool Preprocess(const UTILITY_NAME::GsDataSetQuadKey& key, const unsigned char* data, int nLen, UTILITY_NAME::GsByteBuffer* buff) = 0;
};
/// \brief GsRequestDataPreprocessPtr 
GS_SMARTER_PTR(GsRequestDataPreprocess);

/// \brief 复合处理器，多个处理器中任何一个成功则成功
class GS_API GsMultiDataPreprocess :public GsRequestDataPreprocess
{
	UTILITY_NAME::GsVector<GsRequestDataPreprocessPtr> m_vecSub;

public:
	GsMultiDataPreprocess();
	GsMultiDataPreprocess(GsRequestDataPreprocess* sub);
	
	/// \brief 添加一个
	void Add(GsRequestDataPreprocess* sub);
	/// \brief 数量
	int Count();
	/// \brief 清空
	void Clear();
	/// \brief 移除，返回移除的对象
	GsRequestDataPreprocessPtr Remove(int i);
	/// \brief 获取对象
	GsRequestDataPreprocessPtr Item(int i);

	/// \brief 预处理
	virtual bool Preprocess(const UTILITY_NAME::GsDataSetQuadKey& key, const unsigned char* data, int nLen, UTILITY_NAME::GsByteBuffer* buff);


};
/// \brief GsRequestDataPreprocessPtr 
GS_SMARTER_PTR(GsRequestDataPreprocess);



/// \brief 基于Hash算法和数据长度验证无效数据的的预处理对象
class GS_API GsHashCheckDataPreprocess :public GsRequestDataPreprocess
{
	UTILITY_NAME::GsVector<UTILITY_NAME::GsPair<unsigned long long, int> > m_HashData;
public:
	GsHashCheckDataPreprocess();
	GsHashCheckDataPreprocess(unsigned long long hash, int datasize);
	GsHashCheckDataPreprocess(UTILITY_NAME::GsPair<unsigned long long, int>* hashset,int nCount);
	
	/// \brief 清空所有必要数据
	void Clear();
	
	/// \brief hash比较数据的数量
	int Count();
	
	/// \brief 删除一个比较数据，返回删除的数据
	UTILITY_NAME::GsPair<unsigned long long, int> Remove(int i);

	/// \brief 获取一个比较数据
	UTILITY_NAME::GsPair<unsigned long long, int> Data(int i);

	/// \brief 添加一个比较数据
	void Add(unsigned long long hash, int datasize);

	/// \brief 添加多个比较数据
	void Add(UTILITY_NAME::GsPair<unsigned long long, int>* hashset, int nCount);

	virtual bool Preprocess(const UTILITY_NAME::GsDataSetQuadKey& key, const unsigned char* data, int nLen, UTILITY_NAME::GsByteBuffer* buff);
};
/// \brief GsHashCheckDataPreprocessPtr 
GS_SMARTER_PTR(GsHashCheckDataPreprocess);

/// \brief 天地图影像数据处理器
/// \details 识别天地图的无效瓦片
class GS_API GsTianDituImageDataPreprocess :public GsHashCheckDataPreprocess
{ 
public:
	GsTianDituImageDataPreprocess();
};
/// \brief GsTianDituImageDataPreprocessPtr 
GS_SMARTER_PTR(GsTianDituImageDataPreprocess);


/// \brief 瓦片数据集
class GS_API GsTileDataset : public UTILITY_NAME::GsRefObject
{
	/// \brief 数据集的HashKey 
	long long	m_DataSetKey;
	// 是否可见
	bool m_bVisible;
	// 是否重新计算hash标识（当数据集变化需要重新刷新时设置状态）
	bool m_bRefresh;
	
protected:
	GsRequestDataPreprocessPtr m_ptrDataPreprocess;
	/// \brief 数据集名称
	Utility::GsString m_strName;
	/// \brief 数据集类型
	GsDatasetType m_eType;
	/// \brief 数据集路径
	Utility::GsString m_strDSPath;

	GsTileDataset();

	/// \brief 数据集的唯一Key描述
	virtual Utility::GsString UniqueKey() = 0;

	/// \brief 请求数据
	virtual bool OnRequest(int nLevel, int nRow, int nCol) = 0;

	/// \brief 是否是有效的瓦片
	virtual bool IsValidTile(int nLevel, int nRow, int nCol) { return false; }

	/// \brief 瓦片缓存对象
	Utility::GsTileCache* Cache();
	 
public:
	virtual ~GsTileDataset();

	/// \brief 数据预处理对象
	GsRequestDataPreprocess* DataPreprocess();
	
	/// \brief 数据预处理对象
	void DataPreprocess(GsRequestDataPreprocess* process);

	/// \brief 获取或者计算数据集的hashKey
	long long DataSetKey();

	/// \brief 获取名称
	Utility::GsString Name();
	void Name(const char* strName);

	/// \brief 获取数据集路径
	virtual Utility::GsString Path();

	/// \brief 数据集类型
	GsDatasetType DatasetType();
	void DatasetType(GsDatasetType eType);

	/// \brief 数据集是否可见
	virtual void Visible(bool bVislble);
	virtual bool Visible();

	/// \brief 获得有效显示的高程值
	virtual double ValidElevation();

	/// \brief 获取数据范围
	virtual GsBox Extent() = 0;

	/// \brief 获取数据高度
	virtual double Height();

	/// \brief 获取金字塔
	virtual GsPyramid* Pyramid() = 0;

	/// \brief 获取空间参考
	virtual GsSpatialReference* SpatialReference() = 0;

	/// \brief 根据层行列请求数据
	virtual GsRequestResult Request(int l, int r, int c, UTILITY_NAME::GsByteBuffer* buff);

	///\数据加载完成
	UTILITY_NAME::GsDelegate<void(bool state)> DataLoadResultEventHandler;
	virtual void OnDatasetLoadOK(bool state);
};
GS_SMARTER_PTR(GsTileDataset);

/// \brief 瓦片地物类数据集
class GS_API GsTileClassDataset : public GsTileDataset
{
protected:
	/// \brief 瓦片地物类
	GsTileClassPtr m_ptrTileClass;

public:
	GsTileClassDataset(GsTileClass *pTileClass);
	virtual ~GsTileClassDataset();

	/// \brief 获取瓦片地物类
	GsTileClass* TileClass();

	/// \brief 获取数据范围
	virtual GsBox Extent();

	/// \brief 获取金字塔
	virtual GsPyramid* Pyramid();

	/// \brief 获取空间参考
	virtual GsSpatialReference* SpatialReference();

protected:
	/// \brief 数据集的唯一Key描述
	virtual Utility::GsString UniqueKey();

	/// \brief 请求数据
	virtual bool OnRequest(int nLevel, int nRow, int nCol);

	/// \brief 是否是有效的瓦片
	virtual bool IsValidTile(int nLevel, int nRow, int nCol);
};
GS_SMARTER_PTR(GsTileClassDataset);

/// 瓦片地图服务数据集类型
class GS_API GsTMSDataset :public GsTileClassDataset
{
protected:
	GsTMSTileClassPtr m_ptrTMSTileClass;
	GsTMSUriParserPtr m_ptrTMSUriParser;

	/// \brief 范围
	GsBox m_Extent;
	/// \brief 金字塔
	GsPyramidPtr m_ptrPyramid;
	/// \brief 空间参考
	GsSpatialReferencePtr m_ptrRef;
	/// \brief 开始级别
	int m_nTopLevel;
	/// \brief 结束级别
	int m_nBottomLevel;

	GsTMSDataset(GsTileClass* pTileClass);
public:
	GsTMSDataset(GsTMSUriParser* pUriParser);
	virtual ~GsTMSDataset();

	/// \brief 设置数据范围
	void Extent(const GsBox& ext);
	/// \brief 获取数据范围
	virtual GsBox Extent();

	/// \brief 设置金字塔
	void Pyramid(GsPyramid* pPyramid);
	/// \brief 获取金字塔
	virtual GsPyramid* Pyramid();

	/// \brief 设置空间参考
	void SpatialReference(GsSpatialReference* pRef);
	/// \brief 获取空间参考
	virtual GsSpatialReference* SpatialReference();

	/// \brief 瓦片层级范围
	void LevelRange(int nTopLevel, int nBottomLevel);
	/// \brief 瓦片开始层级
	int TopLevel();
	/// \brief 瓦片结束层级
	int BottomLevel();

	// \brief 获得Url解析器
	GsTMSUriParser *UrlParser();

protected:
	/// \brief 数据集的唯一Key描述
	virtual Utility::GsString UniqueKey();

	/// \brief 请求数据
	virtual bool OnRequest(int nLevel, int nRow, int nCol);

	/// \brief 瓦片是否有效
	virtual bool IsValidTile(int nLevel, int nRow, int nCol);
};
GS_SMARTER_PTR(GsTMSDataset);

/// WMTS数据集类型
class GS_API GsWMTSDataset : public GsTMSDataset
{
public:
	GsWMTSDataset(GsWMTSUriParser *pUriParser);
	virtual ~GsWMTSDataset();

	/// \brief 设置样式
	void Style(const char* strStyle);

	/// \brief 设置瓦片矩阵
	void TileMatrixSet(const char* strTileMatrixSet);

	/// \brief 设置图片格式
	void ImageFormat(const char* strImageFormat);

protected:
	/// \biref 更新Url串
	bool UpdateUrlTemplate(const UTILITY_NAME::GsString& strAttrName, const UTILITY_NAME::GsString& strAttrValue);
};
GS_SMARTER_PTR(GsWMTSDataset);

/// WMS数据集类型
class GS_API GsWMSDataset : public GsTMSDataset
{
public:
	GsWMSDataset(GsWMSUriParser *pUriParser);
	virtual ~GsWMSDataset();

	/// \brief 设置图片格式
	void ImageFormat(const char* strImageFormat);

	/// \brief 设置图片是否透明
	void ImageTransparent(bool bTransparent);

	/// \brief 设置请求数据的图层名
	void ImageLayer(const char* strLayerNames);

	/// \brief 设置请求数据的版本号
	void Version(const char* strLayerNames);

protected:
	/// \biref 更新Url串
	bool UpdateUrlTemplate(const UTILITY_NAME::GsString& strAttrName, const UTILITY_NAME::GsString& strAttrValue);
};
GS_SMARTER_PTR(GsWMSDataset);

/// \brief GeoTile服务数据集类型
class GS_API GsGeoTileDataset : public GsTMSDataset
{
protected:
	GsGeoTileDataset(GsTileClass *pTileClass);
public:
	GsGeoTileDataset(GsGeoTileUriParser* pParser);
	virtual ~GsGeoTileDataset();
};
GS_SMARTER_PTR(GsGeoTileDataset);

/// \brief 模型数据句柄封装
struct GS_API GsModelDataHandle
{
	/// \brief 类型
	int Type;
	/// \brief 主数据句柄
	union
	{
		long long MainIdentity;
		void*     MainHandle;
	};
	/// \brief 辅数据句柄
	union
	{
		long long AssistIdentity;
		void*     AssistHandle;
	};
	GsModelDataHandle()
	{
		Type = 0;
		AssistIdentity = 0;
		MainIdentity = 0;
	}
	GsModelDataHandle(const GsModelDataHandle& o)
	{
		Type = o.Type;
		AssistIdentity = o.AssistIdentity;
		MainIdentity = o.MainIdentity;
	}
	GsModelDataHandle(int type,void* mainHandle,void* assistHandle = NULL)
	{
		Type = type;
		MainHandle = mainHandle;
		AssistHandle = assistHandle;
	}
	GsModelDataHandle(int type, long long mainIdentity, long long assistIdentity = NULL)
	{
		Type = type;
		MainIdentity = mainIdentity;
		AssistIdentity = assistIdentity;
	}
	/// \brief 是否有效
	operator bool()
	{
		return Type != 0 || AssistIdentity != 0 || MainIdentity != 0;
	}
	template<class T>
	T CastType()
	{
		return (T)Type;
	}

	template<class T>
	T* CastMainPointer()
	{
		return (T*)MainIdentity;
	}

	template<class T>
	T& CastMainHandle()
	{
		return *((T*)MainIdentity);
	}

	template<class T>
	T* CastAssistPointer()
	{
		return (T*)AssistIdentity;
	}

	template<class T>
	T& CastAssistHandle()
	{
		return *((T*)AssistIdentity);
	}
};
/// \brief 模型数据节点
class GS_API GsModelDataNode:public UTILITY_NAME::GsRefObject
{
protected:
	UTILITY_NAME::GsString  m_strName, m_strPath;
	unsigned long long				m_Hash;
	GsTileDatasetPtr				m_ptrDS;
	GsModelDataNode();
	
public:
	virtual ~GsModelDataNode();
	
	/// \brief 数据节点所属的数据集对象
	virtual GsTileDataset* Dataset();

	/// \brief 节点哈希值
	unsigned long long Hash();

	/// \brief 节点名称
	virtual const char* Name();
	/// \brief 节点路径
	virtual const char* Path();

	/// \brief 节点ID
	virtual const int Id();

	/// \brief 获取数据句柄
	/// \details 数据句柄的具体数据类型决定于数据集类型，内部方法不可轻易调用
	/// \details 调用此方法会导致实例化实际数据
	virtual GsModelDataHandle DataHandle();

	/// \brief 地理范围
	virtual KERNEL_NAME::GsBox Extent() = 0;

	/// \brief 定位点或中心点
	virtual KERNEL_NAME::GsRawPoint3D Location() = 0;

	/// \brief 子节点数量
	virtual int ChildrenCount();

	/// \brief 创建子对象并返回
	/// \details 调用者应该主动保存对象，多次调用此方法会导致多次创建子对象 
	virtual UTILITY_NAME::GsSmarterPtr<GsModelDataNode> Child(int i);

	/// \brief 设置高程偏移值
	virtual void ElevationOffside(double dblOffside);

	/// \brief 设置模型平移
	virtual void Translate(double dblX, double dblY, double dblZ);

	/// \brief 设置模型缩放
	virtual void Scale(float x, float y, float z);

	/// \brief 设置模型旋转
	virtual void Rotate(double axisX, double axisY, double axisZ, double angle);

	/// \brief 设置可见
	virtual void Visible(bool bVisible);

	/// \brief 是否可见
	virtual bool Visible();
};
GS_SMARTER_PTR(GsModelDataNode);


/// \brief 枚举模型数据节点
class GS_API GsEnumModelDataNode :public UTILITY_NAME::GsRefObject
{
public:
	virtual ~GsEnumModelDataNode();
	/// \brief 获取下一个数据节点
	virtual GsModelDataNodePtr Next() = 0;
	/// \brief 重置枚举过程
	virtual void Reset() = 0;
};
/// \brief GsEnumModelDataNodePtr
GS_SMARTER_PTR(GsEnumModelDataNode);

/// \brief 模型据集类型
class GS_API GsModelDataset : public GsTileDataset
{
protected:
	GsModelDataset(const char *strModelFilePath);
	GsModelDataset();
public:
	virtual ~GsModelDataset();

	/// \brief 枚举数据节点
	virtual GsEnumModelDataNodePtr EnumDataNode();

	/// \brief 顶层数据节点的数量
	virtual int RootDataNodeCount();

	/// \brief 创建子对象并返回
	/// \details 调用者应该主动保存对象，多次调用此方法会导致多次创建子对象 
	virtual GsModelDataNodePtr RootDataNode(int i);


};
GS_SMARTER_PTR(GsModelDataset);

/// \brief 复合模型数据集 
class GS_API GsMultiModelDataset:public GsModelDataset
{
protected:
	GsMultiModelDataset();
public:
	virtual ~GsMultiModelDataset();
	/// \brief 子数据集数量
	virtual int Count() = 0;
	/// \brief 获取一个子数据集
	virtual GsModelDatasetPtr SubDataset(int i) = 0;

	/// \brief 展开所有数据集
	virtual UTILITY_NAME::GsVector<GsModelDatasetPtr> ExpandSubDataset(int i) = 0;

};
GS_SMARTER_PTR(GsMultiModelDataset);

/// \brief 模型数据集类厂
class GS_API GsModelDatasetFactory
{
	UTILITY_NAME::GsConfig m_Config;
public:
	GsModelDatasetFactory(const UTILITY_NAME::GsConfig& config);
	GsModelDatasetFactory();
	~GsModelDatasetFactory();

	/// \brief 从路径创建模型数据集
	GsModelDatasetPtr Create(const char* path);
};


/// \brief 模型据集类型
class GS_API GsUModelDataset : public GsModelDataset
{
public:
	GsUModelDataset(const char *strModelFilePath);
	virtual ~GsUModelDataset();

	/// \brief 根据层行列请求数据
	virtual GsRequestResult Request(int l, int r, int c, UTILITY_NAME::GsByteBuffer* buff);

	GsBox Extent();
	double Height();
	GsPyramid* Pyramid();
	GsSpatialReference* SpatialReference();

	GsGtsDataSource* DataSourcePtr();

	/// \brief 获得有效显示的高程值
	virtual double ValidElevation();

	/// \brief 设置可见
	virtual void Visible(bool bVisible);
protected:
	virtual bool IsValidTile(int nLevel, int nRow, int nCol);

	bool OnRequest(int nLevel, int nRow, int nCol);
	Utility::GsString UniqueKey();

	GsPyramidPtr m_ptrGsPyramid;
	UTILITY_NAME::GsSmarterPtr<GsGtsDataSource> m_ptrDatasource;
};
GS_SMARTER_PTR(GsUModelDataset);

/// \brief Unigine World场景数据集
class GS_API GsUWorldDataset : public GsModelDataset
{
public:
	GsUWorldDataset(const char *strModelFilePath, const KERNEL_NAME::GsRawPoint3D* ptGeoPos = 0);

	virtual ~GsUWorldDataset();

	virtual GsBox Extent();

	/// \brief 获得有效显示的高程值
	virtual double ValidElevation();

	/// \brief 设置是否可见
	virtual void Visible(bool bVislble);

	void Position(const KERNEL_NAME::GsRawPoint3D& ptGeoPos);

	/// \brief 根据名字查找模型节点
	GsModelDataNodePtr SearchModelDataNode(UTILITY_NAME::GsString strName);

	/// \brief 根据id查找模型节点
	GsModelDataNodePtr SearchModelDataNode(int nModelID);

	///\brief 设置默认world坐标原点
	void SetDefaultOriginPoint();

	UTILITY_NAME::GsSharedPtr<USmallScene> getWorldScenePtr();

protected:
	virtual Utility::GsString UniqueKey() { return m_strName; }

	virtual bool OnRequest(int nLevel, int nRow, int nCol) { return false; }

	virtual GsPyramid* Pyramid() { return 0; }

	virtual GsSpatialReference* SpatialReference() { return 0; }

protected:
	UTILITY_NAME::GsSharedPtr<USmallScene> m_ptrWorldScene;

	//world坐标原点
	KERNEL_NAME::GsRawPoint3D m_OriginPoint;

	//配置文件中的默认world坐标原点（在用户没有给出定位信息时使用）
	KERNEL_NAME::GsRawPoint3D m_DefaultOriginPoint;
};
GS_SMARTER_PTR(GsUWorldDataset);

/// \brief OSGB格式模型据集类型
class GS_API GsOsgbModelDataset : public GsModelDataset
{
public:
	GsOsgbModelDataset(const char *strModelFilePath);
	virtual ~GsOsgbModelDataset();

public:
	virtual void Visible(bool bVisible);

	/// \brief 获得有效显示的高程值
	virtual double ValidElevation();

	virtual bool IsValidTile(int nLevel, int nRow, int nCol);
	virtual GsRequestResult Request(int l, int r, int c, UTILITY_NAME::GsByteBuffer* buff);

	GsBox Extent();
	GsPyramid* Pyramid();
	GsSpatialReference* SpatialReference();

	/// \brief 请求数据
	virtual bool OnRequest(int nLevel, int nRow, int nCol);
	void *DataSetPtr();
protected: 
	Utility::GsString UniqueKey();
	 
	void *m_pModelTree;
	KERNEL_NAME::GsPyramidPtr m_ptrGsPyramid;   
};
GS_SMARTER_PTR(GsOsgbModelDataset);

/// \brief 矢量数据集类型
class GS_API GsVectorDataset : public GsTileDataset
{
	KERNEL_NAME::GsFeatureClassPtr m_ptrFcs;
public:
	GsVectorDataset(KERNEL_NAME::GsFeatureClass *pFeatureClass);
	virtual ~GsVectorDataset();

public:
	GsBox Extent();
	GsPyramid* Pyramid();
	GsSpatialReference* SpatialReference();
	KERNEL_NAME::GsFeatureClass *FeatureClass();
	virtual bool IsValidTile(int nLevel, int nRow, int nCol);
	virtual void Visible(bool bVislble);
protected:
	bool OnRequest(int nLevel, int nRow, int nCol);
	Utility::GsString UniqueKey();
	GsPyramidPtr m_ptrGsPyramid;

	bool IsDataValid();
};
GS_SMARTER_PTR(GsVectorDataset);

/// \brief 地名数据集类型
class GS_API GsPlaceNameDataset : public GsGeoTileDataset
{
	UTILITY_NAME::GsGrowByteBuffer m_IconBuffer;
	KERNEL_NAME::GsTilePtr m_ptrPOITile;
public:
	GsPlaceNameDataset(GsTileClass *pTileClass);
	GsPlaceNameDataset(GsWTFSUriParser *pUriParser);
	virtual ~GsPlaceNameDataset();

	/// \brief 获取数据范围
	virtual GsBox Extent();

	/// \brief 获取金字塔
	virtual GsPyramid* Pyramid();

	/// \brief 获取空间参考
	virtual GsSpatialReference* SpatialReference();

	/// \brief 设置可见性
	virtual void Visible(bool bVislble);

public:
	virtual GsRequestResult Request(int l, int r, int c, UTILITY_NAME::GsByteBuffer* buff);

	/// \brief 请求地名图标
	UTILITY_NAME::GsImagePtr RequestIcon(int nId);
protected:
	/// \brief 瓦片是否有效
	virtual bool IsValidTile(int nLevel, int nRow, int nCol);
};
GS_SMARTER_PTR(GsPlaceNameDataset);


/// \brief 三维图层
class GS_API Gs3DLayer : public Utility::GsRefObject
{
protected:
	Utility::GsString m_strName;
	Utility::GsString m_strAliasName;
	GsTileDatasetPtr m_ptrDataset;
	bool m_bVisible;
	int m_nPriority;
	double m_dMinAltitude;
	double m_dMaxAltitude; 

	Gs3DLayer();
public:
	virtual ~Gs3DLayer() {}
	/// \brief 设置图层名称
	void Name(const char* strName);
	/// \brief 获取图层名称
	const char* Name();

	/// \brief 设置图层别名
	void AliasName(const char* strAliasName);
	/// \brief 获取图层别名
	const char* AliasName();

	/// \brief 设置数据集
	void Dataset(GsTileDataset* pDataset);
	/// \brief 数据集
	GsTileDataset* Dataset();

	/// \brief 设置是否可见
	void Visible(bool bVisible);
	/// \brief 获取是否可见
	bool Visible();

	/// \brief 设置优先级
	void Priority(int nPri);
	/// \brief 获取优先级
	int Priority();

	/// \brief 设置可视的高度范围
	void ViewAltitude(double dMinAltitude, double dMaxAltitude);
	/// \brief 获取最小可视高度
	double MinViewAltitude();
	/// \brief 获取最大可视高度
	double MaxViewAltitude();
	
};
GS_SMARTER_PTR(Gs3DLayer);

class GS_API Gs3DVectorLayer : public Gs3DLayer
{
	KERNEL_NAME::GsFeatureRendererPtr m_ptrRenderer;
public:
	Gs3DVectorLayer();
	virtual ~Gs3DVectorLayer() {}

	void Renderer(KERNEL_NAME::GsFeatureRenderer* pRenderer);
	KERNEL_NAME::GsFeatureRenderer* Renderer();
};
GS_SMARTER_PTR(Gs3DVectorLayer);

class GS_API Gs3DImageLayer : public Gs3DLayer
{
public:
	Gs3DImageLayer();
	virtual ~Gs3DImageLayer();
};
GS_SMARTER_PTR(Gs3DImageLayer);

class GS_API Gs3DTerrainLayer : public Gs3DLayer
{
public:
	Gs3DTerrainLayer();
	virtual ~Gs3DTerrainLayer();
};
GS_SMARTER_PTR(Gs3DTerrainLayer);

class GS_API Gs3DElementLayer : public Gs3DLayer
{
public:
	Gs3DElementLayer() {}
	virtual ~Gs3DElementLayer() {}
};
GS_SMARTER_PTR(Gs3DElementLayer);

class GS_API Gs3DPOILayer : public Gs3DLayer
{
public:
	Gs3DPOILayer() {}
	virtual ~Gs3DPOILayer() {}
};
GS_SMARTER_PTR(Gs3DPOILayer);

/// \brief 地形访问器
class GS_API GsTerrainAccessor : public UTILITY_NAME::GsRefObject, UTILITY_NAME::GsRWLock
{
	friend class GsLayerContainer;

	// 默认地形
	Gs3DTerrainLayerPtr m_ptrDefaultTerrain;
	// 地形数据表
	UTILITY_NAME::GsVector<Gs3DTerrainLayerPtr> m_vecTerrain;
	UTILITY_NAME::GsAtomic<long long> m_VerticalExaggeration;
	UTILITY_NAME::GsAtomic<long long> m_InvalidElevation;

	// 数据变化
	void FireOnDatasetChanged();
public:
	GsTerrainAccessor();
	~GsTerrainAccessor();

	/// \brief 默认地形
	Gs3DTerrainLayer* DefaultTerrain();

	/// \brief 地形数据集的数量
	int TerrainCount();

	/// \brief 根据索引获取一个地形数据集
	Gs3DTerrainLayer* Terrain(int nIndex);

public:
	/// \brief 地形夸张。
	double VerticalExaggeration();
	/// \brief 地形夸张。
	void VerticalExaggeration(double value);

	/// \brief 无效高程。
	double InvalidElevation();
	/// \brief 无效高程。
	void InvalidElevation(double value);


	/// \brief 查询地理坐标的高程。
	double QueryElevation(double x, double y);


	/// \brief 设置是否显示地形
	void TerrainVisible(bool bVisible);

	/// \brief 查询一组三维坐标的高层
	/// \param p3DCoord 坐标数组，以X，Y，Z形式存储
	int QueryElevation(double* p3DCoord, int nPointCount);


	/// \brief 当图层数量、顺序发生变化的时候发生
	UTILITY_NAME::GsDelegate<void()> OnDatasetChanged;

private:
	/// \brief 增加一个地形图层
	void AddTerrain(Gs3DTerrainLayer* terrain);

	/// \brief 根据索引移除一个地形图层
	Gs3DTerrainLayerPtr RemoveTerrain(int nIndex);

	/// \brief 移除一个地形图层
	Gs3DTerrainLayerPtr RemoveTerrain(Gs3DTerrainLayer* terrain);

	/// \brief 清除所有的地形图层
	void ClearTerrain();

	/// \brief 插入一个地形图层到指定位置。
	void InsertTerrain(int nIndex, Gs3DTerrainLayer* terrain);

	/// \brief 调整地形图层的顺序
	/// \param nNewIndex 置顶2  置底-2   上移1  下移-1 ;这里的移动是说的图层在vec中的移动
	void MoveTerrain(Gs3DTerrainLayer* terrain, int nNewIndex);
};
/// \brief TerrainAccessorPtr
GS_SMARTER_PTR(GsTerrainAccessor);


class GS_API GsPOIGeoDatabaseFactory : public KERNEL_NAME::GsGeoDatabaseFactory
{
public:
	/// \brief 根据数据库连接信息打开一个空间数据库
	/// \param connProperty 数据库连接信息
	/// \return 返回空间数据库对象实例或者空
	virtual GsGeoDatabasePtr Open(const GsConnectProperty& connProperty);
};

class GS_API GsLayerContainer :public UTILITY_NAME::GsRefObject
{
	UTILITY_NAME::GsVector<UTILITY_NAME::GsSmarterPtr<Gs3DLayer>> m_vecLayers;
	GsTerrainAccessor* m_pTerrainAccessor;
public:
	GsLayerContainer(GsTerrainAccessor* pTerrain);
	~GsLayerContainer();

	/// \brief 添加图层
	void AddLayer(Gs3DLayer* pLayer);

	/// \brief 删除图层
	void RemoveLayer(Gs3DLayer* pLayer);

	/// \brief 删除图层
	void RemoveLayer(int nIndex);

	/// \brief 清空图层
	void ClearLayer();

	/// \brief 调整图层顺序
	/// \param nNewIndex 置顶2  置底 - 2   上移1  下移 - 1; 这里的移动是说的图层在vec中的移动
	void MoveLayer(Gs3DLayer* pLayer, int nIndex);

	/// \brief 图层数量
	int LayerCount();

	/// \brief 获取指定位置的图层
	Gs3DLayer *Layer(int nIndex);

	/// \brief 获取指定名字的图层
	Gs3DLayer *Layer(const char* strName);

	/// \brief 获取图层处理器
	//GsTerrainAccessor* TerrainAccessor();

private:
	void OnLayerChanged();

};
GS_SMARTER_PTR(GsLayerContainer);

GLOBE_ENDNS