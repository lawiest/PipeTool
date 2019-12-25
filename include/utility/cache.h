#pragma once
#include "preconfig.h"  
#include "configuration.h"
#include "model.h"
UTILITY_NS 

/// \brief 缓存对象，以Key-Value方式存储任意数据
class GS_API GsCache:public GsRefObject
{
protected:
	GsCache();
public:
	~GsCache();

	/// \brief 关闭缓存
	virtual void Close();
	/// \brief 缓存数据
	/// \param key 缓存的Key 
	/// \param nKLen 缓存的Key的长度
	/// \param value 缓存的value
	/// \param nValueLen 缓存的Value的长度
	virtual bool Write(const unsigned char* key, int nKLen, const unsigned char* value, int nValueLen) = 0;
	
	/// \brief 缓存字符串类型的Key和Value
	virtual bool Write(const char* key, const char* value);
	/// \brief 缓存Key为字符串的Value
	virtual bool Write(const char* key, const unsigned char* value, int nValueLen);

	/// \brief 缓存Key为任意结构的字符串Value
	template<class U>
	bool WriteT(const U& key, const char* value)
	{
		return Write((const unsigned char*)&key, sizeof(U), (const unsigned char*)value, strlen(value));
	}

	/// \brief 缓存Key为任意结构的字符串Value
	template<class U>
	bool WriteT(const U& key, const unsigned char* value,int nValueLen)
	{
		return Write((const unsigned char*)&key, sizeof(U), value, nValueLen);
	}

	/// \brief 缓存Key和Value为任意结构
	template<class U, class V>
	bool WriteT(const U& key, const V& value)
	{
		return Write((const unsigned char*)&key, sizeof(U), (const unsigned char*)&value, sizeof(V));
	}

	/// \brief 查询缓冲中的数据
	/// \param key 缓存的Key 
	/// \param nKLen 缓存的Key的长度
	/// \param value 输出存储缓存值用的Buffer
	/// \param nValueLen 存储缓存的Buffer长度
	/// \return 返回Value的长度，如果输入缓冲区长度不够则只返回值的长度
	virtual int Read(const unsigned char* key, int nKLen, unsigned char* valueBuffer, int nBufferLen) const = 0;

	/// \brief 查询字符串Key和Value
	virtual int Read(const char* key, GsByteBuffer* buffer) const;
	/// \brief 查询字符串Key和Value
	virtual int Read(const char* key, unsigned char* value, int nValueLen) const;
	/// \brief 查询字符串Key和Value
	virtual int Read(const unsigned char* key, int nKLen, GsByteBuffer* buffer) const;

	/// \brief 查询字符串Key和Value
	virtual GsString Read(const char* key) const;

	/// \brief 查询ey为任意结构的字符串Value
	template<class U>
	int ReadT(const U& key, GsByteBuffer* buffer) const
	{
		return Read((const unsigned char*)&key, sizeof(U), buffer);
	}

	/// \brief 查询Key和Value为任意结构
	template<class U, class V>
	int ReadT(const U& key, const V& value) const
	{
		return Read((const unsigned char*)&key, sizeof(U), (unsigned char*)&value, sizeof(V));
	}

	/// \brief 是否存在Key
	virtual bool Exist(const unsigned char* key, int nKLen)const = 0;

	virtual bool Exist(const  char* key) const;

	template<class T>
	bool ExistT(const T& key)const
	{
		return Exist((const unsigned char*)&key, sizeof(T));
	}

};
/// \brief GsCachePtr
GS_SMARTER_PTR(GsCache);

#pragma pack(push)
#pragma pack(1)
 

/// \brief 带数据集标识的四叉树瓦片Key
struct GsDataSetQuadKey
{
	GsDataSetQuadKey()
	{
		DataSet = 0;
		Level = 0;
		Row = 0;
		Col = 0;

	} 
	GsDataSetQuadKey(long long ds, const GsQuadKey& k)
	{
		DataSet = ds;
		Level = k.Level;
		Row = k.Row;
		Col = k.Col;
	}
	GsDataSetQuadKey(long long ds, int l, int r, int c)
	{
		DataSet = ds;
		Level = l;
		Row = r;
		Col = c;

	}
	bool operator<(const GsDataSetQuadKey& rhs) const
	{
		return (DataSet != rhs.DataSet)? DataSet < rhs.DataSet:
			(Level != rhs.Level) ? (Level < rhs.Level) :
			(Row != rhs.Row) ? (Row < rhs.Row) :
			(Col < rhs.Col);

	}
	operator GsQuadKey()const
	{
		return QuadKey();
	}
	GsQuadKey QuadKey()const
	{
		return GsQuadKey(Level, Row, Col);
	}
	GsDataSetQuadKey(const GsDataSetQuadKey& rhs)
	{
		
		DataSet = rhs.DataSet;
		Level = rhs.Level;
		Row = rhs.Row;
		Col = rhs.Col;

	} 
	/// \brief 数据集标识
	long long DataSet;
	/// \brief 瓦片级别
	int Level;
	/// \brief 瓦片行
	int Row;
	/// \brief 瓦片列
	int Col;
};
#pragma pack(pop)

/// \brief 缓存瓦片数据的缓存
class GS_API  GsTileCache:public GsCache
{
protected:
	GsTileCache();
public:
	~GsTileCache();
	
	/// \brief 缓存瓦片数据
	virtual bool WriteTile(const GsQuadKey& key, const unsigned char* value, int nlen);

	/// \brief 缓存瓦片数据
	virtual bool WriteTile(const GsDataSetQuadKey& key, const unsigned char* value, int nlen);

	/// \brief 查询瓦片数据
	virtual int ReadTile(const GsDataSetQuadKey& key, GsByteBuffer* buffer)const;
	/// \brief 查询瓦片数据
	virtual int ReadTile(const GsQuadKey& key, GsByteBuffer* buffer)const;

	/// \brief 判断瓦片是否存在
	virtual bool ExistTile(const GsQuadKey& key)const;
	
	/// \brief 判断瓦片是否存在
	virtual bool ExistTile(const GsDataSetQuadKey& key)const;



};
/// \brief GsTileCachePtr
GS_SMARTER_PTR(GsTileCache);

/// \brief 缓存管理器
class GS_API GsCacheManager
{
	bool m_bInit;
	GsTileCachePtr m_TileCache;
	GsConfig	m_Config;
	/// \brief 引用缓冲管理器的数量
	GsAtomic<int> m_RefCount;
public:
	GsCacheManager();
	~GsCacheManager();
	/// \brief 全局唯一的缓存管理对象
	static GsCacheManager& Default();

	/// \brief 从配置初始化缓存管理器
	virtual bool Initialize(const GsConfig& config);

	/// \brief 内部的配置对象
	const GsConfig& Config();

	/// \brief 主缓存对象
	GsCache* PrimaryCache();

	/// \brief 主瓦片缓存对象
	GsTileCache* PrimaryTileCache();

	/// \brief 增加一次对管理器的引用
	int AddReference();

	/// \brief 减少一次对管理器的引用
	int ReleaseReference();

	/// \brief 是否已经初始化
	bool IsInitialized();

	/// \brief 是否已经初始化
	operator bool ();

};
UTILITY_ENDNS