#pragma once
#include "utility.h"
#include "tracker.h"

GLOBE_NS

enum GsPlotType
{
	ePlotNull,
	ePlotPoint,
	ePlotLine,
	ePlotSurface,
	ePlotModel,
};
enum GsPlotModeType
{
	eSphereModelType = 1,
	eCubeModelType = 2,
};
/// \brief ������
class GS_API GsPlotObject : public UTILITY_NAME::GsRefObject
{
protected:
	GsPlotType m_ePlotType;	// ����
	int m_nID; // Ψһidֵ

	UTILITY_NAME::GsString m_strName;		// ����

	GsRawPoint3D m_ptCamera;	// ���λ��
	GsRawPoint3D m_ptLookAt;	// �����λ��
	GsRawPoint3D m_dir, m_up;
	double m_dPitchAngle;		// ������
	double m_dHeadingAngle;		// ��λ��

	// �켣����
	GsTrackerElementPtr m_ptrTrackEle;
	// ������Ϣ
	UTILITY_NAME::GsString m_strDesc;

	// �����ַ���
	GsTextSymbolPtr m_ptrTextSymbol;
	// ����ͼ������
	UTILITY_NAME::GsConfig m_PointCfg;

	// ģ�ʹ�С
	int m_fModelSize;
	// ģ������
	GsPlotModeType m_eModelType;
public:
	GsPlotObject(GsPlotType eType);
	GsPlotObject(GsTrackerElement* pEle, GsPlotType eType);
	~GsPlotObject();

	/// \brief ���ù켣����
	void Element(GsTrackerElement* pTracker) { m_ptrTrackEle = pTracker; }
	/// \brief ��ȡ�켣����
	GsTrackerElement* Element() { return m_ptrTrackEle; }

	/// \biref �������
	GsPlotType PlotType() { return m_ePlotType; }

	/// \brief ���ΨһID
	void ID(int nid) { m_nID = nid; }
	int ID() { return m_nID; }

	/// \brief ����
	void Name(const char* strUTF8Name);
	UTILITY_NAME::GsString Name() { return m_strName; }

	/// \brief ���λ��
	void CameraPosition(const GsRawPoint3D& ptGeo) { m_ptCamera = ptGeo; }
	GsRawPoint3D CameraPosition() { return m_ptCamera; }

	/// \brief �����λ��
	void LookAtPosition(const GsRawPoint3D& pt) { m_ptLookAt = pt; }
	GsRawPoint3D LookAtPosition() { return m_ptLookAt; }

	void Direction(const GsRawPoint3D& dir) { m_dir = dir; }
	GsRawPoint3D Direction() { return m_dir; }

	void Up(const GsRawPoint3D& up) { m_up = up; }
	GsRawPoint3D Up() { return m_up; }

	/// \brief ������
	void Pitch(double dPitch) { m_dPitchAngle = dPitch; }
	double Pitch() { return m_dPitchAngle; }

	/// \brief ��λ��
	void Heading(double dHeading) { m_dHeadingAngle = dHeading; }
	double Heading() { return m_dHeadingAngle; }

	/// \brief ������Ϣ
	void Description(const char* str) { 
		if (str == 0) m_strDesc.empty();
		else m_strDesc = str; 
	}
	UTILITY_NAME::GsString Description() { return m_strDesc; }

	/// \brief ͨ��xml�ַ�������������
	static UTILITY_NAME::GsSmarterPtr<GsPlotObject> LoadFrom(const UTILITY_NAME::GsString& strXml);
	/// \brief ת����xml�ַ���
	UTILITY_NAME::GsString ToXml();

public:
	/// \brief �������ַ���
	void TextSymbol(GsTextSymbol* pSym);
	GsTextSymbol* TextSymbol() { return m_ptrTextSymbol; }
	/// \brief ��ȡ����ͼ��·��
	UTILITY_NAME::GsString PointImagePath();
	/// \brief ����ͼ������
	UTILITY_NAME::GsConfig& PointImageProperty() { return m_PointCfg; }

public:
	/// \brief ģ������
	void ModelType(GsPlotModeType eType) { m_eModelType = eType; }
	GsPlotModeType ModelType() { return m_eModelType; }

	/// \brief ģ�ʹ�С
	void ModelSize(float fVal) { m_fModelSize = fVal; }
	float ModelSize() { return m_fModelSize; }

protected:
	/// \brief ˢ�µ���
	void RefreshPointPlot();
};
GS_SMARTER_PTR(GsPlotObject);

class GS_API GsPlotRenderManager : public UTILITY_NAME::GsRefObject
{
public:
	GsPlotRenderManager();
	virtual ~GsPlotRenderManager();

	/// \brief �������
	void PlotType(GsPlotType eType);
	GsPlotType PlotType();

	/// \brief ��ȡ��ǰ���߶���
	GsTracker* CurrentTracker() {
		return m_pTracker;
	}

	/// \brief ��������
	virtual void ClearResult();
public:
	/// \brief ��������¼�
	UTILITY_NAME::GsDelegate<void(GsPlotObject*)> CompleteEventHandler;

	/// \breif ��ӱ�����
	void AddPlotObject(GsPlotObject *pPlot);

	/// \brief ɾ��������
	void DeletePlotObject(GsPlotObject *pPlot);
protected:
	/// \brief ���ݱ�����ͻ�ȡ�켣����
	GsTracker* GetTracker(GsPlotType eType);

	/// \brief ���������Ӧ����
	void OnComplete(GsTrackerElement *pEle, GsTracker *pTool, unsigned int nErrorCode);

	void OnClearPlotObject();
private:
	// �켣���� 
	GsTrackerPtr m_ptrModelTracker;
	// �켣����
	GsPlotType m_eType;
	// ��ǰ�켣����
	GsTracker* m_pTracker;

	// �����󻺴�
	UTILITY_NAME::GsStlMap<int, GsPlotObjectPtr> m_mapPlotObj;

	int m_nIndex;
	UTILITY_NAME::GsStlMap<GsPlotType, int> m_mapPlotCount;
};
GS_SMARTER_PTR(GsPlotRenderManager);

/// \brief ���湤��
class GsModelPlotTool : public UTILITY_NAME::GsRefObject
{
protected:
	GsModelPlotTool()
		:m_eModelType(eSphereModelType)
	{
		m_fModelSize = 10;
	}
public:
	/// \brief ���ģ������
	void ModelType(GsPlotModeType eType) { m_eModelType = eType; }
	GsPlotModeType ModelType() { return m_eModelType; }

	/// \brief ģ�ʹ�С
	void ModelSize(float fVal) { m_fModelSize = fVal; }
	float ModelSize() { return m_fModelSize; }

protected:
	int m_fModelSize;
	GsPlotModeType m_eModelType;
};
GS_SMARTER_PTR(GsModelPlotTool);
GLOBE_ENDNS
