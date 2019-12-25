﻿#pragma once
#include "../utility/preconfig.h"
#include "../utility/object.h"
#include "../utility/stringhelp.h"

KERNEL_NS

/// \brief 配置类，实现配置的读取和写入。
class GS_API GsScriptHost:public Utility::GsRefObject
{
protected:
	/// \brief 
	GsScriptHost() {}
public:
	virtual ~GsScriptHost(){}

	/// \brief 执行一段文本脚本
	/// \param script 
	/// \return 
	virtual int Execute(const char* script) = 0;

	/// \brief 重置脚本引擎为初始状态
	virtual void Reset() = 0;

	/// \brief 设置全局对象变量
	/// \param name 全局对象的名称
	/// \param ptr 全局对象的指针
	/// \param objecttype 全局对象的类型，例如GsPoint*
	virtual bool SetGlobalVariable(const char* name, void* ptr, const char* objecttype) = 0;

	/// \brief 设置全局引用对象变量
	/// \param name 全局对象的名称
	/// \param ref 全局对象的指针
	/// \param objecttype 全局对象的类型，例如GsPoint*
	/// \return 
	virtual bool SetRefObjectGlobalVariable(const char* name, Utility::GsRefObject* ref, const char* objecttype)=0;

	/// \brief 设置全局字符串变量
	/// \param name 全局变量的名称
	/// \param str 全局字符串变量的值
	/// \return 
	virtual bool SetGlobalVariable(const char* name, const char* str) = 0;

	/// \brief 设置全局整数变量
	/// \param name 全局变量的名称
	/// \param val 全局整数变量的值
	/// \return 
	virtual bool SetGlobalVariable(const char* name, int val) = 0;

	/// \brief 设置全局浮点数变量
	/// \param name 全局变量的名称
	/// \param val 全局浮点数变量的值
	/// \return 
	virtual bool SetGlobalVariable(const char* name, double val) = 0;

	/// \brief 获取特定对象类型的全局变量指针
	/// \param name 全局变量的名称
	/// \param objecttype 全局变量的类型
	virtual void* GetGlobalVariable(const char* name, const char* objecttype) = 0;

	/// \brief 获取整数的全局变量
	/// \param name 全局变量的名称
	/// \return 
	virtual int GetIntGlobalVariable(const char* name) = 0;

	/// \brief 获取字符串的全局变量
	/// \param name 全局变量的名称
	/// \return 
	virtual Utility::GsString GetStringGlobalVariable(const char* name) = 0;

	/// \brief 获取浮点数的全局变量
	/// \param name 全局变量的名称
	/// \return 
	virtual double GetDoubleGlobalVariable(const char* name) = 0;
};

/// \brief GsScriptHostPtr
GS_SMARTER_PTR(GsScriptHost);


/// \brief 
class GS_API GsLuaScriptHost:public GsScriptHost
{
	void* m_Host;
public:
	GsLuaScriptHost();
	~GsLuaScriptHost();

	/// \brief 执行一段文本脚本
	/// \param script 
	/// \return 
	virtual int Execute(const char* script);

	/// \brief 重置脚本引擎为初始状态
	virtual void Reset();

	/// \brief 设置全局对象变量
	/// \param name 全局对象的名称
	/// \param ptr 全局对象的指针
	/// \param objecttype 全局对象的类型，例如GsPoint*
	virtual bool SetGlobalVariable(const char* name, void* ptr, const char* objecttype);

	/// \brief 设置全局引用对象变量
	/// \param name 全局对象的名称
	/// \param ref 全局对象的指针
	/// \param objecttype 全局对象的类型，例如GsPoint*
	/// \return 
	virtual bool SetRefObjectGlobalVariable(const char* name, Utility::GsRefObject* ref, const char* objecttype);

	/// \brief 设置全局字符串变量
	/// \param name 全局变量的名称
	/// \param str 全局字符串变量的值
	/// \return 
	virtual bool SetGlobalVariable(const char* name,const char* str);

	/// \brief 设置全局整数变量
	/// \param name 全局变量的名称
	/// \param val 全局整数变量的值
	/// \return 
	virtual bool SetGlobalVariable(const char* name, int val);

	/// \brief 设置全局浮点数变量
	/// \param name 全局变量的名称
	/// \param val 全局浮点数变量的值
	/// \return 
	virtual bool SetGlobalVariable(const char* name, double val);
	
	/// \brief 获取特定对象类型的全局变量指针
	/// \param name 全局变量的名称
	/// \param objecttype 全局变量的类型
	virtual void* GetGlobalVariable(const char* name, const char* objecttype);

	/// \brief 获取整数的全局变量
	/// \param name 全局变量的名称
	/// \return 
	virtual int GetIntGlobalVariable(const char* name);

	/// \brief 获取字符串的全局变量
	/// \param name 全局变量的名称
	/// \return 
	virtual Utility::GsString GetStringGlobalVariable(const char* name);

	/// \brief 获取浮点数的全局变量
	/// \param name 全局变量的名称
	/// \return 
	virtual double GetDoubleGlobalVariable(const char* name);

	/// \brief 注册类厂对象
	static void RegisterClassFactory();
};

/// \brief GsLuaScriptHostPtr
GS_SMARTER_PTR(GsLuaScriptHost);
DECLARE_CLASS_CREATE(GsLuaScriptHost);

/// \brief 
class GS_API GsPythonScriptHost :public GsScriptHost
{
	void* m_Host;
public:
	GsPythonScriptHost();
	~GsPythonScriptHost();

	/// \brief 执行一段文本脚本
	/// \param script 
	/// \return 
	virtual int Execute(const char* script);

	/// \brief 重置脚本引擎为初始状态
	virtual void Reset();

	/// \brief 设置全局对象变量
	/// \param name 全局对象的名称
	/// \param ptr 全局对象的指针
	/// \param objecttype 全局对象的类型，例如GsPoint*
	virtual bool SetGlobalVariable(const char* name, void* ptr, const char* objecttype);

	/// \brief 设置全局引用对象变量
	/// \param name 全局对象的名称
	/// \param ref 全局对象的指针
	/// \param objecttype 全局对象的类型，例如GsPoint*
	/// \return 
	virtual bool SetRefObjectGlobalVariable(const char* name, Utility::GsRefObject* ref, const char* objecttype);

	/// \brief 设置全局字符串变量
	/// \param name 全局变量的名称
	/// \param str 全局字符串变量的值
	/// \return 
	virtual bool SetGlobalVariable(const char* name, const char* str);

	/// \brief 设置全局整数变量
	/// \param name 全局变量的名称
	/// \param val 全局整数变量的值
	/// \return 
	virtual bool SetGlobalVariable(const char* name, int val);

	/// \brief 设置全局浮点数变量
	/// \param name 全局变量的名称
	/// \param val 全局浮点数变量的值
	/// \return 
	virtual bool SetGlobalVariable(const char* name, double val);

	/// \brief 获取特定对象类型的全局变量指针
	/// \param name 全局变量的名称
	/// \param objecttype 全局变量的类型
	virtual void* GetGlobalVariable(const char* name, const char* objecttype);

	/// \brief 获取整数的全局变量
	/// \param name 全局变量的名称
	/// \return 
	virtual int GetIntGlobalVariable(const char* name);

	/// \brief 获取字符串的全局变量
	/// \param name 全局变量的名称
	/// \return 
	virtual Utility::GsString GetStringGlobalVariable(const char* name);

	/// \brief 获取浮点数的全局变量
	/// \param name 全局变量的名称
	/// \return 
	virtual double GetDoubleGlobalVariable(const char* name);

	/// \brief 注册类厂对象
	static void RegisterClassFactory();
	/// \brief 初始化python环境
	static void Initialized();
	/// \brief 是否初始化python环境
	static bool IsInitialized();
	/// \brief 反初始化python环境
	static void Finalize();
protected:
	//调用python模块函数
	int PyModuleRunFunction(const char *module, const char *function,
		const char *result_format, void *result, const char *args_format, ...);
};

/// \brief GsLuaScriptHostPtr
GS_SMARTER_PTR(GsPythonScriptHost);
DECLARE_CLASS_CREATE(GsPythonScriptHost);

KERNEL_ENDNS