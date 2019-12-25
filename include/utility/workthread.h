#pragma once
#include "preconfig.h" 
#include "locker.h"
#include "stringhelp.h"
#include "object.h" 

UTILITY_NS

/// \brief 后台任务，会以异步的方式执行
class GS_API GsBackgroundTask :public GsRefObject
{
protected:
	GsBackgroundTask();
	volatile bool m_bCancel;
public:
	virtual ~GsBackgroundTask();

	/// \brief 执行任务
	virtual void ExecuteTask() = 0;

	/// \brief 
	virtual void Cancel();
};
/// \brief GsBackgroundTaskPtr
GS_SMARTER_PTR(GsBackgroundTask);

/// \brief 工作线程，通过继承工作线程类，实现类对多线程的支持
class GS_API GsWorkThread
{
	void* m_Wait;
	unsigned long long m_ThreadID;
	GsAtomic<int> m_Working;
	GsAtomic<int> m_Shutdown;
protected:
	GsString	m_ThreadName;
	
	void* m_pThread;
	/// \brief 
	/// \return 
	int OnThread();
public:
	/// \brief 
	/// \param name 
	GsWorkThread(const char* name = NULL);

	virtual ~GsWorkThread();
	/// \brief 启动线程
    /// \return 返回执行是否成功
	virtual bool StartThread();

	/// \brief 实现是否在执行
    /// \return 返回实现是否在执行
	virtual bool IsWorking();

	/// \brief 发送关闭线程的通知，或等待线程结束
	/// \param bWaitFinish 是否等待线程结束
	/// \return 返回是否成功
	virtual bool Shutdown(bool bWaitFinish = true);

	
	/// \brief 获取线程的ID
    /// \return 返回线程的ID
	virtual unsigned long long ThreadID();

	/// \brief 是否需要停止，在Execute函数中判断线程是否接受到了外部的停止通知
	/// \brief 调用Shutdown方法后ShouldStop会返回true
    /// \return 如果线程可以结束了则返回true
	virtual bool ShouldStop();

	/// \brief 发送关闭线程的通知后等待线程结束
    /// \return 返回是否成功
	virtual bool Wait();

	/// \brief 执行线程，实现此纯虚函数
    /// \return 返回执行是否成功
	virtual bool Execute() = 0;
public:

	/// \brief 使线程挂起一段时间
	/// \param nMicroSecond 
	static void Sleep(int nMicroSecond);

	/// \brief 当前线程的ID
	/// \return 
	static unsigned long long CurrentThreadID();
	
	/// \brief 当前逻辑CPU的数量
	/// \return 
	static int LogicCPUCount();

	/// \brief 异步执行一次回调。
	/// \details 参数1 
	static int SingleShot(GsDelegate<void(void*)>& cb, void* userData);

	/// \brief 异步执行一次回调。
	/// \param void 
	static int SingleShot(void(*CB)(void*data), void* userData);

	/// \brief 异步执行一次回调。
	/// \param task 
	/// \return 
	static int SingleShot(GsBackgroundTask* task);

};
/// \brief 后台,用于异步多线程的方式执行后台任务
class GS_API GsBackground:public GsRefObject
{
	GsSafeObject<GsList<GsBackgroundTaskPtr>> m_ListTask;
	GsList<GsWorkThread*> m_ListWorker;
	GsRWLock m_Lock;
	int m_nMin;
	int m_nMax;
public:
	/// \brief 
	/// \param nMin 
	/// \param nMax 
	GsBackground(int nMin=1, int nMax=10);
	~GsBackground();

	/// \brief 添加一个用于后台执行的任务
	/// \param task 
	void AddTask(GsBackgroundTask* task);
	/// \brief 关闭所有后台工人。停止执行任务
	void Shutdown();

};
/// \brief GsBackgroundPtr
GS_SMARTER_PTR(GsBackground);

UTILITY_ENDNS