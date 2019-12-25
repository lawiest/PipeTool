#pragma once
#include <utility.h>
#include "geodatabase.h"
#include "expression.h"
KERNEL_NS



/// \brief Where子句解析器
class GS_API  GsWhereClauserParser
{
	void * m_Handle;
protected:
	GsFields  m_Fields;
public:
	GsWhereClauserParser();
	/// \brief 
	/// \param fs 
	GsWhereClauserParser(const GsFields& fs);
	virtual ~GsWhereClauserParser();

	/// \brief 设置字段结构
	/// \param fs 
	void Fields(const GsFields& fs);

	/// \brief 获取字段结构
	/// \return 
	const GsFields& Fields()const;
	
	/// \brief 获取解析出来的表达式对象
	/// \return 
	GsExpressionPtr Expression();
	
	/// \brief 重置解析状态。
	void Reset();

	/// \brief 解析子句
	/// \param strWhere 
	/// \return 
	bool Parse(const char* strWhere);

	/// \brief 解析是否成功
	/// \return 
	bool IsParseSucceed();

};
KERNEL_ENDNS
