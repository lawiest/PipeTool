#pragma once 
#include "preconfig.h" 
#include <iostream>
#include "stringhelp.h"
#include "listhelp.h"
UTILITY_NS 


/// \brief xml流式读取
/// \details 分段从Read方法读取xml片段，并逐渐将完整xml解析出来。
/// \details 通过继承GsXmlReader类副高OnXXX方法实现对xml的解析。
class GS_API GsXmlReader
{
	void* m_pParserHandle;
protected:
	int		m_nDepth;
public:
	GsXmlReader();
	virtual ~GsXmlReader();

	/// \brief xml节点的属性
	class  ElementAttribute
	{
	public:
		virtual int AttributeCount()  = 0;
		virtual const char* Name(int index)  = 0;
		virtual const char* Value(int index)  = 0;
		virtual const char** AttributePtr() = 0;
	};

	/// \brief 文档解析深度
	/// \return 
	int Depth();
	/// \brief 设置文档解析深度
	/// \param nDepth 
	void Depth(int nDepth);

	/// \brief 将解析器恢复为缺省状态。
	void Reset();

	/// \brief 当刚开始解析xml时发生。
	virtual void OnBegin();
	/// \brief 当完整解析xml后发生。
	virtual void OnEnd();

	/// \brief 当元素开始时发生
	/// \param pEleName 
	/// \param pAtt 
	virtual void OnElementBegin(const char* pEleName,ElementAttribute* pAtt);
	/// \brief 当元素结束时发生
	/// \param pEleName 
	virtual void OnElementEnd(const char* pEleName);

	/// \brief 当CData元素开始时发生
	virtual void OnCDataBegin();
	/// \brief 当CData元素结束时发生
	virtual void OnCDataEnd();

	/// \brief 当读取注释时发生
	/// \param strComment 
	virtual void OnComment(const char* strComment);
	/// \brief 读取到ElementContent时发生
	/// \param Comment 
	/// \param nLen 
	virtual void OnElementContent(const char* Comment,int nLen);
	/// \brief 当开始一个文档声明时发生
	/// \param doctypeName 
	/// \param sysid 
	/// \param pubid 
	virtual void OnStartDoctypeDecl(const char* doctypeName, const char* sysid,const char* pubid);
	/// \brief 当结束一个文档声明时发生
	virtual void OnEndDoctypeDecl();
	/// \brief 但发生错误时发生
	/// \param errStr 
	/// \param nErr 
	virtual void OnError(const char* errStr,int nErr);
	/// \brief 读取一个xml片段。
	/// \details 分段读取xml片段，解析整个xml
	/// \param strXMLPiece 
	/// \param bIsFinal 
	/// \return 
	virtual bool Read(const char* strXMLPiece,bool bIsFinal = false);
};

/// \brief xml流式写入
class GS_API GsXmlWriter
{
	std::ostream& m_Stream;
	GsStack<GsString> m_Stack;
	int m_nFlag;
	int m_nDepth;
public:
	/// \brief 构造函数
	/// \param stream 输出流。
	GsXmlWriter(std::ostream& stream);
	virtual ~GsXmlWriter();
	
	/// \brief 已经写入的xml的深度
	/// \return 
	int Depth();

	/// \brief 直接写入xml片段到xml流中
	/// \param xml 
	void WriteXml(const char* xml);

	/// \brief 开始一个文档
	/// \param version 
	/// \param encoding 
	void WriteStartDocument(const char* version, const char* encoding);
	/// \brief 结束写入一个文档
	void WriteEndDocument();

	/// \brief 开始一个元素
	/// \param name 
	void WriteStartElement(const char* name);
	/// \brief 写入元素的字符串
	/// \param value 
	void WriteElementString(const char* value);
	/// \brief 结束一个元素
	void WriteEndElement();
	/// \brief 写入一个元素
	/// \param name 
	/// \param value 
	void WriteAttribute(const char* name ,const char* value);
	/// \brief 写入一个注释
	/// \param value 
	void WriteComment(const char* value);
	/// \brief 写入一个CDATA
	/// \param value 
	void WriteCData(const char* value);
};

UTILITY_ENDNS