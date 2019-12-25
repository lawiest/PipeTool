#pragma once
#include <utility.h>
#include "geodatabase.h"

KERNEL_NS
/// \brief 表达式上下文，用于计算表达式值时使用。
class GS_API GsExpressionContext
{
protected:
	GsExpressionContext();
public:
	virtual ~GsExpressionContext();

};
/// \brief 属性访问器,根据字段索引值访问属性数据
class GS_API GsIndexedAttributeVisitor:public GsExpressionContext
{
public:
	~GsIndexedAttributeVisitor();
	/// \brief 获取字段的Value
	/// \param n 
	/// \return 
	virtual UTILITY_NAME::GsAny Value(int n) = 0;
};

/// \brief 访问Row或Feature对象的属性
class GS_API GsRowAttributeVisitor:public GsIndexedAttributeVisitor
{
	GsRowPtr m_ptrRow;
public:
	GsRowAttributeVisitor();
	/// \brief 
	/// \param row 
	GsRowAttributeVisitor(GsRow* row);
	/// \brief 
	/// \param row 
	void Row(GsRow * row);
	/// \brief 
	/// \return 
	GsRow* Row();
	/// \brief 获取字段的Value
	/// \param n 
	/// \return 
	virtual UTILITY_NAME::GsAny Value(int n);
};

/// \brief 属性访问器,根据字段索引值访问属性数据
class GS_API GsNamedAttributeVisitor:public GsExpressionContext
{
public:
	~GsNamedAttributeVisitor();
	/// \brief 获取字段的Value
	/// \param col 
	/// \return 
	virtual UTILITY_NAME::GsAny Value(const char* col) = 0;
};
/// \brief 表达式操作类型
enum GsExpressionOperationType {
	eExpression_OR,
	eExpression_AND,
	eExpression_NOT,
	eExpression_EQ,
	eExpression_NE,
	eExpression_GE,
	eExpression_LE,
	eExpression_LT,
	eExpression_GT,
	eExpression_LIKE,
	eExpression_ISNULL,
	eExpression_IN,
	eExpression_BETWEEN,
	eExpression_ADD,
	eExpression_SUBTRACT,
	eExpression_MULTIPLY,
	eExpression_DIVIDE,
	eExpression_MODULUS,
	eExpression_CONCAT,
	eExpression_SUBSTR,
	eExpression_HSTORE_GET_VALUE,
	eExpression_AVG,
	eExpression_MIN,
	eExpression_MAX,
	eExpression_COUNT,
	eExpression_SUM,
	eExpression_CAST,
};

/// \brief 表达式类型
enum GsExpressionType {
	/// \brief 表达式为常数
	eExpression_CONSTANT,
	/// \brief 表达式为列
	eExpression_COLUMN,
	/// \brief 表达式为函数操作，具体操作参考GsExpressionOperationType
	eExpression_OPERATION,
};

/// \brief 表达式
class GS_API GsExpression :public UTILITY_NAME::GsRefObject
{
protected:
	GsExpressionOperationType m_eOPType;
	GsExpressionType			m_eType;
	UTILITY_NAME::GsAny			m_Value;
	UTILITY_NAME::GsVector<UTILITY_NAME::GsSmarterPtr<GsExpression> > m_Children;
	GsExpression();

	/// \brief 获取表达式计算的值
	/// \param context 
	/// \return 
	UTILITY_NAME::GsAny EvaluateInner(GsExpressionContext* context)const;
	/// \brief 
	/// \param context 
	/// \return 
	virtual UTILITY_NAME::GsAny OnColumnValue(GsExpressionContext* context)const;
public:
	/// \brief 根据表达式类型，操作类型和值进行构造
	/// \param eType 
	/// \param eOpType 
	/// \param any 
	GsExpression(GsExpressionType eType,GsExpressionOperationType eOpType,const UTILITY_NAME::GsAny& any);
	/// \brief 构造为列类型
	/// \param columnName 
	GsExpression(const char* columnName);
	/// \brief 构造为常数
	/// \param any 
	GsExpression(const UTILITY_NAME::GsAny& any);
	/// \brief 构造为操作类型
	/// \param eOpType 
	GsExpression(GsExpressionOperationType eOpType);
	virtual ~GsExpression();

	/// \brief 表达式类型
	/// \return 
	GsExpressionType Type()const;
	/// \brief 表达式操作类型
	/// \return 
	GsExpressionOperationType OperationType()const;
	/// \brief 表达式值
	/// \return 
	UTILITY_NAME::GsAny& Value();
	/// \brief 表达式值
	/// \return 
	const UTILITY_NAME::GsAny& Value()const;

	/// \brief 子表达式
	/// \return 
	UTILITY_NAME::GsVector<UTILITY_NAME::GsSmarterPtr<GsExpression> >& Children();
	/// \brief 子表达式
	/// \return 
	const UTILITY_NAME::GsVector<UTILITY_NAME::GsSmarterPtr<GsExpression> >& Children()const;


	/// \brief 获取表达式计算的值
	/// \param pAtt 
	/// \return 
	UTILITY_NAME::GsAny Evaluate(GsIndexedAttributeVisitor* pAtt)const;
	/// \brief 获取表达式计算的值
	/// \param pAtt 
	/// \return 
	UTILITY_NAME::GsAny Evaluate(GsNamedAttributeVisitor* pAtt)const;

	/// \brief 评估是否满足过滤条件
	/// \param pAtt 
	/// \return 
	bool Filter(GsIndexedAttributeVisitor* pAtt)const;
	/// \brief 评估是否满足过滤条件
	/// \param pAtt 
	/// \return 
	bool Filter(GsNamedAttributeVisitor* pAtt)const;

};
/// \brief GsExpressionPtr;
GS_SMARTER_PTR(GsExpression)


/// \brief 表达式序列化对象
class GS_API GsExpressionWriter :public UTILITY_NAME::GsRefObject
{
protected:
	GsExpressionWriter();
public:
	virtual ~GsExpressionWriter();
	/// \brief 写入表达式;
	/// \param exp 
	/// \return 
	virtual bool Write(GsExpression* exp) = 0;
};
/// \brief GsExpressionWriterPtr;
GS_SMARTER_PTR(GsExpressionWriter)


/// \brief 表达式序列化为OGC标准过滤条件（OGC Filter Encoding Standard）
class GS_API GsOGCFilterExpressionWriter :public GsExpressionWriter
{
	UTILITY_NAME::GsString m_NameSpace;
	tinyxml2::XMLDocument m_Doc;
	tinyxml2::XMLElement* m_root;
public:
	/// \brief 
	/// \param ns 
	GsOGCFilterExpressionWriter(const char* ns);
	/// \brief 
	/// \param ns 
	/// \param root 
	GsOGCFilterExpressionWriter(const char* ns, tinyxml2::XMLElement* root);
	
	/// \brief 
	/// \return 
	tinyxml2::XMLElement* RootElement();
	/// \brief 
	/// \return 
	tinyxml2::XMLDocument* Document();
	/// \brief 写入表达式;
	/// \param exp 
	/// \return 
	virtual bool Write(GsExpression* exp); 
};
/// \brief GsOGCFilterExpressionWriterPtr;
GS_SMARTER_PTR(GsOGCFilterExpressionWriter)

/// \brief 表达式序列化为MapBox的filter条件
class GS_API GsMapBoxFilterExpressionWriter :public GsExpressionWriter
{
	Json::Value m_Doc;
	Json::Value& m_Root;
public:
	GsMapBoxFilterExpressionWriter();
	/// \brief 
	/// \param val 
	GsMapBoxFilterExpressionWriter(Json::Value& val);
	/// \brief 
	/// \return 
	Json::Value& Root();

	/// \brief 写入表达式;
	/// \param exp 
	/// \return 
	virtual bool Write(GsExpression* exp);
};
/// \brief GsMapBoxFilterExpressionWriterPtr;
GS_SMARTER_PTR(GsMapBoxFilterExpressionWriter)


KERNEL_ENDNS
