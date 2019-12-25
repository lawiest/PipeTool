﻿#pragma once
#include "preconfig.h"  
#include "stringhelp.h"
UTILITY_NS

/// \brief 时间间隔
struct GS_API  GsTimeSpan
{
	/// \brief 时间间隔（秒	）
	long long TimeSpan;

	GsTimeSpan();
	/// \brief 
	/// \param rhs 
	GsTimeSpan(const GsTimeSpan& rhs);
	/// \brief 
	/// \param span 
	GsTimeSpan(long long span);
	/// \brief 
	/// \param day 
	/// \param hour 
	/// \param min 
	/// \param sec 
	GsTimeSpan(int day,int hour,int min,int sec);
	/// \brief 时间间隔的天数
	/// \return 
	int Days()const;
	/// \brief 时间间隔的总小时数
	/// \return 
	int TotalHours()const;
	/// \brief 时间间隔的小时数
	/// \return 
	int Hours()const;
	/// \brief 时间间隔的总分钟数
	/// \return 
	int TotalMinutes()const;
	/// \brief 时间间隔的分钟数
	/// \return 
	int Minutes()const;
	/// \brief 时间间隔的总秒数
	/// \return 
	int TotalSeconds()const;
	/// \brief 时间间隔的秒数
	/// \return 
	int Seconds()const;

	/// \brief 重载操作符
	operator long long ()const;
	 
	GsTimeSpan&  operator =(const GsTimeSpan& rhs);
	GsTimeSpan&  operator =(const long long span);
	bool operator ==(const GsTimeSpan& rhs)const;
	bool operator !=(const GsTimeSpan& rhs)const;
	bool operator >(const GsTimeSpan& rhs)const;
	bool operator <(const GsTimeSpan& rhs)const;
	bool operator <=(const GsTimeSpan& rhs)const;
	bool operator >=(const GsTimeSpan& rhs)const;

	GsTimeSpan operator +(const GsTimeSpan& rhs)const;
	GsTimeSpan operator -(const GsTimeSpan& rhs)const;

	GsTimeSpan& operator +=(const GsTimeSpan& rhs);
	GsTimeSpan& operator -=(const GsTimeSpan& rhs);
};
/// \brief 星期
enum GsWeekDay
{
	/// \brief 星期天
	eSunday,
	/// \brief 星期一
	eMonday,
	/// \brief 星期二
	eTuesday,
	/// \brief 星期三
	eWednesday,
	/// \brief 星期四
	eThursday,
	/// \brief 星期五
	eFriday,
	/// \brief 星期六
	eSaturday,
};
/// \brief 日期时间，缺省为UTC时间
/// \brief https://en.wikipedia.org/wiki/Coordinated_Universal_Time
struct GS_API GsDateTime
{
	/// \brief 从1970.1.1日经过的秒
	/// \detail 首先确定 【格林威治时间1970年01月01日00时00分00秒】 时间等于 【北京时间1970年01月01日08时00分00秒】
	/// \detail 时间戳：从上面的时间开始至现在的总秒数。
	/// \detail 1：time_t 类型就是实际的时间戳。也是内核中GsDateTime真正存储的long long Time。
	/// \detail 2：time_t now = time(0),也正好验证了时间戳的概念。返回的是当前时间戳。

	long long Time;
	/// \brief 缺省构造，当前时间,UTC时间
	GsDateTime();
	/// \brief 拷贝构造
	/// \param rhs 
	GsDateTime(const GsDateTime& rhs);
	/// \brief 从1970.1.1日经过的秒构造时间
	/// \param tm 
	/// \param bUTC 
	GsDateTime(long long tm,bool bUTC = true);
	/// \brief 根据年月日时分秒构造
	/// \param year 四位年yyyy
	/// \param mon  月[1~12]
	/// \param day  日[1~31]
	/// \param hour 时[0~23]
	/// \param min  分[0~59]
	/// \param sec  秒[0~59]
	GsDateTime(int year,int mon,int day,int hour,int min,int sec);
	
	/// \brief 当前时区偏移，单位秒
	/// \details 时区偏移是UTC时间到本地时间的时间差。比如正8区的时区偏移是-288000=-8*60*60
	/// \return 
	static long long TimeZone();
	
	/// \brief 当前时间，UTC时间
	/// \return 
	static GsDateTime Now();

	/// \brief 将当前时间当作本地时间转换为UTC时间
	/// \details 等价于当前时间减去时区偏移
	/// \return 
	GsDateTime ToUTC()const;

	/// \brief 将当前时间UTC时间转换为本地时间
	/// \details 等价于当前时间加上时区偏移
	/// \return 
	GsDateTime ToLocal()const;


	/// \brief 根据年月日时分秒构造
	/// \param year  四位年yyyy
	/// \param mon  月[1~12]
	/// \param day  日[1~31]
	/// \param hour 时[0~23]
	/// \param min  分[0~59]
	/// \param sec  秒[0~59]
	void MakeDateTime(int year,int mon,int day,int hour,int min,int sec);

	/// \brief 获取年
	/// \return 
	int Year()const;
	/// \brief 获取月
	/// \return 
	int Month()const;
	/// \brief 获取日
	/// \return 
	int Day()const;
	/// \brief 获取小时
	/// \return 
	int Hour()const;
	/// \brief 获取分
	/// \return 
	int Minute()const;
	/// \brief 获取秒
	/// \return 
	int Second()const;
	/// \brief 获取星期几
	/// \return 
	GsWeekDay DayOfWeek()const;
	 
	operator time_t()const;

	GsDateTime&  operator =(const long long tim);
	GsDateTime&  operator =(const GsDateTime& rhs);
	bool operator ==(const GsDateTime& rhs)const;
	bool operator !=(const GsDateTime& rhs)const;
	bool operator >(const GsDateTime& rhs)const;
	bool operator <(const GsDateTime& rhs)const;
	bool operator <=(const GsDateTime& rhs)const;
	bool operator >=(const GsDateTime& rhs)const;

	GsDateTime operator +(const GsTimeSpan& rhs)const;
	GsDateTime operator -(const GsTimeSpan& rhs)const;
	GsTimeSpan operator -(const GsDateTime& rhs)const;

	GsDateTime& operator +=(const GsTimeSpan& rhs);
	GsDateTime& operator -=(const GsTimeSpan& rhs);

	/// \brief 转换为长日期字符串
	/// \details 格式 %Y-%m-%d
	/// \return 
	GsString ToLongDateString()const;
	/// \brief 转换为长时间字符串
	/// \details 格式 %H:%M:%S
	/// \return 
	GsString ToLongTimeString()const;
	/// \brief 转换短日期字符串
	/// \details 格式 %Y/%m/%d
	/// \return 
	GsString ToShortDateString()const;
	/// \brief 转换短时间字符串
	/// \details 格式 %H:%M
	/// \return 
	GsString ToShortTimeString()const;
	/// \brief 转换字符串
	/// \details 格式 %Y-%m-%d %H:%M:%S
	/// \return 
	GsString ToString()const;
	/// \brief 按照格式转换为字符串
	/// \details 参考strftime
	/// http://www.cplusplus.com/reference/ctime/strftime/
	//%a 星期几的简写
	//%A 星期几的全称
	//%b 月份的简写
	//%B 月份的全称
	//%c 标准的日期的时间串
	//%C 年份的前两位数字
	//%d 十进制表示的每月的第几天
	//%D 月/天/年
	//%e 在两字符域中，十进制表示的每月的第几天
	//%F 年-月-日
	//%g 年份的后两位数字，使用基于周的年
	//%G 年份，使用基于周的年
	//%h 简写的月份名
	//%H 24小时制的小时
	//%I 12小时制的小时
	//%j 十进制表示的每年的第几天
	//%m 十进制表示的月份
	//%M 十时制表示的分钟数
	//%n 新行符
	//%p 本地的AM或PM的等价显示
	//%r 12小时的时间
	//%R 显示小时和分钟：hh:mm
	//%S 十进制的秒数
	//%t 水平制表符
	//%T 显示时分秒：hh:mm:ss
	//%u 每周的第几天，星期一为第一天 （值从1到7，星期一为1）
	//%U 第年的第几周，把星期日作为第一天（值从0到53）
	//%V 每年的第几周，使用基于周的年
	//%w 十进制表示的星期几（值从0到6，星期天为0）
	//%W 每年的第几周，把星期一做为第一天（值从0到53）
	//%x 标准的日期串
	//%X 标准的时间串
	//%y 不带世纪的十进制年份（值从0到99）
	//%Y 带世纪部分的十制年份
	//%z，%Z 时区名称，如果不能得到时区名称则返回空字符。
	//%% 百分号
	/// \brief 
	/// \param format 
	/// \return 
	GsString ToString(const char* format)const;
	
	/// \brief 解析字符串时间为时间数据
	/// \param strTime 
	/// \param result 
	/// \return 
	static bool TryParse(const char* strTime,GsDateTime& result);

	/// \brief 当前cpu时钟周期
	/// \return 
	static unsigned long long TickCount();

};

/// \brief 时间标准类型
enum GsDateTimeType
{
	/// \brief UTC时间表示法
	eUTCTime,
	/// \brief 本地时间
	eLocalTime,
};

/// \brief 标记了类型的日期
struct GS_API GsSignedDateTime:public GsDateTime
{
	/// \brief 时间类型
	GsDateTimeType Type;
	
	/// \brief 
	/// \param t 
	GsSignedDateTime(GsDateTimeType t = eLocalTime);
	/// \brief 
	/// \param tim 
	/// \param t 
	GsSignedDateTime(long long tim,GsDateTimeType t = eLocalTime);
	/// \brief 
	/// \param o 
	GsSignedDateTime(const GsSignedDateTime& o);
	/// \brief 
	/// \param o 
	GsSignedDateTime(GsSignedDateTime&& o);
	 
	GsSignedDateTime&  operator =(const GsSignedDateTime& rhs); 

	GsSignedDateTime&  operator =(GsSignedDateTime&& rhs);
	bool operator ==(const GsSignedDateTime& rhs);
	 

};

/// \brief 高精度计时器
class GS_API GsStopWatch
{
	volatile double   m_dblFrequency;
	volatile long long m_nLowPart;
	volatile long long m_nHighPart;
public:
	/// \brief 构造
	/// \param bStart 
	GsStopWatch(bool bStart = false);
	virtual ~GsStopWatch();

	/// \brief 计时器是否已经开始工作了
	/// \return 
	bool IsStarted()const;

	/// \brief 启动计时器
	/// \return 
	bool Start();

	/// \brief 经过的时间（单位秒）
	/// \return 
	double EscapedSecond()const;
	 
	/// \brief 经过的时间（单位毫秒）
	/// \return 
	double EscapedMillisecond()const;

	/// \brief 经过的时间（单位纳秒）
	/// \return 
	double EscapedNanosecond()const;
};

/// \brief 计时器跟踪者，当时间超过约定时间则通知到期
class GS_API GsTimeTracker
{
	int m_nPeriod;
	UTILITY_NAME::GsStopWatch m_Watch;
public:
	/// \brief 毫秒构造，小于等于0则标识没有期限限制。
	/// \param nPeriodByMillisecond 
	GsTimeTracker(int nPeriodByMillisecond = -1);
	/// \brief 时间是否到期了
	/// \return 
	bool IsExpire()const;
	/// \brief 时间是否到期了
	operator bool()const;
};

UTILITY_ENDNS
