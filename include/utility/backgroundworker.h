#pragma once
#include "preconfig.h"   
UTILITY_NS 

/// \brief 后台工作参数
class GS_API GsBackGroundParameter:public GsRefObject
{
protected:
	GsBackGroundParameter();
public:
	virtual ~GsBackGroundParameter();
};
/// \brief GsBackGroundParameterPtr 
GS_SMARTER_PTR(GsBackGroundParameter);

/// \brief 优先级别
enum GsPriorityLevel
{

	/// \brief 低优先级
	eLowPriorityLevel = 0,
	/// \brief 中优先级
	eMiddlePriorityLevel = 100,

	/// \brief 高优先级
	eHighPriorityLevel = 1000,

};
/// \brief 后台工作任务
class GS_API GsBackGroundTask :public GsRefObject
{
protected:
	GsBackGroundTask();
public:
	virtual ~GsBackGroundTask();
	
	/// \brief 任务id用于唯一标识，用于区分。
	virtual long long ID() = 0;

	/// \brief 优先级别
	virtual GsPriorityLevel PriorityLevel() = 0;
	
	/// \brief 执行工作任务
	virtual int Execute(GsBackGroundParameter* param) = 0;
};

/// \brief GsBackGroundTaskPtr 
GS_SMARTER_PTR(GsBackGroundTask);
 
/// \brief 后台工作队列，用于存储获取后台工作任务。
class GS_API GsBackGroundTaskQueue :public GsRefObject
{
protected:
	GsBackGroundTaskQueue();
public:
	virtual ~GsBackGroundTaskQueue();
	
	/// \brief 回收任务，任务完成后调用此方法回收资源
	virtual void Recycle(GsBackGroundTask* task) = 0;

	/// \brief 添加任务到队列
	virtual void Add(GsBackGroundTask* task) = 0;
	/// \brief 获取下一个工作任务
	virtual GsBackGroundTaskPtr  NextTask(GsPriorityLevel ePriority) = 0;
};

/// \brief GsBackGroundTaskQueuePtr 
GS_SMARTER_PTR(GsBackGroundTaskQueue);

/// \brief 后台工作队列
class GS_API GsBackGroundWorker:public GsWorkThread
{
	GsBackGroundParameterPtr m_ptrParameter;
	GsBackGroundTaskQueuePtr m_ptrTaskQueue;
	
	GsVector<std::shared_ptr<GsWorkThread> > m_vecWorkers;

	/// \brief 执行线程，实现此纯虚函数
	///\return 返回执行是否成功
	virtual bool Execute();
	virtual void CreateWorker(int index, GsPriorityLevel level);
public:
	GsBackGroundWorker();
	~GsBackGroundWorker();
	
	/// \brief 后台任务队列
	GsBackGroundTaskQueue* TaskQueue();
	/// \brief 后台任务队列
	void TaskQueue(GsBackGroundTaskQueue* queue);


	/// \brief 后台工作任务的全局参数
	GsBackGroundParameter* Parameter();
	/// \brief 后台工作任务的全局参数
	void Parameter(GsBackGroundParameter* param);

	/// \brief 添加任务到后台执行。
	virtual void Add(GsBackGroundTask* task);

	/// \brief 全局唯一的后台工作队列
	static GsBackGroundWorker& Default();

	/// \brief 从配置初始化
	virtual bool Initialize(const GsConfig& config);

};
 
UTILITY_ENDNS