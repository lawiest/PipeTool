#pragma once
#include <geometry.h>

KERNEL_NS

/// \brief 基于MapBox矢量瓦片标准的集合类型
enum GsMBGeometryType
{
	eMB_UNKNOWN = 0,
	eMB_POINT = 1,
	eMB_LINESTRING = 2,
	eMB_POLYGON = 3,	
};

struct GsMBLayer;
/// \brief 基于MapBox矢量瓦片标准的矢量地物对象
struct GS_API GsMBFeature
{
	/// \brief 地物唯一ID,PB索引1，缺省值0，
	/// \details PB:optional uint64 id = 1[default = 0];
	unsigned long long ID;

	/// \brief 地物属性在StringTable中的索引，PB索引1
	/// \details 偶数为Key，基数为Value
	/// \details PB:repeated uint32 tags = 2[packed = true];
	UTILITY_NAME::GsVector<unsigned int> Tags;

	/// \brief 几何类型，PB索引3
	/// \details PB:optional GeomType type = 3[default = UNKNOWN];
	GsMBGeometryType  Type;

	/// \brief 几何数据，PB索引4
	/// \details repeated uint32 geometry = 4[packed = true];
	UTILITY_NAME::GsVector<unsigned int> Geometry;

	/// \brief 高度编码后的几何数据对应的解码后的几何对象
	KERNEL_NAME::GsGeometryPtr   GeometryPtr;

	GsMBFeature();
	/// \brief 
	/// \param data 
	/// \param nLen 
	GsMBFeature(const unsigned char* data,int nLen);
	/// \brief 存储为二进制数据
	/// \param data 
	/// \return 
	bool Save(UTILITY_NAME::GsString& data);
	/// \brief 标识图层是否有效
	/// \return 
	bool IsValid();

	/// \brief 获取解压后的几何对象
	/// \param tileExtent 
	/// \param nPixelEtent 
	/// \return 
	KERNEL_NAME::GsGeometry* EnsureGeometry(const KERNEL_NAME::GsBox& tileExtent, unsigned int nPixelEtent = 4096);

	/// \brief 设置Geometry将Geometry编码
	/// \param pGeo 
	/// \param tileExtent 
	/// \param nPixelEtent 
	void AssignGeometry(KERNEL_NAME::GsGeometry* pGeo, const KERNEL_NAME::GsBox& tileExtent, unsigned int nPixelEtent = 4096);
	/// \brief 
	/// \param pGeo 
	/// \param tileExtent 
	/// \param nPixelEtent 
	void AssignGeometry(geostar::geo_object *pGeo, const KERNEL_NAME::GsBox& tileExtent, unsigned int nPixelEtent = 4096);
	/// \brief 
	/// \param pGeo 
	/// \param tileExtent 
	/// \param nPixelEtent 
	void AssignSimpleGeometry(geostar::geo_object *pGeo, const KERNEL_NAME::GsBox& tileExtent, unsigned int nPixelEtent = 4096);
	/// \brief 获取某1列的值
	/// \param index 
	/// \return 
	UTILITY_NAME::GsAny   Value(int index);
	/// \brief 获取某个key的值
	/// \param key 
	/// \return 
	UTILITY_NAME::GsAny  Value(const char* key);
	/// \brief 设置图层,方便查询,不提供获取方法
	/// \param Layer 
	void Layer(GsMBLayer * Layer);
private:
	GsMBLayer * m_Layer;
	int m_offX, m_offY;
	UTILITY_NAME::GsStlMap<UTILITY_NAME::GsString, UTILITY_NAME::GsAny>    m_ValueCacheMap;
	/// \brief 
	/// \param point 
	/// \param tileExtent 
	void AddPoint(double* point, const KERNEL_NAME::GsBox & tileExtent);
};


/// \brief 基于MapBox矢量瓦片标准的矢量图层对象
struct GS_API GsMBLayer
{
/// \brief 版本号,PB索引15，缺省值1，
	/// \details PB:required uint32 version = 15[default = 1];
	unsigned int Version;

	/// \brief 图层名称,PB索引1，
	/// \details PB:required string name = 1;
	UTILITY_NAME::GsString Name;

	/// \brief 所有的地物,PB索引2，
	/// \details PB:repeated Feature features = 2;
	UTILITY_NAME::GsVector<GsMBFeature> Features;

	/// \brief 字符串表StringTable,PB索引3，
	/// \details PB:repeated string keys = 3;
	UTILITY_NAME::GsVector<UTILITY_NAME::GsString> Keys;

	/// \brief 属性值表,PB索引4，
	/// \details PB:repeated Value values = 4;
	UTILITY_NAME::GsVector<UTILITY_NAME::GsAny> Values;

	/// \brief 逻辑范围,PB索引5，缺省值4096
	/// \details PB:optional uint32 extent = 5[default = 4096];
	unsigned int Extent;

	GsMBLayer();
	/// \brief 
	/// \param data 
	/// \param nLen 
	GsMBLayer(const unsigned char* data, int nLen);
	
	/// \brief 存储为二进制数据
	/// \param data 
	/// \return 
	bool Save(UTILITY_NAME::GsString& data);

	/// \brief 标识图层是否有效
	/// \return 
	bool IsValid();

	/// \brief 根据OID获取一个Feature
	/// \param oid 
	/// \return 
	GsMBFeature& QueryFeature(unsigned long long oid);
	
	/// \brief 根据OID判断Feature是否才能在
	/// \param oid 
	/// \return 
	bool ExistFeature(unsigned long long oid);
	
	/// \brief 增加一个Key，返回Key在StringTable中的索引
	/// \param key 
	/// \param bIgnoreCase 
	/// \return 
	unsigned int AddKey(const char* key, bool bIgnoreCase = true);

	/// \brief 增加一个值，返回值在字典中的索引
	/// \param val 
	/// \return 
	unsigned int AddValue(const UTILITY_NAME::GsAny& val);

	/// \brief 
	void Clear();
private:
	UTILITY_NAME::GsStlMap<unsigned long long, int>    m_IndexMap;
};


/// \brief 基于MapBox矢量瓦片标准的矢量瓦片对象
/// \brief https://github.com/mapbox/vector-tile-spec
class GS_API GsMBVectorTile
{
	/// \brief 图层列表,PB索引3
	/// \details PB:repeated Layer layers = 3;
	UTILITY_NAME::GsVector<GsMBLayer> m_Layers;
public:
	/// \brief 构造空的矢量瓦片
	GsMBVectorTile();
	/// \brief 从二进制块构造
	/// \param data 
	/// \param nLen 
	GsMBVectorTile(const unsigned char* data,int nLen);

	virtual ~GsMBVectorTile();
	
	/// \brief 从二进制数据解析
	/// \param data 
	/// \param nLen 
	/// \return 
	virtual bool Parse(const unsigned char* data, int nLen);

	/// \brief 存储为二进制数据
	/// \param data 
	/// \return 
	virtual bool Save(UTILITY_NAME::GsString& data);

	/// \brief 根据图层名称检索图层
	/// \param name 
	/// \param bIgnoreCase 
	/// \return 
	GsMBLayer& QueryLayer(const char* name, bool bIgnoreCase = true);

	/// \brief 判断图层是否存在
	/// \param name 
	/// \param bIgnoreCase 
	/// \return 
	bool ExistLayer(const char* name, bool bIgnoreCase = true);


	/// \brief 图层列表,PB索引3
	/// \details PB:repeated Layer layers = 3;
	/// \return 
	UTILITY_NAME::GsVector<GsMBLayer>& Layers();

	/// \brief 
	void Clear();
protected:
	/// \brief 
	/// \return 
	virtual bool Filter();
};

/// \brief 基于经过GZ或ZLib压缩的矢量瓦片
class GS_API GsZipMBVectorTile:public GsMBVectorTile
{
public:

	/// \brief Zip压缩类型
	enum GsZipType
	{
		/// \brief 未压缩
		eUnZip,
		/// \brief gs压缩类型
		eGZip,
		/// \brief Zlib压缩
		eZLib,
	};
	GsZipType m_eType;
public:
	GsZipMBVectorTile();
	/// \brief 
	/// \param data 
	/// \param nLen 
	GsZipMBVectorTile(const unsigned char* data,int nLen);

	/// \brief 获取设置压缩类型
	/// \return 
	GsZipType& Type();

	/// \brief 从二进制数据解析
	/// \param data 
	/// \param nLen 
	/// \return 
	virtual bool Parse(const unsigned char* data, int nLen);

	/// \brief 存储为二进制数据
	/// \param data 
	/// \return 
	virtual bool Save(UTILITY_NAME::GsString& data);
};

/// \brief 基于经过GZ或ZLib压缩的矢量瓦片,解析瓦片数据就过滤掉出需要的图层数据
class GS_API GsFilterZipMBVectorTile : public GsZipMBVectorTile
{
	UTILITY_NAME::GsVector<UTILITY_NAME::GsString> m_FilterNames;
public:
	GsFilterZipMBVectorTile();
	/// \brief 
	/// \param data 
	/// \param nLen 
	/// \param filterNames 
	GsFilterZipMBVectorTile(const unsigned char* data, int nLen, const UTILITY_NAME::GsVector<UTILITY_NAME::GsString>& filterNames);

protected:
	/// \brief 
	/// \return 
	virtual bool Filter();

};

KERNEL_ENDNS