#pragma once
#include "utility.h"
#include "kernel.h"
#include "element.h"
  
GLOBE_NS
// �켣����
enum GsTrackerType
{
	eTrackerDefault = 0,// �Զ�������
	eTrackerMeasure=1,	// ����켣����
	eTrackerPlot=2,		// ���켣����
	//...
	eTrackerCustom = 5	//�Զ���켣����
};

/// \brief �켣Ҫ����
class GS_API GsTrackerElement : public Gs3DElement
{
protected:
	// �켣����
	int m_nTrackerType;

	// ��ʾ����
	KERNEL_NAME::GsSymbolPtr m_ptrSymbol;

	// ���ζ���
	KERNEL_NAME::GsGeometryPtr m_ptrGeometry;
public:
	GsTrackerElement(bool bSurface);
	virtual ~GsTrackerElement();

	virtual void Destory();

	/// \brief ���ƻ���
	virtual bool Draw(KERNEL_NAME::GsCanvas* pCanvas, KERNEL_NAME::GsDisplayTransformation *pDT) = 0;

	/// \brief ��ʾ����
	virtual void Symbol(GsSymbol* pSymbol, bool bClone = false) {}
	virtual GsSymbol* Symbol() { return m_ptrSymbol; }

	/// \brief ���ζ���
	virtual void Geometry(GsGeometry* pGeo) {}
	virtual GsGeometry* Geometry() { return m_ptrGeometry; }

	/// \brief �Ƿ��ǵر�Ҫ��
	virtual void Element3D(bool b3DElement) { m_b3DElement = b3DElement; }
	virtual bool Element3D() { return m_b3DElement; }

	/// \brief �켣����
	virtual void TrackerType(int nTrackerType) { m_nTrackerType = nTrackerType; }
	virtual int TrackerType() { return m_nTrackerType; }

};
GS_SMARTER_PTR(GsTrackerElement);

class GS_API GsTrackerElementMgr : public UTILITY_NAME::GsRefObject
{
	int m_nTrackerType;
protected:
	GsTrackerElementMgr(int nTrackerType);
	virtual ~GsTrackerElementMgr(){}
public:
	int TrackerType();

	/// \brief �����켣Ҫ��
	virtual void AddTrackerElement(GLOBE_NAME::GsTrackerElement* pEle, bool bRedraw = true) = 0;

	/// \brief ɾ���켣Ҫ��
	virtual bool DeleteTrackerElement(GLOBE_NAME::GsTrackerElement* pEle, bool bRedraw = true) = 0;

	/// \brief ɾ�����й켣Ҫ�ض���
	virtual void Clear() = 0;
};

/// \biref �켣���߻���
class GS_API GsTracker : public UTILITY_NAME::GsRefObject
{
	friend class GsTrackerRenderer;
	// ����״̬
	bool m_bActivate;
protected:
	// �켣����Ԫ��
	GsTrackerElementPtr m_ptrElement;
	// �켣ˢ��Ԫ��
	GsTrackerElementPtr m_ptrRefreshElement;
	// �Ƿ���ʾ������
	bool m_bShowResult;
	// ������Ȳ���
	int m_nTrackerType;
	// �Ƿ�����Ȳ���
	bool m_bDepthTest;
	GsTracker();
public:
	virtual ~GsTracker() {}
	/// \brief ���߼���
	virtual bool Activate(bool b);
	virtual bool Activate();

	/// \brief �Ƿ��ڹ���״̬
	virtual bool IsWorking() { return false; }

	/// \brief Ԫ�ر���ķ���
	virtual void ElementSymbol(KERNEL_NAME::GsSymbol *pSymbol);
	KERNEL_NAME::GsSymbol* ElementSymbol();

	/// \brief ˢ��Ԫ�صķ���
	void RefreshElementSymbol(KERNEL_NAME::GsSymbol *pSymbol);
	KERNEL_NAME::GsSymbol* RefreshElementSymbol();

	/// \brief �Ƿ���Ƶر�켣
	virtual void SurfaceElement(bool bIsSurface);
	virtual bool SurfaceElement();

	/// \brief ���ù켣����
	virtual void TrackerType(int nTrackerType);
	virtual int TrackerType();

	/// \brief ��Ȳ���
	virtual void DepthTest(bool b) { m_bDepthTest = b; }
	virtual bool DepthTest() { return m_bDepthTest; }

	/// \brief �Ƿ���ʾ������
	void ShowResult(bool bShow) { m_bShowResult = bShow; }

	/// \brief ȡ������
	virtual void Cancel() = 0;

	/// \brief ���ӵ��������Ļ���꣩
	virtual bool AddPoint(int x, int y, bool bComplete) = 0;
	/// \brief ���ӵ�������������꣩
	//virtual bool AddPoint(const KERNEL_NAME::GsRawPoint3D& pt, bool bComplete) = 0;

	/// \brief ����β�ڵ��������Ļ���꣩
	virtual bool UpdatePoint(int x, int y) = 0;
	/// \brief ����β�ڵ�������������꣩
	//virtual bool UpdatePoint(const KERNEL_NAME::GsRawPoint3D& pt) = 0;

	/// \brief ���ز�������¼�
	UTILITY_NAME::GsDelegate<void(double)> ShowResultEventHandler;

	/// \brief ��������¼�
	/// \param GsTrackerElement* ��ǰ���ƵĹ켣Ҫ�ض���
	/// \param GsTracker* ��ǰ���ƵĹ켣����
	/// \param int ���صĴ�����룬Ĭ��Ϊ0-�ɹ�����0-������루1ͼ�����ཻ...��
	UTILITY_NAME::GsDelegate<void(GsTrackerElement*, GsTracker*, unsigned int)> CompleteEventHandler;

protected:
	/// \brief ˢ�µ�ǰ�ռ�Ҫ��
	virtual void RefreshSpaceElement();

	/// \brief ���Ƶ�ǰ�ر�Ҫ��
	bool DrawSurfaceElement(KERNEL_NAME::GsCanvas* pCanvas, KERNEL_NAME::GsDisplayTransformation *pDT);	

	/// \brief �޸ĸ���״̬
	void UpdateState(bool bUpdate);
	bool UpdateState();

	// �Ƿ�����Ч�ļӵ����
	bool IsValidAddPointOperator(bool bComplete);
};
GS_SMARTER_PTR(GsTracker);

/// \breif �켣����������
class GS_API GsTrackerFactory
{
public:
	static GsTrackerFactory& Instance();

	/// \brief ��ȡ�켣Ҫ�ع������
	GsTrackerElementMgr* GetTrackerElementMgr(int nTrackerType = eTrackerDefault);

	/// \breif ������켣����
	GsTrackerPtr CreatePointTracker(int nTrackerType = eTrackerDefault);

	/// \breif �����߹켣����
	GsTrackerPtr CreateLengthTracker(int nTrackerType = eTrackerDefault);

	/// \breif ������켣����
	GsTrackerPtr CreateAreaTracker(int nTrackerType = eTrackerDefault);

	/// \breif �����߶ȹ켣����
	GsTrackerPtr CreateAltitudeTracker(int nTrackerType = eTrackerDefault);
private:
	UTILITY_NAME::GsVector<GsTrackerPtr> m_vtTrackerKit;

	// ��ǰ��Tracker
	GsTrackerPtr m_ptrCurTracker;
};

GLOBE_ENDNS