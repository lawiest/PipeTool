#pragma once
#include "utility.h"

class MyFFmpeg;

/// \brief 纹理
class GS_API GsTexture : public UTILITY_NAME::GsRefObject
{
public:
	GsTexture();
	GsTexture(UTILITY_NAME::GsImage* ptrImage);
	virtual ~GsTexture();

	/// \brief 获取纹理图片
	UTILITY_NAME::GsImage* Image();
	/// \brief 设置纹理图片
	void Image(UTILITY_NAME::GsImage* ptrImage);

	/// \brief 获取纹理图片哈希值
	unsigned long long Hash();

private:
	UTILITY_NAME::GsImagePtr m_ptrImage;
	unsigned long long m_hHash;
};
GS_SMARTER_PTR(GsTexture);

/// \brief 纹理数据源抽象类
class GS_API GsTextureSource : public UTILITY_NAME::GsRefObject
{
public:
	GsTextureSource();
	virtual ~GsTextureSource();

	/// \brief 获取下一张
	virtual GsTexturePtr Next() = 0;
};
GS_SMARTER_PTR(GsTextureSource);

/// \brief gif纹理数据源
class GS_API GsGifTextureSource : public GsTextureSource
{
public:
	GsGifTextureSource(UTILITY_NAME::GsString gstrFile);
	virtual ~GsGifTextureSource();

	/// \brief 获取下一张
	virtual GsTexturePtr Next();

	/// \brief 获取帧间时间间隔(单位毫秒)
	int TimeSpan();
	/// \brief 设置帧间时间间隔(单位毫秒)
	void TimeSpan(int nSpan);

private:
	UTILITY_NAME::GsGIFImageDecoderPtr m_ptrGifDecoder;
	int m_nFrameIndex;
	int m_nTimeSpan;
	long long m_preTime;
};
GS_SMARTER_PTR(GsGifTextureSource);

/// \brief 静态纹理数据源，可以手工添加多张纹理和对应时间进行播放
class GS_API GsStaticTextureSource : public GsTextureSource
{
	struct TimeSpanImage
	{
		TimeSpanImage() { m_ptrImage = NULL; m_nTime = 0; }
		TimeSpanImage(UTILITY_NAME::GsImagePtr ptrImage, int nTime)
		{
			m_ptrImage = ptrImage;
			m_nTime = nTime;
		}

		UTILITY_NAME::GsImagePtr m_ptrImage;
		int m_nTime;
	};

public:
	GsStaticTextureSource();
	virtual ~GsStaticTextureSource();

	/// \brief  添加视频帧
	/// \param ptrImage 图片
	/// \param nTimeSpan 时间间隔
	void AddImage(UTILITY_NAME::GsImage* ptrImage,int nTimeSpan);
	/// \brief 暂停
	void Pause();
	/// \brief 播放
	void Play();
	/// \brief 跳帧
	void Seek(int nIndex);
	/// \brief 获取下一张
	virtual GsTexturePtr Next();
	/// \帧间时间间隔(单位毫秒)
	int TimeSpan();

private:
	int m_nCnt;
	int m_nFrameIndex;
	int m_nTimeSpan;
	bool m_bIsPlay;
	long long m_preTime;

	std::map<int, TimeSpanImage> m_mImage;
};
GS_SMARTER_PTR(GsStaticTextureSource);


/// \brief 视频纹理数据源抽象类
class GS_API GsVideoTextureSource : public GsTextureSource
{
public:
	GsVideoTextureSource();
	virtual ~GsVideoTextureSource();

	/// \brief 获取下一张
	virtual GsTexturePtr Next();

	/// \原始视频帧，例如gif或者视频文件原始帧间时间间隔(单位毫秒)
	int OriginTimeSpan();

	/// \brief 设置用户自定义时间间隔(单位毫秒)，可以通过设置这个值来达到快进或慢放效果
	void TimeSpan(int nSpan) {};
	/// \brief 获得用户自定义时间间隔(单位毫秒)，内部会优先使用这个时间间隔
	int TimeSpan() { return 0; };

private:
	MyFFmpeg* m_ffmpeg;
};
GS_SMARTER_PTR(GsVideoTextureSource);
