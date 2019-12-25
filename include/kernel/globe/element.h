#pragma once
#include "utility.h"
#include "kernel.h"
#include <texturesource.h>

class UWaterMesh;
class UBboard;
class UDecal;

GLOBE_NS

/// \brief ��ά����Ҫ�ػ���
class GS_API Gs3DElement : public UTILITY_NAME::GsRefObject
{
	bool m_bOwner;
	bool m_bValid;
protected:
	bool m_bVisible;
	bool m_b3DElement;
	
public:
	Gs3DElement(bool bOwner=true);
	virtual ~Gs3DElement();

	/// \brief ����Ҫ���Ƿ����������
	virtual void Owner(bool bOwner) final;
	virtual bool Owner() const { return m_bOwner; }

	/// \brief ��Ȳ��Կ���
	virtual void DepthTest(bool b) { }

	/// \brief ���ÿɼ���
	virtual void Visible(bool b){ m_bVisible = b; }
	/// \brief ��ȡ�ɼ���
	virtual bool Visible() const { return m_bVisible; }

	/// \brief �Ƿ���3D����Ҫ��
	virtual void Element3D(bool b3DElement) { }
	virtual bool Element3D() const { return m_b3DElement; }

	/// \brief �ͷ���ʾ�Ķ���
	virtual void Destory();
};
GS_SMARTER_PTR(Gs3DElement);

class GS_API GsGeoElement : public Gs3DElement
{
protected:
	
	void* m_pElement;

	GsGeoElement(bool bOwner=true);
public:
	virtual ~GsGeoElement();

	/// \brief ���ÿɼ���
	virtual void Visible(bool b);
	/// \brief ��ȡ�ɼ���
	virtual bool Visible();

	/// \brief �ͷ���ʾ�Ķ���
	virtual void Destory();

	/// \brief ���ζ���
	virtual bool Geometry(KERNEL_NAME::GsGeometry* pGeo);

	bool Valid();
protected:
	virtual bool IsGeometryValid(KERNEL_NAME::GsGeometry* pGeo) { return false; }

	// ����2D����Ҫ��
	virtual bool Create2DElement(KERNEL_NAME::GsGeometry* pGeo, KERNEL_NAME::GsSymbol* pSymbol);
};
GS_SMARTER_PTR(GsGeoElement);

/// \brief ��Ҫ��
class GS_API GsPointElement : public GsGeoElement
{
public:
	GsPointElement(KERNEL_NAME::GsGeometry* pGeo, KERNEL_NAME::GsPointSymbol *pSymbol);
	virtual ~GsPointElement();

	/// \brief ��Ȳ��Կ���
	virtual void DepthTest(bool b);

	/// \brief ���ÿɼ���
	virtual void Visible(bool b);
	/// \brief ��ȡ�ɼ���
	virtual bool Visible();

	/// \brief �ͷ���ʾ�Ķ���
	virtual void Destory();

	/// \brief ���ü��ζ���
	virtual bool Geometry(KERNEL_NAME::GsGeometry* pGeo);

	/// \brief ��ʾ����
	bool Symbol(KERNEL_NAME::GsPointSymbol *pSymbol);
protected:
	virtual bool IsGeometryValid(KERNEL_NAME::GsGeometry* pGeo);

	// ����ͼƬ
	UTILITY_NAME::GsImagePtr GenerateImage(KERNEL_NAME::GsPointSymbol *pPtSymbol);
};
GS_SMARTER_PTR(GsPointElement);

/// \brief ��Ҫ��
class GS_API GsLineElement : public GsGeoElement
{
public:
	GsLineElement(KERNEL_NAME::GsGeometry* pGeo, KERNEL_NAME::GsLineSymbol *pSymbol);
	virtual ~GsLineElement();

	/// \brief ��Ȳ��Կ���
	virtual void DepthTest(bool b);

	/// \brief ���ÿɼ���
	virtual void Visible(bool b);
	/// \brief ��ȡ�ɼ���
	virtual bool Visible();

	/// \brief �ͷ���ʾ�Ķ���
	virtual void Destory();

	/// \brief ���ü��ζ���
	virtual bool Geometry(KERNEL_NAME::GsGeometry* pGeo);

	/// \brief ��ʾ����
	bool Symbol(KERNEL_NAME::GsLineSymbol *pSymbol);
protected:
	virtual bool IsGeometryValid(KERNEL_NAME::GsGeometry* pGeo);
};
GS_SMARTER_PTR(GsLineElement);

/// \brief ��Ҫ��
class GS_API GsFillElement : public GsGeoElement
{
public:
	GsFillElement(KERNEL_NAME::GsGeometry* pGeo, KERNEL_NAME::GsFillSymbol *pSymbol);
	virtual ~GsFillElement();

	/// \brief ��Ȳ��Կ���
	virtual void DepthTest(bool b);

	/// \brief ���ÿɼ���
	virtual void Visible(bool b);
	/// \brief ��ȡ�ɼ���
	virtual bool Visible();

	/// \brief �ͷ���ʾ�Ķ���
	virtual void Destory();

	/// \brief ���ü��ζ���
	virtual bool Geometry(KERNEL_NAME::GsGeometry* pGeo);

	/// \brief ��ʾ����
	bool Symbol(KERNEL_NAME::GsFillSymbol *pSymbol);
protected:
	virtual bool IsGeometryValid(KERNEL_NAME::GsGeometry* pGeo);
};
GS_SMARTER_PTR(GsFillElement);


/// \brief ˮ��Ҫ��
/// \details ˮ����Ҫָ���Ĳ��ʣ�������Ϊ������Element����
class GS_API GsWaterElement : public GsGeoElement
{
	UWaterMesh* m_ptrWaterMesh;
public:
	/// \brief ���ݼ��δ���ˮ��
	/// \param pGeo Я���߳�ֵ�ļ�������
	GsWaterElement(KERNEL_NAME::GsGeometry* pGeo, bool bOwner = true);

	/// \brief ���ݼ��δ���ˮ��
	/// \param pGeo ��Я���߳�ֵ�Ķ�ά��������
	/// \param pElevation �߳�ֵ���򣬳��Ⱥ�pGeo�ĵ����һ��
	GsWaterElement(KERNEL_NAME::GsGeometry* pGeo, double *pElevation, bool bOwner = true);

	~GsWaterElement();

	/// \brief ��Ȳ��Կ���
	virtual void DepthTest(bool b);

	/// \brief �ͷ���ʾ�Ķ���
	virtual void Destory();

	/// \brief ���ÿɼ���
	virtual void Visible(bool b);

	/// \brief ��ȡ�ɼ���
	virtual bool Visible();

	/// \brief ���ζ���
	virtual bool Geometry(KERNEL_NAME::GsGeometry* pGeo);

	/// \brief ���ø߳�ƫ��ֵ
	void ElevationOffside(double dblOffside);
protected:
	virtual bool IsGeometryValid(KERNEL_NAME::GsGeometry* pGeo);
};
GS_SMARTER_PTR(GsWaterElement);

/// \brief �����Ҫ��
/// \details ��ע��ʾ����ƣ�֧����ʾ�������ֺ�����ͼƬ
class GS_API GsBillboardElement : public Gs3DElement
{
public:
	GsBillboardElement(bool bOwner = true);
	virtual ~GsBillboardElement();

	/// \breif ������Ȳ���
	virtual void DepthTest(bool bDepth);

	/// \brief �ͷ���ʾ�Ķ���
	virtual void Destory();

	/// \brief ���ÿɼ���
	virtual void Visible(bool b);
	/// \brief ��ȡ�ɼ���
	virtual bool Visible();

	/// \brief ��������
	void Position(const KERNEL_NAME::GsRawPoint3D& pt);
	/// \brief ��������
	KERNEL_NAME::GsRawPoint3D Position();

	/// \brief �������ַ���
	void TextSymbol(KERNEL_NAME::GsTextSymbol* pTextSymbol, KERNEL_NAME::GsFillSymbol* pBkSymbol=0);

	/// \brief ������ʾͼƬ
	void Image(UTILITY_NAME::GsImage* pImage);

	/// \brief ��С���Ӿ���
	void MinVisibleDistance(float fDis);
	/// \brief �����Ӿ���
	void MaxVisibleDistance(float fDis);

	/// \brief ����ͼ��ê��λ��(0��0 ��ʾ���м䣬���½�-1��-1�����Ͻ�1��1��Ĭ�����½�)
	void AnchorPosition(float x, float y);

	/// \brief ��ȡ��Ļ���ط�Χ
	UTILITY_NAME::GsRect ScreenRect();
protected:
	std::shared_ptr<UBboard> m_pUBboard;
};
GS_SMARTER_PTR(GsBillboardElement);

/// \brief ��������,�����޷�ʵ��������ʹ��������
/// \details ���ڽ�������������ط�
class GS_API GsDecalElement : public Gs3DElement
{
protected:
	GsDecalElement();
public:
	virtual ~GsDecalElement();

	/// \brief �ͷ���ʾ�Ķ���
	virtual void Destory();

	/// \brief ���ÿɼ���
	virtual void Visible(bool bVisible);
	/// \brief ��ȡ�ɼ���
	virtual bool Visible();

	/// \brief ����
	virtual void Update();

	/// \brief ��������
	virtual void Position(const KERNEL_NAME::GsRawPoint3D& position);
	/// \brief ��������
	virtual KERNEL_NAME::GsRawPoint3D Position();

	/// \brief ������ʾͼƬ
	void Image(UTILITY_NAME::GsImage* pImage);

	/// \brief ��������Դ
	/// \details ͨ���ò�������ʵ�ֺܶ�����Ч������gif����Ƶ���ŵȣ��ɰ�����չ
	void TextureSource(GsTextureSource* ptrTextureSource);
	/// \brief ��ȡ����Դ
	GsTextureSource* TextureSource();

	/// \brief ������С���Ӿ���
	virtual void MinVisibleDistance(float minDistance);
	/// \brief ��ȡ��С���Ӿ���
	virtual float MinVisibleDistance() const;

	/// \brief ���������Ӿ���
	virtual void MaxVisibleDistance(float maxDistance);
	/// \brief ��ȡ�����Ӿ���
	virtual float MaxVisibleDistance() const;

	/// \brief ���������ʧ����
	virtual void MaxFadeDistance(float maxFadeDistance);
	/// \brief ��ȡ�����ʧ����
	virtual float MaxFadeDistance() const;

	/// \brief ������С��ʧ����
	virtual void MinFadeDistance(float minFadeDistance);
	/// \brief ��ȡ��С��ʧ����
	virtual float MinFadeDistance() const;

	/// \brief ����ƫ����(Z����ʱ����ת)
	/// \details ��������������ƽ������ϵ
	void Yaw(float angle);
	/// \brief ��ȡƫ����
	float Yaw() const;

	/// \brief ���ø�����(X����ʱ����ת)
	/// \details ��������������ƽ������ϵ
	void Pitch(float angle);
	/// \brief ��ȡ������
	float Pitch() const;

protected:
	UDecal* m_ptrDecal;
	GsTextureSourcePtr m_ptrTextureSrc;
	unsigned long long m_preHash;
};
GS_SMARTER_PTR(GsDecalElement);

/// \brief ����ͶӰ����
/// \details ���ڽ�������������ط�,ԭ��Ϊһ��ָ���������ߵĳ����峯��ָ������ͶӰ(Ĭ��Ϊ����������һ�㳯�ŵ��ķ���)
/// \details ���Ϳ������ͶӰ�ĳߴ�(һ������º�������ͬ���ı���)���߾���ͶӰ�Ƿ���Ч��ֻ�иó�����ײ������ͶӰ���ཻʱ���ŻᱻͶӰ
class GS_API GsDecalOrthoElement : public GsDecalElement
{
public:

	/// \brief ���캯��
	/// \param position ͶӰ���ĵ�
	/// \param lenght �����峤
	/// \param width �������
	/// \param height �������
	GsDecalOrthoElement(const KERNEL_NAME::GsRawPoint3D& position, float lenght, float width, float height);
	virtual ~GsDecalOrthoElement();

	/// \brief ����ͶӰ��
	void Lenght(float lenght);
	/// \brief ��ȡͶӰ��
	float Lenght() const;

	/// \brief ����ͶӰ���
	void Width(float width);
	/// \brief ��ȡͶӰ���
	float Width() const;

	/// \brief ����ͶӰ���
	void Height(float height);
	/// \brief ��ȡͶӰ���
	float Height() const;
};

GS_SMARTER_PTR(GsDecalOrthoElement);

/// \brief ͸��ͶӰ����
/// \details ���ڽ�������������ط�,ԭ��Ϊһ��ָ��fov�ǡ�����ȡ�ͶӰ�ߵ���׶�峯��ָ������ͶӰ(Ĭ��Ϊ����������һ�㳯�ŵ��ķ���)
/// \details aspect������ͶӰ�ĳ����(һ������º�������ͬ���ı���)
/// \details fov�Ǿ�����ͶӰ�Ĵ�С���Ƕ�Խ��ͶӰԽ�󡣽�����0-90��֮��
/// \details �߾���ͶӰ�Ƿ���Ч��ֻ�иó�����ײ������ͶӰ���ཻʱ���ŻᱻͶӰ
class GS_API GsDecalProjectionElement : public GsDecalElement
{
public:

	/// \brief ���캯��
	/// \param position ͶӰ���ĵ�
	/// \param fov ��׶��fov��
	/// \param aspect ��׶�峤���
	/// \param height ͶӰ��
	GsDecalProjectionElement(const KERNEL_NAME::GsRawPoint3D& position, float fov, float aspect, float height);
	virtual ~GsDecalProjectionElement();

	/// \brief ���ó����
	void Aspect(float aspect);
	/// \brief ��ȡ�����
	float Aspect() const;
	/// \brief ����Fov��
	void Fov(float fov);
	/// \brief ��ȡFov��
	float Fov() const;
	/// \brief ����ͶӰ�߶�
	void Height(float height);
	/// \brief ��ȡͶӰ�߶�
	float Height() const;
};

GS_SMARTER_PTR(GsDecalOrthoElement);

GLOBE_ENDNS