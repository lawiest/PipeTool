#pragma once
#include "../utility/preconfig.h"
#include "geodatabase.h"

KERNEL_NS 

/// \brief 地名式样扩展数据
class GS_API GsPlaceNameStyleExtensionData :public GsDataRoomExtensionData
{
protected:
	GsPlaceNameStyleExtensionData();
public:
	virtual ~GsPlaceNameStyleExtensionData();

	/// \brief 根据图标的ID获取图标数据
	/// \param ID 
	/// \param buff 
	/// \return 
	virtual bool Icon(long long ID, Utility::GsByteBuffer* buff) = 0;
};
/// \brief GsPlaceNameStyleExtensionDataPtr
GS_SMARTER_PTR(GsPlaceNameStyleExtensionData);

/// \brief 图标数据
struct GS_API GsIconData
{
	GsIconData();
	/// \brief 拷贝构造
	/// \param rhs 
	GsIconData(const GsIconData& rhs);
	/// \brief 赋值操作符重载
	/// \param rhs 
	/// \return 
	GsIconData& operator =(const GsIconData& rhs);
	/// \brief 判断是否相等
	/// \param rhs 
	/// \return 
	bool operator == (const GsIconData& rhs)const;

	/// \brief 唯一ID
	long long ID;
	
	
	/// \brief 名称
	Utility::GsString Name;

	/// \brief 别名
	Utility::GsString AliasName;

	/// \brief 图标内容
	Utility::GsGrowByteBuffer Content;

	/// \brief 图标显示宽度，单位像素
	int Width;

	/// \brief 图标显示宽度，单位像素
	int Height;

	/// \brief 图标类型
	int Type;
};
/// \brief 图标库
class GS_API GsIconLibrary
{
public:
	virtual ~GsIconLibrary();
	
	/// \brief 图标的数量
	/// \return 
	virtual int Count() = 0;

	/// \brief 根据索引获取图标数据内容
	/// \param nIndex 
	/// \param data 
	/// \return 
	virtual bool IconData(int nIndex, GsIconData& data) = 0;

	/// \brief 根据图标ID查询图标数据内容
	/// \param id 
	/// \param data 
	/// \return 
	virtual bool QueryIconData(long long id, GsIconData& data) = 0;

	/// \brief 存储或替换已有图标数据
	/// \param data 
	/// \return 
	virtual bool SaveIconData(GsIconData& data) = 0;

	/// \brief 删除图标数据
	/// \param id 
	/// \return 
	virtual bool DeleteIconData(long long id) = 0;
};



/// \brief 地名符号
struct GS_API GsPlaceNameSymbol
{
	GsPlaceNameSymbol();
	/// \brief 
	/// \param rhs 
	GsPlaceNameSymbol(const GsPlaceNameSymbol& rhs);
	/// \brief 
	/// \param rhs 
	/// \return 
	GsPlaceNameSymbol& operator = (const GsPlaceNameSymbol& rhs);
	/// \brief 判断是否相等
	/// \param rhs 
	/// \return 
	bool operator == (const GsPlaceNameSymbol& rhs)const;

	/// \brief 符号唯一ID，GUID形式
	Utility::GsString ID;

	/// \brief 字体名称
	Utility::GsString FontName;

	/// \brief 字体大小
	float FontSize;
	 
	/// \brief 字体颜色
	Utility::GsColor FontColor;

	/// \brief 线宽，单位像素
	double LineSize;

	/// \brief 线颜色
	Utility::GsColor LineColor;

	/// \brief 填充颜色
	Utility::GsColor PolygonColor;

	/// \brief 扩展渲染信息
	UTILITY_NAME::GsGrowByteBuffer ExternRenderInfo;
	
	/// \brief 标题
	UTILITY_NAME::GsString Caption;
	/// \brief 描述
	UTILITY_NAME::GsString Description;

	/// \brief 开始显示级别
	int TopLevel;

	/// \brief 结束显示级别
	int BottomLevel;

	/// \brief 图标显示宽度,单位像素
	int Width;

	/// \brief 图标显示高度,单位像素
	int Height;

	/// \brief 文字光晕宽度，单位像素
	double HaloSize;

	/// \brief 文字光晕颜色
	Utility::GsColor HaloColor;

};
/// \brief 地名符号库
class GS_API GsPlaceNameSymbolLibrary
{
public:
	virtual ~GsPlaceNameSymbolLibrary();
	
	/// \brief 符号数量
	/// \return 
	virtual int Count() = 0;

	/// \brief 根据索引获取一个符号
	/// \param nIndex 
	/// \param sym 
	/// \return 
	virtual bool QuerySymbol(int nIndex, GsPlaceNameSymbol& sym) = 0;

	/// \brief 根据唯一id查询一个符号
	/// \param id 
	/// \param sym 
	/// \return 
	virtual bool QuerySymbol(const char* id, GsPlaceNameSymbol& sym) = 0;

	/// \brief 存储或者替换一个符号
	/// \param sym 
	/// \return 
	virtual bool SaveSymbol(GsPlaceNameSymbol& sym) = 0;

	/// \brief 根据唯一ID删除一个符号
	/// \param id 
	/// \return 
	virtual bool DeleteSymbol(const char* id) = 0;

};

/// \brief 地名属性分类
struct GS_API GsPlaceNameClassify
{
	GsPlaceNameClassify();
	bool operator == (const GsPlaceNameClassify& r)const;
	GsPlaceNameClassify& operator = (const GsPlaceNameClassify& r);

	/// \brief 分类值
	UTILITY_NAME::GsString Classify;
	
	/// \brief 图标ID
	long long IconID;
	
	/// \brief 符号ID
	UTILITY_NAME::GsString SymbolID;

	/// \brief 开始级别
	int TopLevel;

	/// \brief 结束
	int BottomLevel;
};

/// \brief 地名数据属性分类
class GS_API GsPlaceNameClassifies
{
protected:
	GsPlaceNameClassifies();
public:
	virtual ~GsPlaceNameClassifies();
	
	/// \brief 数量
	/// \return 
	virtual int Count() = 0;

	/// \brief 根据索引查询
	/// \param nIndex 
	/// \param data 
	/// \return 
	virtual bool QueryClassify(int nIndex, GsPlaceNameClassify& data) = 0;

	/// \brief 根据分类值
	/// \param value 
	/// \param data 
	/// \return 
	virtual bool QueryClassify(const char* value, GsPlaceNameClassify& data) = 0;

	/// \brief 增加或替换分类值
	/// \param data 
	/// \return 
	virtual bool SaveClassify( GsPlaceNameClassify& data) = 0;

	/// \brief 删除分类值
	/// \param value 
	/// \return 
	virtual bool DeleteClassify(const char* value) = 0;

};

/// \brief 地名数据基本元信息
struct GS_API GsPlaceNameMetadata
{
	GsPlaceNameMetadata();
	
	/// \brief 数据集名称
	UTILITY_NAME::GsString Name;

	/// \brief 金字塔信息
	GsPyramidPtr Pyramid;

	/// \brief 有效金字塔级别
	UTILITY_NAME::GsVector<int> Levels;

	/// \brief 分类字段
	UTILITY_NAME::GsString ClassifyField;
	/// \brief 显示字段
	UTILITY_NAME::GsString DisplayField;
	/// \brief 分类名称
	UTILITY_NAME::GsString ClassName;

	/// \brief 扩展url地址
	UTILITY_NAME::GsString ExtractURL;

	UTILITY_NAME::GsString SymID;

	/// \brief X坐标字段名
	UTILITY_NAME::GsString XField;
	/// \brief Y坐标字段名
	UTILITY_NAME::GsString YField;

	/// \brief Z坐标字段名
	UTILITY_NAME::GsString ZField;

	/// \brief 坐标维度，2或3
	int CoordinateDimension;
};


/// \brief 地名数据管理数据扩展
class GS_API GsPlaceNameManagerExtensionData :public GsPlaceNameStyleExtensionData
{
protected:

	GsPlaceNameManagerExtensionData();
public:

	virtual ~GsPlaceNameManagerExtensionData();

	/// \brief 获取图标库
	/// \return 
	virtual GsIconLibrary* IconLibrary() = 0;

	/// \brief 获取属性分类
	/// \return 
	virtual GsPlaceNameClassifies* Classifies() = 0;

	/// \brief 获取符号库
	/// \return 
	virtual GsPlaceNameSymbolLibrary* SymbolLibrary() = 0;

	/// \brief 获取发布的瓦片数据集
	/// \return 
	virtual GsTileClass* PublishTileClass() = 0;
	
	/// \brief 获得元数据信息
	/// \return 
	virtual GsPlaceNameMetadata Metadata() = 0;
	/// \brief 设置元数据信息
	/// \param data 
	virtual void Metadata(const GsPlaceNameMetadata& data) = 0;
};
/// \brief GsPlaceNameManagerExtensionDataPtr
GS_SMARTER_PTR(GsPlaceNameManagerExtensionData);

KERNEL_ENDNS
