#pragma once
#include "kernel.h"
#include "utility.h"
#include "tracker.h"


GLOBE_NS
/// \brief ���㷽ʽ
enum GsMeasureMode
{
	eMeasureNull = 0,
	//�ر�������1
	eSurfaceLength,
	//�ռ䳤������2
	eSpaceLength,
	//�ر��������3
	eSurfaceArea,
	//�ռ��������4
	eSpaceArea,
	//�߶�����5
	eAltitude,
	//���ڷ�����6
	eCutFillVolumn,
	//��ˮ��û7
	eFlood,
	//�������8
	eSectionAnalysis,
	//���շ���9
	eSunAnalysis,
	//�������10
	eOnePointAnalyse,
	//����ͨ��11
	eTwoPointAnalyse,
	//���ͨ��12
	eMultiPointAnalyse,
	//����ͷ����13
	eCameraAnalyse,
	//�̲߳�ѯ14
	eQueryAltitude,
	//�¶Ȳ�ѯ15
	eQuerySlope,
	//�������16
	eSlopeAnalyse,
	// �״����17
	eRadarAnalyse,
	//���������18
	eViewShedAnalyse,
	// ����߷���19
	eSkylineAnalysis,
	// �޸߷���20
	eHeightLimitAnalysis
};


/// \brief ���������
class GS_API GsMeasureAnalyzer : public UTILITY_NAME::GsRefObject
{
	//  ������ʽ
	GsMeasureMode m_eMode;
	// ���Ŷ���
	UTILITY_NAME::GsVector<KERNEL_NAME::GsSymbolPtr> m_vtSymbolBox;
	
	// �������߻���
	UTILITY_NAME::GsStlMap< GsMeasureMode, GsTrackerPtr > m_mapMeasureTool;

	GsTracker* m_pTracker;
public:
	GsMeasureAnalyzer(KERNEL_NAME::GsPyramid* pPym = 0);
	virtual ~GsMeasureAnalyzer();

	/// \brief ���������
	virtual void ClearResult();

	/// \brief ����ģʽ
	void MeasureMode(GsMeasureMode eMode);
	GsMeasureMode MeasureMode() { return m_eMode; }

	/// \brief ��ǰ�켣����
	GsTracker* CurrentTracker() { return m_pTracker; }

private:
	/// \brief ��ȡ����
	KERNEL_NAME::GsSymbol* GetSymbol(GsMeasureMode eMode, bool bRefreshSymbol);

	// ��ȡ��������
	GsTracker* GetTrackerTool(GsMeasureMode eMode);

	/// \brief ��������߲���
	void SetSkylineParam();

};
GS_SMARTER_PTR(GsMeasureAnalyzer);

/// \brief ����ͨ�ӷ�������
class GsTwoPointAnalysis : public UTILITY_NAME::GsRefObject
{
public:
	/// \brief ����ͨ�ӷ�������¼�
	UTILITY_NAME::GsDelegate<void(const KERNEL_NAME::GsRawPoint3D&, const KERNEL_NAME::GsRawPoint3D&, const KERNEL_NAME::GsRawPoint3D&)> TwoPointAnalyseEventHandler;
};
GS_SMARTER_PTR(GsTwoPointAnalysis);

/// \brief ��ˮ��û��������
class GsFloodAnalysis : public UTILITY_NAME::GsRefObject
{
public:
	/// \brief ��ˮ��û��������¼���������С�̡߳��������߳�,�Ƿ��ǵ��θ̷߳�Χ��
	/// \breif ���bool����Ϊfalse��double������ʾ(��ˮ�������ˮ�߶�)
	UTILITY_NAME::GsDelegate<void(double, double, bool, bool bComplete)> FloodAnalyseEventHandler;

	/// \brief ��ʼ����
	/// \params dStepHeight ��ˮÿ�����߸߶�
	virtual bool Start(double dStepHeight) = 0;

	// ֹͣ
	virtual void Stop() = 0;

	// ������û�߶�
	virtual void FloodElevation(double dH) = 0;
	// ��ȡ��û�߶�
	virtual double FloodElevation() = 0;
};

/// \brief �����������
class GsSectionAnalysis : public UTILITY_NAME::GsRefObject
{
public:
	/// \brief ������Ϣί�ж���, 
	// ������1.�����в�ֺ�ĸ��߶εĳ���; 2.�����в�ֺ�ĸ��߶ε�ĩ�˵�ĸ߳�;
	UTILITY_NAME::GsDelegate<void(std::vector<double>&, std::vector<double>&, std::vector<GsRawPoint3D>&)> SectionAnalysisEventHandler;
};
GS_SMARTER_PTR(GsSectionAnalysis);


/// \brief ���ڷ���������
class GsCutFillAnalysis : public UTILITY_NAME::GsRefObject
{
public:
	/// \brief ���ڷ���Ϣί�ж���, 
	// ������1.�; 2.�ڷ�;2.��С�߶�;2.���߶�;2.���ڷ���׼�߶�;
	UTILITY_NAME::GsDelegate<void(double, double, double, double ,double)> OnCutFillEventFinish;
	virtual void CutFillByHeight(double dbHeight) = 0;
};
GS_SMARTER_PTR(GsCutFillAnalysis);

/// \brief ���շ�������
class GsSunshineAnalysis : public UTILITY_NAME::GsRefObject
{
public:
	// ��ȡ�����ۼƽ��
	virtual double GetSunshineAnalysisResult(int nStartHour, int nStartMinute, int nEndHour, int nEndMinute, int nFrequency, double dLength) = 0;
};
GS_SMARTER_PTR(GsSunshineAnalysis);

/// \brief �޸߷�������
class GsHeightLimitAnalysis : public UTILITY_NAME::GsRefObject
{
public:
	// ��ʾ��Χ��
	virtual void ShowAnalysisResult(double dHeight) = 0;
};
GS_SMARTER_PTR(GsHeightLimitAnalysis);

GLOBE_ENDNS