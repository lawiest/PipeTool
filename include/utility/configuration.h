﻿#pragma once
#include "preconfig.h"
#include "tinyxml2.h"
#include "stringhelp.h"
#include "vectorhelp.h" 
#include "locker.h"
#include "object.h"
#include "structreflect.h"

UTILITY_NS

/// \brief 配置项目
struct GsConfigItem
{
	GsString Name;
	GsString Type;
	GsString Value;
	GsString Description;
	union
	{
		void* Handle;
		long long Identity;
	};
	GsConfigItem()
	{
		Identity = 0;
	}
	/// \brief 
	/// \param h 
	GsConfigItem(void* h)
	{ 
		Handle = h;
	}
	/// \brief 
	/// \param n 
	GsConfigItem(const char* n)
	{
		Name = n;
		Identity = 0;
	}
	/// \brief 
	/// \param n 
	/// \param handle 
	GsConfigItem(const char* n,void* handle)
	{
		Name = n;
		Identity = 0;
		Handle = handle;
	}
	/// \brief 
	/// \param n 
	/// \param v 
	GsConfigItem(const char* n, long long v)
	{
		Name = n;
		Identity = v;
	}
	/// \brief 
	/// \param n 
	/// \param t 
	/// \param v 
	/// \param d 
	/// \param i 
	GsConfigItem(const char* n, const char* t, const char* v, const char* d, long long i)
	{
		Name = n ? n : "";
		Type = t ? t : "";
		Value = v ? v : "";
		Description = d ? d : "";
		Identity = i;
	}
	/// \brief 
	/// \param n 
	/// \param t 
	/// \param v 
	/// \param d 
	/// \param h 
	GsConfigItem(const char* n, const char* t, const char* v, const char* d, void* h)
	{
		Name = n ? n : "";
		Type = t ? t : "";
		Value = v ? v : "";
		Description = d ? d : "";
		Identity = 0;
		Handle = h;
	}
	/// \brief 
	/// \param val 
	GsConfigItem(const GsConfigItem& val)
	{
		Name = val.Name;
		Type = val.Type;
		Value = val.Value;
		Description = val.Description;
		Identity = val.Identity;
	}
	GsConfigItem& operator =(const GsConfigItem& val)
	{
		Name = val.Name;
		Type = val.Type;
		Value = val.Value;
		Description = val.Description;
		Identity = val.Identity;
		return *this;
	}
	/// \brief 
	/// \return 
	bool IsNull()
	{
		return Identity == 0;
	}
};

/// \brief 配置引擎
class GS_API  GsConfigEngine:public GsRefObject
{
protected:
	GsConfigEngine();
public:
	virtual ~GsConfigEngine();
	/// \brief 数据是否变化了
	/// \return 
	virtual bool IsDirty();
	/// \brief 清除数据变化标识
	virtual void ClearDirty();

	/// \brief 获取数据
	/// \param item 
	virtual void Assign(GsConfigItem* item) = 0;
	/// \brief 判断是否存在子项
	/// \param name 
	/// \param parent 
	/// \return 
	virtual bool Exists(const char* name, const  GsConfigItem* parent = NULL) = 0;
	/// \brief 获取一个配置项的所有子项
	/// \param parent 
	/// \return 
	virtual GsVector<GsString> Children(const GsConfigItem* parent = NULL) = 0;
	/// \brief 获取一个配置项的所有子项
	/// \param vec 
	/// \param parent 
	virtual void Children(GsVector<GsConfigItem> &vec,const GsConfigItem* parent = NULL) = 0;
	/// \brief 删除一个子项
	/// \param name 
	/// \param parent 
	virtual void RemoveChild(const char* name,const GsConfigItem* parent = NULL) = 0;

	/// \brief 获取一个配置项的子项
	/// \param name 
	/// \param parent 
	/// \return 
	virtual GsConfigItem Child(const char* name, const GsConfigItem* parent = NULL) = 0;
	/// \brief 更新或者添加一个子项
	/// \param child 
	/// \param parent 
	/// \return 
	virtual GsConfigItem UpdateChild(const GsConfigItem& child, const GsConfigItem* parent = NULL) = 0;

	/// \brief 获取一个子项的父
	/// \param child 
	/// \return 
	virtual GsConfigItem Parent(const GsConfigItem& child) = 0;

};
/// \brief GsConfigEnginePtr
GS_SMARTER_PTR(GsConfigEngine);

/// \brief 文件类型的的Engine
class GS_API  GsFileConfigEngine :public GsConfigEngine
{
public:
	virtual ~GsFileConfigEngine() {}
	/// \brief 
	/// \return 
	virtual GsString FileName() = 0;
	/// \brief 
	/// \param file 
	/// \return 
	virtual bool Save(const char* file = NULL) = 0;
};
/// \brief GsFileConfigEnginePtr
GS_SMARTER_PTR(GsFileConfigEngine);

class GS_API GsXMLConfigEngine :public GsFileConfigEngine
{
	Utility::GsRWLock		m_Lock;
	/// \brief Document只有根配置才不为空。
	tinyxml2::XMLDocument m_Doc; 
	tinyxml2::XMLDocument* m_pDoc;
	bool m_bDirty;
	/// \brief 
	void OnDirty();
	/// \brief 
	void Init();
	/// \brief 获取数据
	/// \param item 
	virtual void InnerAssign(GsConfigItem* item);


public: 
	GsXMLConfigEngine(); 
	/// \brief 
	/// \param pEle 配置项目的xml节点
	GsXMLConfigEngine(tinyxml2::XMLElement* pEle);
	/// \brief 从xml文件或者字符串打开配置
	/// \param strXML 字符串或者配置文件路径
	/// \param bIsString 判断strXML是xml字符串还是文件名，true表示strXML为纯的xml字符串
	GsXMLConfigEngine(const char* strXML, bool bIsString = false);
	~GsXMLConfigEngine();
	/// \brief 数据是否变化了
	/// \return 
	virtual bool IsDirty();

	/// \brief 清除数据变化标识
	virtual void ClearDirty();
	/// \brief 
	/// \return 
	virtual GsString FileName();
	/// \brief 获取数据
	/// \param item 
	virtual void Assign(GsConfigItem* item);
	/// \brief 删除一个子项
	/// \param name 
	/// \param parent 
	virtual void RemoveChild(const char* name, const GsConfigItem* parent = NULL);

	/// \brief 判断是否存在子项
	/// \param name 
	/// \param parent 
	/// \return 
	virtual bool Exists(const char* name, const  GsConfigItem* parent = NULL);
	/// \brief 获取一个配置项的所有子项
	/// \param parent 
	/// \return 
	virtual GsVector<GsString> Children(const GsConfigItem* parent = NULL);
	/// \brief 获取一个配置项的所有子项
	/// \param vec 
	/// \param parent 
	virtual void Children(GsVector<GsConfigItem> &vec, const GsConfigItem* parent = NULL);
	/// \brief 获取一个配置项的子项
	/// \param name 
	/// \param parent 
	/// \return 
	virtual GsConfigItem Child(const char* name, const  GsConfigItem* parent = NULL);
	/// \brief 更新或者添加一个子项
	/// \param child 
	/// \param parent 
	/// \return 
	virtual GsConfigItem UpdateChild(const GsConfigItem& child, const  GsConfigItem* parent = NULL);

	/// \brief 获取一个子项的父
	/// \param child 
	/// \return 
	virtual GsConfigItem Parent(const GsConfigItem& child) ;

	/// \brief 保存到文件
	/// \param file 
	/// \return 
	virtual bool Save(const char* file = NULL);
	
	/// \brief 输出成xml字符串
	/// \return 
	GsString ToString();

};
/// \brief GsXMLConfigEnginePtr
GS_SMARTER_PTR(GsXMLConfigEngine);

/// \brief 配置类，实现配置的读取和写入
class GS_API GsConfig
{
	GsConfigEnginePtr m_Engine;
	GsConfigItem		m_Item;

	/// \brief 特殊构造空的配置
	GsConfig(int i);	

public: 
	
	/// \brief 缺省构造，构造一个空的配置
	GsConfig();	

	/// \brief 
	/// \param engine 
	/// \param item 
	GsConfig(GsConfigEngine* engine, const GsConfigItem& item);
	/// \brief 
	/// \param engine 
	GsConfig(GsConfigEngine* engine);

	/// \brief 拷贝构造函数
	/// \param GsConfig 
	/// \return 
    GsConfig(const GsConfig & GsConfig) ; 
	/// \brief 
	/// \param pEle 配置项目的xml节点
	GsConfig(tinyxml2::XMLElement* pEle); 
 	/// \brief 从xml文件或者字符串打开配置
	/// \param strXML 字符串或者配置文件路径
	/// \param bIsString 判断strXML是xml字符串还是文件名，true表示strXML为纯的xml字符串
	GsConfig(const char* strXML,bool bIsString = false);

	/// \brief 等号赋值操作符。 
    /// \brief GsConfig其他配置项  
	GsConfig & operator =(const GsConfig &GsConfig);
	
	/// \brief 析构函数
	virtual ~GsConfig(void);
	 
	/// \brief 获取配置项的内容
	/// \return 
	const GsConfigItem& Item()const;

	/// \brief 获取配置文件的文件名
	/// \return 
    GsString FileName() const;
	
	/// \brief 保存到文件中
	/// \param strFile 
	/// \return 
	bool Save(const char* strFile);
	
	/// \brief 保存为XML字符串
	/// \return 
	GsString Save();
	
	/// \brief 判断配置是否发生了变化
	/// \return 
	bool IsDirty() const;
	
	/// \brief 清除变化标识
	void ClearDirty();


	/// \brief 获取根配置对象
	/// \return 
	GsConfig  Root() const ;
	
	/// \brief 是否为根配置
	/// \return 
	bool IsRoot() const;
	
	/// \brief 获取父亲配置对象
	/// \return 
	GsConfig Parent() const;
	
	/// \brief 获取设置配置的名称
	/// \return 
	GsString Name()const;
	/// \brief 
	/// \param str 
	void Name(const GsString& str);
	/// \brief 
	/// \param str 
	void Name(const char* str);
	
	/// \brief 获取设置配置项的描述
	/// \return 
	GsString Description()const;
	/// \brief 
	/// \param str 
	void Description(const GsString& str);
	/// \brief 
	/// \param str 
	void Description(const char* str);

	/// \brief 配置的数据类型
	/// \return 
	GsString Type()const;
	/// \brief 
	/// \param str 
	void Type(const GsString& str);
	/// \brief 
	/// \param str 
	void Type(const char* str);
	
	/// \brief 判断配置是否有效
	/// \return 
	bool IsValid()const;
	/// \brief 
	/// \return 
	bool Good() const;
	/// \brief 
	/// \return 
	bool IsNull() const;
	operator bool() const;


	/// \brief 获取配置的路径
	/// \return 
	GsString Path()const;
	
	/// \brief 选择一个子的配置，如果不存在的话会创建这个子的配置并返回
	/// \param strName 
	/// \return 
	GsConfig Child(const char* strName);
	/// \brief 
	/// \param strName 
	/// \return 
	GsConfig Child(const GsString& strName);

	/// \brief 是否存在某个子的配置
	/// \param strName 
	/// \return 
	bool Exist(const char* strName)const;
	/// \brief 
	/// \param strName 
	/// \return 
	bool Exist(const GsString& strName)const;
	
	/// \brief 是否存在子的配置
	/// \return 
	bool HasChildren()const;
	/// \brief 是否为同一配置节点
	bool operator ==(const GsConfig& config);

	/// \brief 所有的子对象列表
	/// \return 
	GsVector<GsConfig> Children() const;
	/// \brief 
	/// \param vec 
	void Children(GsVector<GsConfig> &vec) const;

	/// \brief 子配置的名称
	/// \return 
	GsVector<GsString> ChildrenName()const;
	/// \brief 
	/// \param vec 
	void ChildrenName(GsVector<GsString> &vec)const;
	
	/// \brief 选择一个子的配置，如果不存在的话并不会创建
	/// \param strName 
	/// \return 
	GsConfig Peek(const char* strName)const;
	/// \brief 
	/// \param strName 
	/// \return 
	GsConfig Peek(const GsString& strName)const;
	
	/// \brief 方括号操作符，设计调用Peek方法
	GsConfig operator [](const char* strName) const;
	GsConfig operator [](const GsString& strName) const; 

	/// \brief 配置的值
	/// \return 
	GsString Value() const;
	/// \brief 设置配置的值
	/// \param strValue 
	void Value(const char* strValue) ;
	/// \brief 
	/// \param strValue 
	void Value(const GsString&  strValue) ;
	/// \brief 
	/// \param value 
	void Value(int value) ;
	/// \brief 
	/// \param value 
	void Value(unsigned int value) ;
	/// \brief 
	/// \param value 
	void Value(long long value) ;
	/// \brief 
	/// \param value 
	void Value(unsigned long long value) ;
	
	/// \brief 
	/// \param value 
	void Value(bool value) ;
	
	/// \brief 
	/// \param value 
	void Value(float value) ;
	/// \brief 
	/// \param value 
	void Value(double value) ;

	/// \brief 获取字符串值，不存在则返回缺省值
	/// \param strDefaultValue 
	/// \return 
	GsString StringValue(const char* strDefaultValue) const;
	/// \brief 
	/// \param strDefaultValue 
	/// \return 
	GsString StringValue(const GsString& strDefaultValue) const;
	/// \brief 
	/// \return 
	const char* ValuePtr() const;

	/// \brief 判断是否为特定值类型
	/// \return 
	bool IsNumberValue() const;
	/// \brief 
	/// \return 
	bool IsIntValue() const;
	/// \brief 
	/// \return 
	bool IsFloatValue() const;
	/// \brief 
	/// \return 
	bool IsBooleanValue() const;
	
	/// \brief 获取特定类型的值
	/// \param nValue 
	/// \return 
	int IntValue(int nValue) const;
	/// \brief 
	/// \param nValue 
	/// \return 
	long long Int64Value(long long nValue) const;
	/// \brief 
	/// \param bValue 
	/// \return 
	bool BoolValue(bool bValue) const;
	/// \brief 
	/// \param bFloat 
	/// \return 
	double FloatValue(double bFloat) const;

	/// \brief 类型重载操作符
	operator const char* () const;
	operator int () const;
	operator long long () const;
	operator double () const;
	operator float() const;
	operator unsigned int() const;
	operator unsigned long long() const;
	
	/// \brief 将另外的分支添加到这个GsConfig中
	/// \param config 
	void Append(const GsConfig& config);

	/// \brief 清空所有的子配置
	void Clear();
	
	/// \brief 删除一个子配置
	/// \param childName 
	void Remove(const char* childName);
	/// \brief 删除一个子配置
	/// \param childName 
	void Remove(const GsString&  childName);
	
	/// \brief 交换两个节点的内容
	/// \param other 
	/// \return 
	GsConfig& Swap(GsConfig& other);

	/// \brief 获取配置的存储引擎
	/// \return 
	GsConfigEngine* Engine();
};

/// \brief 全局配置类
class GS_API GsGlobalConfig
{
public:
	/// \brief 全局的配置类根对象
	/// \return 
	static GsSafeObject<GsConfig>& Instance();
	
	/// \brief 将全局的配置保存为文件
	/// \param strFile 
	/// \return 
	static bool Save(const char* strFile);

	/// \brief 将全局的配置保存为字符串
	/// \return 
	static GsString Save();

	/// \brief 从xml或者配置中load配置信息
	/// \param strFileOrXML 
	/// \param bFile 
	/// \return 
	static bool Load(const char* strFileOrXML ,bool bFile = true);
};
typedef GsGlobalConfig GsGlobeConfig;
UTILITY_ENDNS