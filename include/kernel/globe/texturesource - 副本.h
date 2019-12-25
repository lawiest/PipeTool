#pragma once
#include "utility.h"

class MyFFmpeg;

/// \brief ����
class GS_API GsTexture : public UTILITY_NAME::GsRefObject
{
public:
	GsTexture();
	GsTexture(UTILITY_NAME::GsImage* ptrImage);
	virtual ~GsTexture();

	/// \brief ��ȡ����ͼƬ
	UTILITY_NAME::GsImage* Image();
	/// \brief ��������ͼƬ
	void Image(UTILITY_NAME::GsImage* ptrImage);

	/// \brief ��ȡ����ͼƬ��ϣֵ
	unsigned long long Hash();

private:
	UTILITY_NAME::GsImagePtr m_ptrImage;
	unsigned long long m_hHash;
};
GS_SMARTER_PTR(GsTexture);

/// \brief ��������Դ������
class GS_API GsTextureSource : public UTILITY_NAME::GsRefObject
{
public:
	GsTextureSource();
	virtual ~GsTextureSource();

	/// \brief ��ȡ��һ��
	virtual GsTexturePtr Next() = 0;
};
GS_SMARTER_PTR(GsTextureSource);

/// \brief gif��������Դ
class GS_API GsGifTextureSource : public GsTextureSource
{
public:
	GsGifTextureSource(UTILITY_NAME::GsString gstrFile);
	virtual ~GsGifTextureSource();

	/// \brief ��ȡ��һ��
	virtual GsTexturePtr Next();

	/// \brief ��ȡ֡��ʱ����(��λ����)
	int TimeSpan();
	/// \brief ����֡��ʱ����(��λ����)
	void TimeSpan(int nSpan);

private:
	UTILITY_NAME::GsGIFImageDecoderPtr m_ptrGifDecoder;
	int m_nFrameIndex;
	int m_nTimeSpan;
	long long m_preTime;
};
GS_SMARTER_PTR(GsGifTextureSource);

/// \brief ��̬��������Դ�������ֹ���Ӷ�������Ͷ�Ӧʱ����в���
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

	/// \brief  �����Ƶ֡
	/// \param ptrImage ͼƬ
	/// \param nTimeSpan ʱ����
	void AddImage(UTILITY_NAME::GsImage* ptrImage,int nTimeSpan);
	/// \brief ��ͣ
	void Pause();
	/// \brief ����
	void Play();
	/// \brief ��֡
	void Seek(int nIndex);
	/// \brief ��ȡ��һ��
	virtual GsTexturePtr Next();
	/// \֡��ʱ����(��λ����)
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


/// \brief ��Ƶ��������Դ������
class GS_API GsVideoTextureSource : public GsTextureSource
{
public:
	GsVideoTextureSource();
	virtual ~GsVideoTextureSource();

	/// \brief ��ȡ��һ��
	virtual GsTexturePtr Next();

	/// \ԭʼ��Ƶ֡������gif������Ƶ�ļ�ԭʼ֡��ʱ����(��λ����)
	int OriginTimeSpan();

	/// \brief �����û��Զ���ʱ����(��λ����)������ͨ���������ֵ���ﵽ���������Ч��
	void TimeSpan(int nSpan) {};
	/// \brief ����û��Զ���ʱ����(��λ����)���ڲ�������ʹ�����ʱ����
	int TimeSpan() { return 0; };

private:
	MyFFmpeg* m_ffmpeg;
};
GS_SMARTER_PTR(GsVideoTextureSource);
