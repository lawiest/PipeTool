#pragma once 

#include "preconfig.h" 

#include "dataio.h" 
#include "sqlite3.h" 
#include <iostream>

UTILITY_NS 

namespace Data{
	namespace Sqlite{

	/// \brief sqlite数据库加密的方式
	enum GsSqliteCodecType
	{
		/// \brief 未知加密方法
		eCodecUnknow=-1,
		/// \brief 未使用加密
		eCodecNone,
		/// \brief 使用wxsqlite的加密方法
		eCodecWxSqlite,
		/// \brief 使用sqlcipher1.1.8版本的加密方法
		eCodecSqlCipher1_1_8,
		/// \brief 使用sqlcipher2.0beta版本的加密方法
		eCodecSqlCipher2_0_beta,
		/// \brief 使用sqlcipher2.0be版本的加密方法
		eCodecSqlCipher2_0_be,
		/// \brief 使用sqlcipher2.0le版本的加密方法
		eCodecSqlCipher2_0_le,
		/// \brief 使用sqlcipher3.0版本的加密方法
		eCodecSqlCipher3_0,
		/// \brief 使用sqlcipher4.0版本的加密方法
		eCodecSqlCipher4_0,
	};
/// \brief sqlite数据库指针的封装。
class GS_API GsSqliteDatabase:public GsDatabase
{	
	GsSqliteCodecType m_eCodecType;
	 sqlite3 * m_pDB;
public:
	/// \brief 构造函数
	GsSqliteDatabase();
	/// \brief 
	/// \param filename 
	GsSqliteDatabase(const char *filename);
	
	/// \brief 使用密码和指定的加密技术打开或创建加密数据库
	/// \details 打开数据库时如果没有明确指定加密技术则会试探每种技术
	/// \details 创建数据库时如果没有明确指定加密技术则会使用eCodecSqlCipher4_0加密技术
	/// \details SqlCipher加密技术创建数据库时eCodecSqlCipher4_0版本
	/// \param filename 
	/// \param pwd 
	/// \param eCodecType 
	GsSqliteDatabase(const char *filename,const char* pwd, GsSqliteCodecType eCodecType);

	/// \brief 获取加密方法
	/// \return 
	GsSqliteCodecType CodecType();

	/// \brief 探测sqlite的加密方法
	/// \param filename 
	/// \param pwd 
	/// \return 
	static GsSqliteCodecType DetectCodecType(const char* filename,const char* pwd);

	virtual ~GsSqliteDatabase();
	/// \brief 转化成数据库指针
	operator sqlite3*() const;
	/// \brief 返回指针地址
	/// \return 
	sqlite3* DB() const;
	void Attach(sqlite3* db);	
	/// \brief 判断是否打开文件
	/// \return 
	virtual bool IsOpen()const ;
	/// \brief 执行操作
	/// \return 返回0 代表执行成功。
	/// \param strSQL 
	virtual int Execute(const char* strSQL);
	/// \brief 执行操作
	/// \param strSQL SQL语句 参见sqlite3_create_function使用方法
	/// \param strFuncName 要绑定的函数名
	/// \param SqliteCallback 绑定的函数
	/// \param pUserParam 传入的参数
	virtual int Execute(const char* strSQL, const char* strFuncName, const void* SqliteCallback, void* pUserParam);
	/// \brief 插入最后1行
	/// \return 
	virtual long long LastInsertRowID () const;
	/// \brief 判断是否关闭
	virtual bool Close();	 
	/// \brief 最后的消息
	/// \return 
	virtual GsString ErrorMessage();
	/// \brief 错误编号
	/// \return 
	virtual long long ErrorCode();
	/// \brief 判断是否读取失败
	/// \param nErrorCode 
	/// \return 
	static bool Error(long long nErrorCode);
	/// \brief 打断正在运行中的数据库命令
	/// \return 不支持打断操作的能力则返回false，成功打断或者无须打断都返回true
	virtual bool Interrupt();


	/// \brief 函数模板
	template<class T>
	/// \brief 
	/// \param nErrorCode 
	/// \param bOkValue 
	/// \param bFailValue 
	/// \return 
	T Error(int nErrorCode,T bOkValue,T bFailValue)
	{
		/// \brief 如果读取成功，返回成功的消息
		if(!Error(nErrorCode))
			return bOkValue;
		/// \brief 如果读取失败，返回失败的消息
		const char* strError = sqlite3_errmsg(m_pDB);
		std::cout<<strError <<std::endl;
		return bFailValue;
	}
	/// \brief 判断表是否存在
	/// \param tbName 
	/// \return 
	bool ExistTable(const char* tbName);

	/// \brief 判断索引是否存在
	/// \brief 索引名称
	/// \param strIndexName 
	/// \return 
	bool ExistIndex(const char* strIndexName);
};


class GS_API GsSqliteTransaction:private GsNoneCopyable
{
	GsSqliteDatabase* m_pDB;
public:
	/// \brief 构造函数
	/// \param pDB 
	GsSqliteTransaction(GsSqliteDatabase* pDB);
	/// \brief 析构函数
	virtual ~GsSqliteTransaction(); 
	/// \brief 提交数据
	virtual void Commit ();
	/// \brief 回滚数据
	virtual void Rollback();
};

/// \brief 包装Sqlite的stmt
class GS_API GsSqliteStatement:public GsStatement
{
protected:
	GsSqliteDatabase* m_SqliteDB;
	/// \brief 创建stmt指针
	sqlite3_stmt * m_pStmt;  
	int m_nRet; 
public:
	/// \brief 缺省构造函数
	GsSqliteStatement();
	/// \brief 构造函数重载
	/// \param db 
	/// \param sql 
	GsSqliteStatement(GsSqliteDatabase* db,const char* sql = NULL);
	/// \brief 准备执行
	/// \param db 
	/// \param sql 
	/// \return 
	virtual bool Prepare(GsDatabase* db,const char* sql);
	/// \brief 返回指针地址
	operator sqlite3_stmt*() {return m_pStmt;}
	/// \brief 析构函数
 	virtual ~GsSqliteStatement();
	/// \brief 
	void Close();
public: 
	/// \brief 判断指针是否为空
	/// \return 
	virtual bool IsNull();
	/// \brief 执行读取，返回多个结果
	/// \return 
	virtual int Execute();
	/// \brief 执行读取，返回1个结果
	/// \return 
	virtual int ExecuteQuery();
	/// \brief 读取下一条数据
	/// \return 
	virtual bool MoveNext();
	/// \brief 读取无符号字符数据
	/// \param nCol 
	/// \return 
	virtual const unsigned char* BlobValue(int nCol);
	/// \brief 读取32位整数数据
	/// \param nCol 
	/// \return 
	virtual int IntValue(int nCol);
	/// \brief 读取64位整数数据
	/// \param nCol 
	/// \return 
	virtual long long Int64Value(int nCol);
	/// \brief 读取64位浮点数据
	/// \param nCol 
	/// \return 
	virtual double DoubleValue(int nCol);
	/// \brief 返回当前列的值
	/// \param nCol 
	/// \return 
	virtual int ValueLength(int nCol); 
	/// \brief 绑定索引
	/// \param nIndex 
	/// \param pBlob 
	/// \param nLen 
	/// \param eType 
	/// \return 
	virtual int BindValue(int nIndex,const unsigned char* pBlob ,int nLen, GsFieldType eType);
	/// \brief 释放内存
	/// \return 
	virtual int Reset();
	/// \brief 获取查询结果的列数
	/// \return 
	virtual int ColumnCount();
	/// \brief 获取列的类型
	/// \param n 
	/// \return 
	virtual GsFieldType ColunmType(int n);
	/// \brief 获取列的名称
	/// \param n 
	/// \return 
	virtual GsString ColunmName(int n); 
	/// \brief 满足要求的记录数
	/// \return 
	virtual long long RecordCount();
	/// \brief 插入最后一行
	/// \return 
	long long LastInsertRowID();

}; 
}
}
UTILITY_ENDNS