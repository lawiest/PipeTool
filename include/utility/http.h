#pragma once
#include "preconfig.h"  
#include "stringhelp.h"  
#include "memorymanager.h"
#include "vectorhelp.h"
#include "workthread.h"

UTILITY_NS
/// \brief http状态编码
enum GsHttpStatus{
	/// \brief 1xx 信息
	eCONTINUE = 100,
	eSWITCHING_PROTOCOLS = 101,
	ePROCESSING = 102,

	/// \brief 2xx 成功
	eOK = 200,
	eCREATED = 201,
	eACCEPTED = 202,
	eNON_AUTHORITATIVE_INFORMATION = 203,
	eNO_CONTENT = 204,
	eRESET_CONTENT = 205,
	ePARTIAL_CONTENT = 206,
	eMULTI_STATUS = 207,
	eIM_USED = 226,

	/// \brief 3xx 重定向
	eMULTIPLE_CHOICES = 300,
	eMOVED_PERMANENTLY = 301,
	eFOUND = 302,
	eSEE_OTHER = 303,
	eNOT_MODIFIED = 304,
	eUSE_PROXY = 305,
	eTEMPORARY_REDIRECT = 307,
	
	/// \brief 4xx 客户端错误
	eBAD_REQUEST = 400,
	eUNAUTHORIZED = 401,
	ePAYMENT_REQUIRED = 402,
	eFORBIDDEN = 403,
	eNOT_FOUND = 404,
	eMETHOD_NOT_ALLOWED = 405,
	eNOT_ACCEPTABLE = 406,
	ePROXY_AUTHENTICATION_REQUIRED = 407,
	eREQUEST_TIMEOUT = 408,
	eCONFLICT = 409,
	eGONE = 410,
	eLENGTH_REQUIRED = 411,
	ePRECONDITION_FAILED = 412,
	eREQUEST_ENTITY_TOO_LARGE = 413,
	eREQUEST_URI_TOO_LONG = 414,
	eUNSUPPORTED_MEDIA_TYPE = 415,
	eREQUESTED_RANGE_NOT_SATISFIABLE = 416,
	eEXPECTATION_FAILED = 417,
	eUNPROCESSABLE_ENTITY = 422,
	eLOCKED = 423,
	eFAILED_DEPENDENCY = 424,
	eUPGRADE_REQUIRED = 426,

	/// \brief 5xx 服务器错误
	eINTERNAL_SERVER_ERROR = 500,
	eNOT_IMPLEMENTED = 501,
	eBAD_GATEWAY = 502,
	eSERVICE_UNAVAILABLE = 503,
	eGATEWAY_TIMEOUT = 504,
	eHTTP_VERSION_NOT_SUPPORTED = 505,
	eINSUFFICIENT_STORAGE = 507,
	eNOT_EXTENDED = 510,
};
class GsHttpCallback
{
public:
	virtual ~GsHttpCallback(){}
	/// \brief 覆盖此方法以获取从服务下载的数据
	/// \param pData 
	/// \param nLen 
	/// \return 
	virtual bool OnData(const unsigned char* pData,int nLen) = 0;
	
	/// \brief 返回开始时发生
	/// \param header 
	/// \param status 
	/// \return 
	virtual bool OnResponse(const GsStringMap& header,GsHttpStatus status) = 0;

	/// \brief 返回开始时发生
	/// \return 
	virtual bool OnResponseComplete() = 0;
};
/// \brief http客户端
class GS_API GsHttpClient
{
	void* m_Handle;
	/// \brief 
	void FillHeaders();
	int m_TimeOut;
protected:
	GsHttpStatus m_Status;
	GsString	 m_Method;
	/// \brief http请求头。
	GsStringMap m_Headers, m_ResponseHeaders;
public:
	/// \brief 构造
	GsHttpClient();
	virtual ~GsHttpClient();

	/// \brief 获取请求的方法POST/GET
	/// \return 
	GsString Method();

	/// \brief 设置请求的方法POST/GET
	/// \param method 
	void Method(const char* method);

	/// \brief 请求头信息
	/// \return 
	GsStringMap& RequestHeaders();

	/// \brief 最近一次状态值
	/// \return 
	GsHttpStatus LastStatus();

	/// \brief 上传数据
	/// \param url 
	/// \param method 
	/// \param data 
	/// \param nLen 
	/// \param pCallBack 
	/// \return 
	GsHttpStatus Upload(const char* url, const char* method, const unsigned char* data, int nLen, GsHttpCallback* pCallBack);

	/// \brief 上传数据
	/// \param url 
	/// \param method 
	/// \param data 
	/// \param nLen 
	/// \return 
	Utility::GsString Upload(const char* url,const char* method,const unsigned char* data,int nLen);

	/// \brief 下载url地址返回内容为字符串数据
	/// \param url   要下载的url地址
	/// \return 
	Utility::GsString Download(const char* url);

	/// \brief 下载url地址返回内容为二进制数据
	/// \param url   要下载的url地址
	/// \param pOutputBuffer  输出数据的buffer
	/// \return 
	GsHttpStatus Download(const char* url,GsByteBuffer* pOutputBuffer);

	/// \brief 下载url地址返回内容为文件
	/// \param url   要下载的url地址
	/// \param file 输出数据的文件
	/// \return 
	GsHttpStatus Download(const char* url,const char* file);

	 
	/// \brief 启动回调下载，通过Callback回调
	/// \param url 
	/// \param pCallBack 
	/// \return 
	GsHttpStatus Download(const char* url,GsHttpCallback* pCallBack);
};


/// \brief URI协议类型
enum GsUriScheme
{
	/// \brief 文件地址
	eFileUri,
	/// \brief FTP地址
	eFtpUri,
	/// \brief Http地址
	eHttpUri,
	/// \brief Https地址
	eHttpsUri,
};
/// \brief 用于处理Uri地址信息
class GS_API GsUri
{
	GsString m_Uri;
public:
	/// \brief 指定将通讯协议方案同 URI 的地址部分分开的字符
	/// \return 
	static GsString SchemeDelimiter();
	/// \brief 协议头
	/// \param eScheme 
	/// \return 
	static GsString UriScheme(GsUriScheme eScheme);
	/// \brief 将字符串转换为它的转义表示形式。
	/// \param stringToEscape 
	/// \return 
	static GsString EscapeDataString(const char* stringToEscape);
	 
	/// \brief 将字符串转换为它的非转义表示形式。
	/// \param stringToEscape 
	/// \return 
	static GsString UnescapeDataString(const char* stringToEscape);
	
	/// \brief 构成一个Uri
	/// \param eScheme 
	/// \param host 
	/// \param path 
	/// \param query 
	/// \param nPort 
	/// \param user 
	/// \param pwd 
	/// \return 
	static GsUri MakeUri(GsUriScheme eScheme, const char* host, const char* path, const char* query = NULL, int nPort = -1, const char* user = NULL, const char* pwd = NULL);
	/// \brief 构成一个Uri
	/// \param eScheme 
	/// \param host 
	/// \param path 
	/// \param query 
	/// \param nPort 
	/// \param user 
	/// \param pwd 
	/// \return 
	static GsUri MakeUri(const char* eScheme, const char* host, const char* path, const char* query = NULL, int nPort = -1, const char* user = NULL, const char* pwd = NULL);

public:

	/// \brief 根据uri地址构造
	/// \param uriString 
	GsUri(const char* uriString);
	 
	/// \brief 根据基础路径和相对路径组成绝对Uri
	/// \param baseUri 
	/// \param relativeUri 
	GsUri(const GsUri& baseUri, const char* relativeUri);
	/// \brief 获取 URI 的绝对路径。
	/// \return 
	GsString AbsolutePath()const;
	/// \brief 获取绝对 URI。
	/// \return 
	GsString AbsoluteUri()const;
	/// \brief 获取服务器的域名系统 (DNS) 主机名或 IP 地址和端口号
	/// \return 
	GsString Authority()const; 
 
	/// \brief 获取转义 URI 片段。
	/// \return 
	GsString Fragment()const;
	/// \brief 获取此实例的主机部分
	/// \return 
	GsString Host()const;
	/// \brief 是否为绝对 URI
	/// \return 
	bool IsAbsoluteUri()const;
	/// \brief 指示 URI 的端口值是否为此方案的默认值
	/// \return 
	bool IsDefaultPort()const;
	/// \brief 指示指定的 Uri 是否为文件 URI
	/// \return 
	bool IsFile()const; 
	/// \brief 获取文件名的本地操作系统表示形式
	/// \return 
	GsString LocalPath()const;

	/// \brief 获取构造函数的原始 URI 字符串
	/// \return 
	GsString OriginalString()const;
	  
	/// \brief 获取用问号 (?) 分隔的 GsUri.AbsolutePath 和 GsUri.Query 属性
	/// \return 
	GsString PathAndQuery()const;
	
	
	/// \brief 获取此 URI 的端口号
	/// \return 
	int Port()const;
	/// \brief 获取指定 URI 中包括的任何查询信息
	/// \return 
	GsString Query()const;
	
	/// \brief 获取查询参数以K/V列表形式返回
	/// \return 
	GsStringMap QueryParameters() const;

	/// \brief 设置查询参数
	/// \param values 
	void QueryParameters(const GsStringMap& values);
	/// \brief 增加查询参数
	/// \param key 
	/// \param value 
	void AddQueryParameters(const char* key,const char* value);


	/// \brief 获取此 URI 的方案名称
	/// \return 
	GsString Scheme()const;
	
	/// \brief 获取包含构成指定 URI 的路径段的数组
	/// \return 
	GsVector<GsString> Segments()const;
  
	/// \brief 获取用户名、密码或其他与指定 URI 关联的特定于用户的信息
	/// \return 
	GsString UserInfo()const;
	/// \brief 获取用户名
	/// \return 
	GsString User()const;
	/// \brief 获取密码
	/// \return 
	GsString Password()const;

	
	/// \brief 确定当前的 GsUri 实例是否为指定 GsUri 实例的基。
	/// \param uri 
	/// \return 
	bool IsBaseOf(const GsUri& uri)const;
	
	/// \brief 指示用于构造此 System.Uri 的字符串是否格式良好，以及它是否不需要进一步转义。
	/// \return 
	bool IsWellFormedOriginalString()const;

	/// \brief 根据当前Uri和传入的Uri构造相对Uri
	/// \param uri 
	/// \return 
	GsUri MakeRelativeUri(const GsUri& uri)const;
	
	/// \brief 获取指定的 GsUri 实例的规范化字符串表示形式。
	/// \return 
	GsString ToString()const;
	
	/// \brief uri是否相等
	bool operator == (const GsUri& uri)const;
	/// \brief 是否不等
	bool operator != (const GsUri& uri)const;
	/// \brief 赋值
	GsUri& operator = (const GsUri& uri);
	/// \brief 赋值
	GsUri& operator = (const char* url);

};

/// \brief HTTP请求的的方法
enum GsHttpMethod
{
	/// \brief 请求指定的页面信息，并返回实体主体。
	eGET,
	/// \brief 类似于get请求，只不过返回的响应中没有具体的内容，用于获取报头
	eHEAD,
	/// \brief 向指定资源提交数据进行处理请求（例如提交表单或者上传文件）。数据被包含在请求体中。POST请求可能会导致新的资源的建立和 / 或已有资源的修改。
	ePOST,
	/// \brief 从客户端向服务器传送的数据取代指定的文档的内容。
	ePUT,
	/// \brief 从客户端向服务器传送的数据取代指定的文档的内容。
	eDELETE,
	/// \brief HTTP / 1.1协议中预留给能够将连接改为管道方式的代理服务器。
	eCONNECT,
	/// \brief 允许客户端查看服务器的性能。
	eOPTIONS,
	/// \brief 回显服务器收到的请求，主要用于测试或诊断。
	eTRACE,
	/// \brief 实体中包含一个表，表中说明与该URI所表示的原内容的区别。
	ePATCH,
	/// \brief 请求服务器将指定的页面移至另一个网络地址。
	eMOVE,
	/// \brief 请求服务器将指定的页面拷贝至另一个网络地址。
	eCOPY,
	/// \brief 请求服务器建立链接关系。
	eLINK,
	/// \brief 断开链接关系
	eUNLINK,
	/// \brief 允许客户端发送经过封装的请求。
	eWRAPPED,
}; 

/// \brief HTTP请求
class GS_API GsHttpRequest
{
protected:
	GsHttpRequest();
public:
	virtual ~GsHttpRequest();
	
	/// \brief http请求方法，GET,POST,PUT,DELTE等
	/// \return 
	virtual const char * Method() const = 0;

	/// \brief http请求方法，GET,POST,PUT,DELTE等
	/// \return 
	virtual GsHttpMethod MethodType() const;

	/// \brief http请求的完整Url地址
	/// \return 
	virtual GsUri Uri() const = 0;
	
	/// \brief http请求客户端的IP地址
	/// \return 
	virtual const char * ClientIP() const = 0;

	/// \brief http请求客户端发送的请求头
	/// \return 
	virtual const GsStringMap& Headers()const = 0;

	/// \brief 当方法为POST，PUT等方法时发送的内容
	/// \return 
	virtual const unsigned char* Content()const = 0;

	/// \brief Content的内容的字节长度
	/// \return 
	virtual int ContentLength()const = 0;
};

/// \brief HTTP响应
class GS_API GsHttpResponse
{
protected:
	GsHttpResponse();
public:
	virtual ~GsHttpResponse();

	/// \brief HTTP返回的状态值
	/// \param statusCode 
	virtual void StatusCode(GsHttpStatus statusCode) = 0;
	/// \brief 
	/// \return 
	virtual GsHttpStatus StatusCode() const = 0;

	/// \brief HTTP返回的状态的原因
	/// \param reason 
	virtual void ReasonPhrase(const char* reason) = 0;
	/// \brief 
	/// \return 
	virtual const char* ReasonPhrase() = 0;

	/// \brief 响应的头
	/// \return 
	virtual GsStringMap& Headers()= 0;

	/// \brief 设置返回的内容
	/// \param content 
	/// \param nLen 
	virtual void Content(const unsigned char* content, int nLen) = 0;

};

/// \brief http服务。
class GS_API GsHttpServer
{
protected:
	void* m_Handle;
	GsAtomic<int> m_Working;
	GsSignaler m_FinishSignaler;

	/// \brief 
	/// \param nc 
	/// \param ev 
	/// \param p 
	virtual bool OnProcessHttp(void* nc, int ev, void *p);
	/// \brief 
	/// \param nc 
	/// \param ev 
	/// \param p 
	virtual bool OnHandler(void* nc, int ev, void *p);
	/// \brief 
	/// \param request 
	/// \param response 
	/// \return 
	virtual bool OnHttpRequest(GsHttpRequest* request, GsHttpResponse* response);

	/// \brief 
	/// \return 
	bool Working(); 
public:
	/// \brief 
	/// \param port 
	GsHttpServer(int port);
	virtual ~GsHttpServer();
	
	/// \brief 停止服务
	/// \param bWait 
	void Shutdown(bool bWait = true);
	/// \brief 以阻塞函数的方式运行服务
	/// \return 
	bool RunServer();

};


/// \brief 虚拟文件路径
struct GS_API GsVirtualPath
{
	/// \brief 虚拟路径，用于标识
	GsString VirtualPath;
	/// \brief 正规化好虚拟路径，用于快速比较和标准化
	GsString RegularVirtualPath;

	/// \brief 映射的本地路径
	GsString LocalPath;

	/// \brief 是否允许列举目录结构
	bool EnableDirectoryListing;
	
	GsVirtualPath();
	/// \brief 
	/// \param virtualPath 
	/// \param localPath 
	GsVirtualPath(const char* virtualPath, const char* localPath);
	/// \brief 
	/// \param rhs 
	GsVirtualPath(const GsVirtualPath& rhs);

	/// \brief 是否有有效
	operator bool()const;

};

/// \brief 文件http服务。
class GS_API GsSimpleFileHttpServer:public GsHttpServer
{
	GsStlMap<GsString,GsVirtualPath> m_mapPath;
protected:
	/// \brief 
	/// \param nc 
	/// \param ev 
	/// \param p 
	virtual bool OnHandler(void* nc, int ev, void *p);

	/// \brief 
	/// \param request 
	/// \param response 
	/// \return 
	virtual bool OnHttpRequest(GsHttpRequest* request, GsHttpResponse* response);
public:
	/// \brief 
	/// \param port 
	GsSimpleFileHttpServer(int port);
	/// \brief 增加一个虚拟路径的映射
	/// \param path 
	/// \return 
	bool AddVirtualPath(const GsVirtualPath& path);
	/// \brief 已经映射的虚拟路径的数量
	/// \return 
	int Count();
	/// \brief 根据索引获取一个虚拟路径映射
	/// \param i 
	/// \return 
	GsVirtualPath VirtualPath(int i);
	/// \brief 根据虚拟路径的名称获取一个虚拟路径映射
	/// \param root 
	/// \return 
	GsVirtualPath VirtualPath(const char* root);
	/// \brief 删除一个虚拟路径
	/// \param root 
	void Remove(const char* root);
};


/// \brief 一个WebSocket会话
class GS_API GsWebSocketSession:public GsRefObject
{
protected:
	GsString m_UrlPath;
	GsStringMap m_QueryString;
	GsStringMap m_Headers;
	void* m_HandleSession;
	/// \brief 连接到一个远程WebSocket服务
	/// \param handle 
	GsWebSocketSession(void* handle);
public:
	virtual ~GsWebSocketSession();

	/// \brief WebSocket连接时的请路径
	/// \return 
	const char* UrlPath()const;

	/// \brief WebSocket连接时的请求查询参数
	/// \return 
	const GsStringMap& QueryString()const;

	/// \brief WebSocket连接时的请求头
	/// \return 
	const GsStringMap& Headers()const;

	/// \brief 是否连接成功了
	/// \return 
	bool IsConnected();

	/// \brief 发送一个数据包
	/// \param data 
	/// \param len 
	virtual void SendPackage(const unsigned char* data, int len);

	/// \brief 当接收到远程发送的数据包时发生
	/// \details 参数1 
	/// \details 参数2 
	/// \details 参数3 
	GsDelegate<void(GsWebSocketSession*,const unsigned char*,int)> OnPackage;
	/// \brief 当链接中断之后发生
	/// \details 参数1 
	/// \details 参数2 
	GsDelegate<void(GsWebSocketSession*, const char*)> OnShutdown;
};
/// \brief GsWebSocketSessionPtr
GS_SMARTER_PTR(GsWebSocketSession)

/// \brief WebSocket客户端。连接到远程WebSocket服务
class GS_API GsWebSocketClient:public GsWebSocketSession
{
	GsAtomic<int> m_Stop;
	void*		m_Handle;
	/// \brief 
	/// \param remote 
	/// \param port 
	/// \param path 
	/// \return 
	bool Connect(const char* remote, int port, const char* path);
public:
	/// \brief 连接到一个远程WebSocket服务
	/// \param remote 
	/// \param port 
	GsWebSocketClient(const char* remote,int port);
	/// \brief 
	/// \param remote 
	/// \param port 
	/// \param path 
	GsWebSocketClient(const char* remote, int port,const char* path);
	~GsWebSocketClient();

	
	/// \brief 运行一次消息泵
	void Pull();
	
	/// \brief 阻塞函数，一直运行消息泵直到停止
	void PullForever();

	/// \brief 运行PullForeve之后停止消息泵
	virtual void StopPull();
};
/// \brief GsWebSocketClientPtr
GS_SMARTER_PTR(GsWebSocketClient)

/// \brief WebSocket客户端。用后台线程驱动消息泵
class GS_API GsWebSocketClientThread :public GsWebSocketClient,GsWorkThread
{
protected:
	/// \brief 执行线程，实现此纯虚函数
	/// \return 返回执行是否成功
	virtual bool Execute();
public:
	/// \brief 
	/// \param server 
	/// \param port 
	GsWebSocketClientThread(const char* server, int port);
	/// \brief 
	/// \param server 
	/// \param port 
	/// \param path 
	GsWebSocketClientThread(const char* server, int port,const char* path);
	~GsWebSocketClientThread();
	/// \brief 运行PullForeve之后停止消息泵
	virtual void StopPull();

};

/// \brief GsWebSocketClientThreadPtr
GS_SMARTER_PTR(GsWebSocketClientThread)

/// \brief websocket服务
class GS_API GsWebSocketServer:public GsHttpServer
{
	GsRWLock m_Lock;
	GsStlMap<void*, GsWebSocketSessionPtr> m_Session;
protected:
	/// \brief 
	/// \param nc 
	/// \param ev 
	/// \param p 
	virtual bool OnHandler(void* nc, int ev, void *p);
	/// \brief 
	/// \param session 
	virtual void NewSession(GsWebSocketSession* session);
public:
	/// \brief 
	/// \param nPort 
	GsWebSocketServer(int nPort);
	~GsWebSocketServer();

	/// \brief 当新的WebSocket客户端连接上时发生。
	/// \details 参数1 
	GsDelegate<void(GsWebSocketSession*)> OnNewSession;
};
UTILITY_ENDNS
