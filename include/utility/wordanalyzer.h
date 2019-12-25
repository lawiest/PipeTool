﻿#pragma once
#include "preconfig.h" 
#include "object.h"
#include "stringhelp.h"

UTILITY_NS
/// \brief 字符分词器
class GS_API GsWordAnalyzer:public GsRefObject
{
public:
	GsWordAnalyzer(void);
	~GsWordAnalyzer(void);

	/// \brief 执行分词操作
	/// \param strText 输入字符串
	/// \param vecSubStr 分词后的子字符串
	/// \return 
	virtual bool Analyse(const char* strText, GsVector<GsString>& vecSubStr);
	/// \brief 分词的个数
	/// \param strText 输入字符串
	/// \return 返回分词的个数
	static int Analyse(const char* strText);

	/// \brief 执行分词操作
	/// \param strText 输入字符串
	/// \param vecSubStr 分词后的子字符串
	/// \return 
	virtual bool Analyse(const wchar_t* strText, GsVector<GsWString>& vecSubStr);
	/// \brief 分词的个数
	/// \param strText 输入字符串
	/// \return 返回分词的个数
	static int Analyse(const wchar_t* strText);
};
GS_SMARTER_PTR(GsWordAnalyzer);

/// \brief 简单规则分词器
class GS_API GsSimpleWordAnalyzer : public GsWordAnalyzer
{
public:
	GsSimpleWordAnalyzer(void);
	~GsSimpleWordAnalyzer(void);

	/// \brief 执行分词操作
	/// \param strText 输入字符串
	/// \param vecSubStr 分词后的子字符串
	/// \return 
	virtual bool Analyse(const char* strText, GsVector<GsString>& vecSubStr);

	/// \brief 执行分词操作
	/// \param strText 输入字符串
	/// \param vecSubStr 分词后的子字符串
	/// \return 
	virtual bool Analyse(const wchar_t* strText, GsVector<GsWString>& vecSubStr);

	/// \brief 设置对称字符规则
	/// \detail 多个组成字符串，格式例如<>[]{}()《》【】『』（）“”‘’''
	/// \param str 
	void PairChars(const char* str);

	/// \brief 设置连接字符规则
	/// \detail 多个组成字符串，格式例如-#
	/// \param str 
	void LinkChars(const char* str);

public:
	/// \brief 执行分析流程
	/// \param strIn 
	/// \param strOut 
	/// \return 
	bool DoAnalyseProcess(const wchar_t* strIn, wchar_t* strOut);
private:
	/// \brief 对称字符
	GsWString m_strPairs;
	/// \brief 连接字符
	GsWString m_strLineChars;
};
GS_SMARTER_PTR(GsSimpleWordAnalyzer);

UTILITY_ENDNS