#pragma once
#include "kernel.h"
#include "utility.h"
#include "utility3d.h"
#include "weburiparser.h"
#include "workthread.h"

class USmallScene;
class GsGtsDataSource;
GLOBE_NS

/// \brief ���ݼ�����
enum GsDatasetType
{
	/// \brief ���ǡ�����Ӱ�����ݼ�
	eDatasetImage,
	/// \brief �������ݼ�
	eDatasetTerrain,
	/// \brief ��ĻԪ�����ݼ�
	eDatasetElement,
	/// \brief ʸ�����ݼ�
	eDatasetVector,
	/// \brief ��̬ʸ�����ݼ�
	eDatasetDynamicVector,

	/// \brief �������ݼ�
	eDatasetPlacename,
	/// \brief ��бӰ�����ݼ�
	eDatasetOblique,
	/// \brief ��ϸģ�����ݼ�
	eDatasetUModel,
	/// \brief ��ϸС����ģ�����ݼ�
	eDatasetUWorld,
	eDatasetMax,
	
};

enum GsRequestResult
{
	eRRInit,
	eRRError,
	eRRBase,
	eRROutOfRange,
	eRRSendOut,
	eRRNotRender,
	eRROK
};
 


/// \brief ��Ƭ������٣����������ظ���ӻ�ִ��
class GS_API GsTileTaskTracker:public UTILITY_NAME::GsRefObject
{
	int m_nFaild;
	int m_nDarkPeriod;
	Utility::GsStopWatch m_Watch;
	Utility::GsSafeObject < Utility::GsStlMap < UTILITY_NAME::GsDataSetQuadKey, Utility::GsPair<long long,int>  > > m_BlackList;
	Utility::GsSafeObject<Utility::GsStlMap<UTILITY_NAME::GsDataSetQuadKey, bool > > m_TaskKey;
public:
	GsTileTaskTracker();

	/// \brief �ж�һ�������Ƿ��Ѿ����������
	bool IsBlack(const UTILITY_NAME::GsDataSetQuadKey& k);

	/// \brief ִ������ǰ����һ�������б�
	void Add(const UTILITY_NAME::GsDataSetQuadKey& k);

	/// \brief �ж������Ƿ����
	bool Exists(const UTILITY_NAME::GsDataSetQuadKey& k);
	
	/// \brief �ж�һ�������Ƿ�����ִ��
	bool IsWorking(const UTILITY_NAME::GsDataSetQuadKey& k);
	
	/// \brief �ж�һ�������Ƿ����ڵȴ�
	bool IsWaiting(const UTILITY_NAME::GsDataSetQuadKey& k);

	/// \brief �ж�һ�������Ƿ�����ִ��
	/// \details ������񲻴����򷵻�false
	bool Begin(const UTILITY_NAME::GsDataSetQuadKey& k);
	
	/// \brief ��ʶһ�������Ѿ����
	/// \param k �����Key
	/// \param bSucceed �����Ƿ�ִ�гɹ���,ִ��ʧ�ܵ���������������
	bool Finish(const UTILITY_NAME::GsDataSetQuadKey& k, bool bSucceed);
	
	/// \brief ɾ��һ������Key
	void RemoveForce(const UTILITY_NAME::GsDataSetQuadKey& k);
};
/// \brief GsTileTaskTrackerPtr
GS_SMARTER_PTR(GsTileTaskTracker);

/// \brief ���ڴ�����Դ��ȡ�����ݽ���Ԥ
class GS_API GsRequestDataPreprocess :public UTILITY_NAME::GsRefObject
{
public:
	virtual ~GsRequestDataPreprocess() {}
	virtual bool Preprocess(const UTILITY_NAME::GsDataSetQuadKey& key, const unsigned char* data, int nLen, UTILITY_NAME::GsByteBuffer* buff) = 0;
};
/// \brief GsRequestDataPreprocessPtr 
GS_SMARTER_PTR(GsRequestDataPreprocess);

/// \brief ���ϴ�������������������κ�һ���ɹ���ɹ�
class GS_API GsMultiDataPreprocess :public GsRequestDataPreprocess
{
	UTILITY_NAME::GsVector<GsRequestDataPreprocessPtr> m_vecSub;

public:
	GsMultiDataPreprocess();
	GsMultiDataPreprocess(GsRequestDataPreprocess* sub);
	
	/// \brief ���һ��
	void Add(GsRequestDataPreprocess* sub);
	/// \brief ����
	int Count();
	/// \brief ���
	void Clear();
	/// \brief �Ƴ��������Ƴ��Ķ���
	GsRequestDataPreprocessPtr Remove(int i);
	/// \brief ��ȡ����
	GsRequestDataPreprocessPtr Item(int i);

	/// \brief Ԥ����
	virtual bool Preprocess(const UTILITY_NAME::GsDataSetQuadKey& key, const unsigned char* data, int nLen, UTILITY_NAME::GsByteBuffer* buff);


};
/// \brief GsRequestDataPreprocessPtr 
GS_SMARTER_PTR(GsRequestDataPreprocess);



/// \brief ����Hash�㷨�����ݳ�����֤��Ч���ݵĵ�Ԥ�������
class GS_API GsHashCheckDataPreprocess :public GsRequestDataPreprocess
{
	UTILITY_NAME::GsVector<UTILITY_NAME::GsPair<unsigned long long, int> > m_HashData;
public:
	GsHashCheckDataPreprocess();
	GsHashCheckDataPreprocess(unsigned long long hash, int datasize);
	GsHashCheckDataPreprocess(UTILITY_NAME::GsPair<unsigned long long, int>* hashset,int nCount);
	
	/// \brief ������б�Ҫ����
	void Clear();
	
	/// \brief hash�Ƚ����ݵ�����
	int Count();
	
	/// \brief ɾ��һ���Ƚ����ݣ�����ɾ��������
	UTILITY_NAME::GsPair<unsigned long long, int> Remove(int i);

	/// \brief ��ȡһ���Ƚ�����
	UTILITY_NAME::GsPair<unsigned long long, int> Data(int i);

	/// \brief ���һ���Ƚ�����
	void Add(unsigned long long hash, int datasize);

	/// \brief ��Ӷ���Ƚ�����
	void Add(UTILITY_NAME::GsPair<unsigned long long, int>* hashset, int nCount);

	virtual bool Preprocess(const UTILITY_NAME::GsDataSetQuadKey& key, const unsigned char* data, int nLen, UTILITY_NAME::GsByteBuffer* buff);
};
/// \brief GsHashCheckDataPreprocessPtr 
GS_SMARTER_PTR(GsHashCheckDataPreprocess);

/// \brief ���ͼӰ�����ݴ�����
/// \details ʶ�����ͼ����Ч��Ƭ
class GS_API GsTianDituImageDataPreprocess :public GsHashCheckDataPreprocess
{ 
public:
	GsTianDituImageDataPreprocess();
};
/// \brief GsTianDituImageDataPreprocessPtr 
GS_SMARTER_PTR(GsTianDituImageDataPreprocess);


/// \brief ��Ƭ���ݼ�
class GS_API GsTileDataset : public UTILITY_NAME::GsRefObject
{
	/// \brief ���ݼ���HashKey 
	long long	m_DataSetKey;
	// �Ƿ�ɼ�
	bool m_bVisible;
	// �Ƿ����¼���hash��ʶ�������ݼ��仯��Ҫ����ˢ��ʱ����״̬��
	bool m_bRefresh;
	
protected:
	GsRequestDataPreprocessPtr m_ptrDataPreprocess;
	/// \brief ���ݼ�����
	Utility::GsString m_strName;
	/// \brief ���ݼ�����
	GsDatasetType m_eType;
	/// \brief ���ݼ�·��
	Utility::GsString m_strDSPath;

	GsTileDataset();

	/// \brief ���ݼ���ΨһKey����
	virtual Utility::GsString UniqueKey() = 0;

	/// \brief ��������
	virtual bool OnRequest(int nLevel, int nRow, int nCol) = 0;

	/// \brief �Ƿ�����Ч����Ƭ
	virtual bool IsValidTile(int nLevel, int nRow, int nCol) { return false; }

	/// \brief ��Ƭ�������
	Utility::GsTileCache* Cache();
	 
public:
	virtual ~GsTileDataset();

	/// \brief ����Ԥ�������
	GsRequestDataPreprocess* DataPreprocess();
	
	/// \brief ����Ԥ�������
	void DataPreprocess(GsRequestDataPreprocess* process);

	/// \brief ��ȡ���߼������ݼ���hashKey
	long long DataSetKey();

	/// \brief ��ȡ����
	Utility::GsString Name();
	void Name(const char* strName);

	/// \brief ��ȡ���ݼ�·��
	virtual Utility::GsString Path();

	/// \brief ���ݼ�����
	GsDatasetType DatasetType();
	void DatasetType(GsDatasetType eType);

	/// \brief ���ݼ��Ƿ�ɼ�
	virtual void Visible(bool bVislble);
	virtual bool Visible();

	/// \brief �����Ч��ʾ�ĸ߳�ֵ
	virtual double ValidElevation();

	/// \brief ��ȡ���ݷ�Χ
	virtual GsBox Extent() = 0;

	/// \brief ��ȡ���ݸ߶�
	virtual double Height();

	/// \brief ��ȡ������
	virtual GsPyramid* Pyramid() = 0;

	/// \brief ��ȡ�ռ�ο�
	virtual GsSpatialReference* SpatialReference() = 0;

	/// \brief ���ݲ�������������
	virtual GsRequestResult Request(int l, int r, int c, UTILITY_NAME::GsByteBuffer* buff);

	///\���ݼ������
	UTILITY_NAME::GsDelegate<void(bool state)> DataLoadResultEventHandler;
	virtual void OnDatasetLoadOK(bool state);
};
GS_SMARTER_PTR(GsTileDataset);

/// \brief ��Ƭ���������ݼ�
class GS_API GsTileClassDataset : public GsTileDataset
{
protected:
	/// \brief ��Ƭ������
	GsTileClassPtr m_ptrTileClass;

public:
	GsTileClassDataset(GsTileClass *pTileClass);
	virtual ~GsTileClassDataset();

	/// \brief ��ȡ��Ƭ������
	GsTileClass* TileClass();

	/// \brief ��ȡ���ݷ�Χ
	virtual GsBox Extent();

	/// \brief ��ȡ������
	virtual GsPyramid* Pyramid();

	/// \brief ��ȡ�ռ�ο�
	virtual GsSpatialReference* SpatialReference();

protected:
	/// \brief ���ݼ���ΨһKey����
	virtual Utility::GsString UniqueKey();

	/// \brief ��������
	virtual bool OnRequest(int nLevel, int nRow, int nCol);

	/// \brief �Ƿ�����Ч����Ƭ
	virtual bool IsValidTile(int nLevel, int nRow, int nCol);
};
GS_SMARTER_PTR(GsTileClassDataset);

/// ��Ƭ��ͼ�������ݼ�����
class GS_API GsTMSDataset :public GsTileClassDataset
{
protected:
	GsTMSTileClassPtr m_ptrTMSTileClass;
	GsTMSUriParserPtr m_ptrTMSUriParser;

	/// \brief ��Χ
	GsBox m_Extent;
	/// \brief ������
	GsPyramidPtr m_ptrPyramid;
	/// \brief �ռ�ο�
	GsSpatialReferencePtr m_ptrRef;
	/// \brief ��ʼ����
	int m_nTopLevel;
	/// \brief ��������
	int m_nBottomLevel;

	GsTMSDataset(GsTileClass* pTileClass);
public:
	GsTMSDataset(GsTMSUriParser* pUriParser);
	virtual ~GsTMSDataset();

	/// \brief �������ݷ�Χ
	void Extent(const GsBox& ext);
	/// \brief ��ȡ���ݷ�Χ
	virtual GsBox Extent();

	/// \brief ���ý�����
	void Pyramid(GsPyramid* pPyramid);
	/// \brief ��ȡ������
	virtual GsPyramid* Pyramid();

	/// \brief ���ÿռ�ο�
	void SpatialReference(GsSpatialReference* pRef);
	/// \brief ��ȡ�ռ�ο�
	virtual GsSpatialReference* SpatialReference();

	/// \brief ��Ƭ�㼶��Χ
	void LevelRange(int nTopLevel, int nBottomLevel);
	/// \brief ��Ƭ��ʼ�㼶
	int TopLevel();
	/// \brief ��Ƭ�����㼶
	int BottomLevel();

	// \brief ���Url������
	GsTMSUriParser *UrlParser();

protected:
	/// \brief ���ݼ���ΨһKey����
	virtual Utility::GsString UniqueKey();

	/// \brief ��������
	virtual bool OnRequest(int nLevel, int nRow, int nCol);

	/// \brief ��Ƭ�Ƿ���Ч
	virtual bool IsValidTile(int nLevel, int nRow, int nCol);
};
GS_SMARTER_PTR(GsTMSDataset);

/// WMTS���ݼ�����
class GS_API GsWMTSDataset : public GsTMSDataset
{
public:
	GsWMTSDataset(GsWMTSUriParser *pUriParser);
	virtual ~GsWMTSDataset();

	/// \brief ������ʽ
	void Style(const char* strStyle);

	/// \brief ������Ƭ����
	void TileMatrixSet(const char* strTileMatrixSet);

	/// \brief ����ͼƬ��ʽ
	void ImageFormat(const char* strImageFormat);

protected:
	/// \biref ����Url��
	bool UpdateUrlTemplate(const UTILITY_NAME::GsString& strAttrName, const UTILITY_NAME::GsString& strAttrValue);
};
GS_SMARTER_PTR(GsWMTSDataset);

/// WMS���ݼ�����
class GS_API GsWMSDataset : public GsTMSDataset
{
public:
	GsWMSDataset(GsWMSUriParser *pUriParser);
	virtual ~GsWMSDataset();

	/// \brief ����ͼƬ��ʽ
	void ImageFormat(const char* strImageFormat);

	/// \brief ����ͼƬ�Ƿ�͸��
	void ImageTransparent(bool bTransparent);

	/// \brief �����������ݵ�ͼ����
	void ImageLayer(const char* strLayerNames);

	/// \brief �����������ݵİ汾��
	void Version(const char* strLayerNames);

protected:
	/// \biref ����Url��
	bool UpdateUrlTemplate(const UTILITY_NAME::GsString& strAttrName, const UTILITY_NAME::GsString& strAttrValue);
};
GS_SMARTER_PTR(GsWMSDataset);

/// \brief GeoTile�������ݼ�����
class GS_API GsGeoTileDataset : public GsTMSDataset
{
protected:
	GsGeoTileDataset(GsTileClass *pTileClass);
public:
	GsGeoTileDataset(GsGeoTileUriParser* pParser);
	virtual ~GsGeoTileDataset();
};
GS_SMARTER_PTR(GsGeoTileDataset);

/// \brief ģ�����ݾ����װ
struct GS_API GsModelDataHandle
{
	/// \brief ����
	int Type;
	/// \brief �����ݾ��
	union
	{
		long long MainIdentity;
		void*     MainHandle;
	};
	/// \brief �����ݾ��
	union
	{
		long long AssistIdentity;
		void*     AssistHandle;
	};
	GsModelDataHandle()
	{
		Type = 0;
		AssistIdentity = 0;
		MainIdentity = 0;
	}
	GsModelDataHandle(const GsModelDataHandle& o)
	{
		Type = o.Type;
		AssistIdentity = o.AssistIdentity;
		MainIdentity = o.MainIdentity;
	}
	GsModelDataHandle(int type,void* mainHandle,void* assistHandle = NULL)
	{
		Type = type;
		MainHandle = mainHandle;
		AssistHandle = assistHandle;
	}
	GsModelDataHandle(int type, long long mainIdentity, long long assistIdentity = NULL)
	{
		Type = type;
		MainIdentity = mainIdentity;
		AssistIdentity = assistIdentity;
	}
	/// \brief �Ƿ���Ч
	operator bool()
	{
		return Type != 0 || AssistIdentity != 0 || MainIdentity != 0;
	}
	template<class T>
	T CastType()
	{
		return (T)Type;
	}

	template<class T>
	T* CastMainPointer()
	{
		return (T*)MainIdentity;
	}

	template<class T>
	T& CastMainHandle()
	{
		return *((T*)MainIdentity);
	}

	template<class T>
	T* CastAssistPointer()
	{
		return (T*)AssistIdentity;
	}

	template<class T>
	T& CastAssistHandle()
	{
		return *((T*)AssistIdentity);
	}
};
/// \brief ģ�����ݽڵ�
class GS_API GsModelDataNode:public UTILITY_NAME::GsRefObject
{
protected:
	UTILITY_NAME::GsString  m_strName, m_strPath;
	unsigned long long				m_Hash;
	GsTileDatasetPtr				m_ptrDS;
	GsModelDataNode();
	
public:
	virtual ~GsModelDataNode();
	
	/// \brief ���ݽڵ����������ݼ�����
	virtual GsTileDataset* Dataset();

	/// \brief �ڵ��ϣֵ
	unsigned long long Hash();

	/// \brief �ڵ�����
	virtual const char* Name();
	/// \brief �ڵ�·��
	virtual const char* Path();

	/// \brief �ڵ�ID
	virtual const int Id();

	/// \brief ��ȡ���ݾ��
	/// \details ���ݾ���ľ����������;��������ݼ����ͣ��ڲ������������׵���
	/// \details ���ô˷����ᵼ��ʵ����ʵ������
	virtual GsModelDataHandle DataHandle();

	/// \brief ����Χ
	virtual KERNEL_NAME::GsBox Extent() = 0;

	/// \brief ��λ������ĵ�
	virtual KERNEL_NAME::GsRawPoint3D Location() = 0;

	/// \brief �ӽڵ�����
	virtual int ChildrenCount();

	/// \brief �����Ӷ��󲢷���
	/// \details ������Ӧ������������󣬶�ε��ô˷����ᵼ�¶�δ����Ӷ��� 
	virtual UTILITY_NAME::GsSmarterPtr<GsModelDataNode> Child(int i);

	/// \brief ���ø߳�ƫ��ֵ
	virtual void ElevationOffside(double dblOffside);

	/// \brief ����ģ��ƽ��
	virtual void Translate(double dblX, double dblY, double dblZ);

	/// \brief ����ģ������
	virtual void Scale(float x, float y, float z);

	/// \brief ����ģ����ת
	virtual void Rotate(double axisX, double axisY, double axisZ, double angle);

	/// \brief ���ÿɼ�
	virtual void Visible(bool bVisible);

	/// \brief �Ƿ�ɼ�
	virtual bool Visible();
};
GS_SMARTER_PTR(GsModelDataNode);


/// \brief ö��ģ�����ݽڵ�
class GS_API GsEnumModelDataNode :public UTILITY_NAME::GsRefObject
{
public:
	virtual ~GsEnumModelDataNode();
	/// \brief ��ȡ��һ�����ݽڵ�
	virtual GsModelDataNodePtr Next() = 0;
	/// \brief ����ö�ٹ���
	virtual void Reset() = 0;
};
/// \brief GsEnumModelDataNodePtr
GS_SMARTER_PTR(GsEnumModelDataNode);

/// \brief ģ�;ݼ�����
class GS_API GsModelDataset : public GsTileDataset
{
protected:
	GsModelDataset(const char *strModelFilePath);
	GsModelDataset();
public:
	virtual ~GsModelDataset();

	/// \brief ö�����ݽڵ�
	virtual GsEnumModelDataNodePtr EnumDataNode();

	/// \brief �������ݽڵ������
	virtual int RootDataNodeCount();

	/// \brief �����Ӷ��󲢷���
	/// \details ������Ӧ������������󣬶�ε��ô˷����ᵼ�¶�δ����Ӷ��� 
	virtual GsModelDataNodePtr RootDataNode(int i);


};
GS_SMARTER_PTR(GsModelDataset);

/// \brief ����ģ�����ݼ� 
class GS_API GsMultiModelDataset:public GsModelDataset
{
protected:
	GsMultiModelDataset();
public:
	virtual ~GsMultiModelDataset();
	/// \brief �����ݼ�����
	virtual int Count() = 0;
	/// \brief ��ȡһ�������ݼ�
	virtual GsModelDatasetPtr SubDataset(int i) = 0;

	/// \brief չ���������ݼ�
	virtual UTILITY_NAME::GsVector<GsModelDatasetPtr> ExpandSubDataset(int i) = 0;

};
GS_SMARTER_PTR(GsMultiModelDataset);

/// \brief ģ�����ݼ��೧
class GS_API GsModelDatasetFactory
{
	UTILITY_NAME::GsConfig m_Config;
public:
	GsModelDatasetFactory(const UTILITY_NAME::GsConfig& config);
	GsModelDatasetFactory();
	~GsModelDatasetFactory();

	/// \brief ��·������ģ�����ݼ�
	GsModelDatasetPtr Create(const char* path);
};


/// \brief ģ�;ݼ�����
class GS_API GsUModelDataset : public GsModelDataset
{
public:
	GsUModelDataset(const char *strModelFilePath);
	virtual ~GsUModelDataset();

	/// \brief ���ݲ�������������
	virtual GsRequestResult Request(int l, int r, int c, UTILITY_NAME::GsByteBuffer* buff);

	GsBox Extent();
	double Height();
	GsPyramid* Pyramid();
	GsSpatialReference* SpatialReference();

	GsGtsDataSource* DataSourcePtr();

	/// \brief �����Ч��ʾ�ĸ߳�ֵ
	virtual double ValidElevation();

	/// \brief ���ÿɼ�
	virtual void Visible(bool bVisible);
protected:
	virtual bool IsValidTile(int nLevel, int nRow, int nCol);

	bool OnRequest(int nLevel, int nRow, int nCol);
	Utility::GsString UniqueKey();

	GsPyramidPtr m_ptrGsPyramid;
	UTILITY_NAME::GsSmarterPtr<GsGtsDataSource> m_ptrDatasource;
};
GS_SMARTER_PTR(GsUModelDataset);

/// \brief Unigine World�������ݼ�
class GS_API GsUWorldDataset : public GsModelDataset
{
public:
	GsUWorldDataset(const char *strModelFilePath, const KERNEL_NAME::GsRawPoint3D* ptGeoPos = 0);

	virtual ~GsUWorldDataset();

	virtual GsBox Extent();

	/// \brief �����Ч��ʾ�ĸ߳�ֵ
	virtual double ValidElevation();

	/// \brief �����Ƿ�ɼ�
	virtual void Visible(bool bVislble);

	void Position(const KERNEL_NAME::GsRawPoint3D& ptGeoPos);

	/// \brief �������ֲ���ģ�ͽڵ�
	GsModelDataNodePtr SearchModelDataNode(UTILITY_NAME::GsString strName);

	/// \brief ����id����ģ�ͽڵ�
	GsModelDataNodePtr SearchModelDataNode(int nModelID);

	///\brief ����Ĭ��world����ԭ��
	void SetDefaultOriginPoint();

	UTILITY_NAME::GsSharedPtr<USmallScene> getWorldScenePtr();

protected:
	virtual Utility::GsString UniqueKey() { return m_strName; }

	virtual bool OnRequest(int nLevel, int nRow, int nCol) { return false; }

	virtual GsPyramid* Pyramid() { return 0; }

	virtual GsSpatialReference* SpatialReference() { return 0; }

protected:
	UTILITY_NAME::GsSharedPtr<USmallScene> m_ptrWorldScene;

	//world����ԭ��
	KERNEL_NAME::GsRawPoint3D m_OriginPoint;

	//�����ļ��е�Ĭ��world����ԭ�㣨���û�û�и�����λ��Ϣʱʹ�ã�
	KERNEL_NAME::GsRawPoint3D m_DefaultOriginPoint;
};
GS_SMARTER_PTR(GsUWorldDataset);

/// \brief OSGB��ʽģ�;ݼ�����
class GS_API GsOsgbModelDataset : public GsModelDataset
{
public:
	GsOsgbModelDataset(const char *strModelFilePath);
	virtual ~GsOsgbModelDataset();

public:
	virtual void Visible(bool bVisible);

	/// \brief �����Ч��ʾ�ĸ߳�ֵ
	virtual double ValidElevation();

	virtual bool IsValidTile(int nLevel, int nRow, int nCol);
	virtual GsRequestResult Request(int l, int r, int c, UTILITY_NAME::GsByteBuffer* buff);

	GsBox Extent();
	GsPyramid* Pyramid();
	GsSpatialReference* SpatialReference();

	/// \brief ��������
	virtual bool OnRequest(int nLevel, int nRow, int nCol);
	void *DataSetPtr();
protected: 
	Utility::GsString UniqueKey();
	 
	void *m_pModelTree;
	KERNEL_NAME::GsPyramidPtr m_ptrGsPyramid;   
};
GS_SMARTER_PTR(GsOsgbModelDataset);

/// \brief ʸ�����ݼ�����
class GS_API GsVectorDataset : public GsTileDataset
{
	KERNEL_NAME::GsFeatureClassPtr m_ptrFcs;
public:
	GsVectorDataset(KERNEL_NAME::GsFeatureClass *pFeatureClass);
	virtual ~GsVectorDataset();

public:
	GsBox Extent();
	GsPyramid* Pyramid();
	GsSpatialReference* SpatialReference();
	KERNEL_NAME::GsFeatureClass *FeatureClass();
	virtual bool IsValidTile(int nLevel, int nRow, int nCol);
	virtual void Visible(bool bVislble);
protected:
	bool OnRequest(int nLevel, int nRow, int nCol);
	Utility::GsString UniqueKey();
	GsPyramidPtr m_ptrGsPyramid;

	bool IsDataValid();
};
GS_SMARTER_PTR(GsVectorDataset);

/// \brief �������ݼ�����
class GS_API GsPlaceNameDataset : public GsGeoTileDataset
{
	UTILITY_NAME::GsGrowByteBuffer m_IconBuffer;
	KERNEL_NAME::GsTilePtr m_ptrPOITile;
public:
	GsPlaceNameDataset(GsTileClass *pTileClass);
	GsPlaceNameDataset(GsWTFSUriParser *pUriParser);
	virtual ~GsPlaceNameDataset();

	/// \brief ��ȡ���ݷ�Χ
	virtual GsBox Extent();

	/// \brief ��ȡ������
	virtual GsPyramid* Pyramid();

	/// \brief ��ȡ�ռ�ο�
	virtual GsSpatialReference* SpatialReference();

	/// \brief ���ÿɼ���
	virtual void Visible(bool bVislble);

public:
	virtual GsRequestResult Request(int l, int r, int c, UTILITY_NAME::GsByteBuffer* buff);

	/// \brief �������ͼ��
	UTILITY_NAME::GsImagePtr RequestIcon(int nId);
protected:
	/// \brief ��Ƭ�Ƿ���Ч
	virtual bool IsValidTile(int nLevel, int nRow, int nCol);
};
GS_SMARTER_PTR(GsPlaceNameDataset);


/// \brief ��άͼ��
class GS_API Gs3DLayer : public Utility::GsRefObject
{
protected:
	Utility::GsString m_strName;
	Utility::GsString m_strAliasName;
	GsTileDatasetPtr m_ptrDataset;
	bool m_bVisible;
	int m_nPriority;
	double m_dMinAltitude;
	double m_dMaxAltitude; 

	Gs3DLayer();
public:
	virtual ~Gs3DLayer() {}
	/// \brief ����ͼ������
	void Name(const char* strName);
	/// \brief ��ȡͼ������
	const char* Name();

	/// \brief ����ͼ�����
	void AliasName(const char* strAliasName);
	/// \brief ��ȡͼ�����
	const char* AliasName();

	/// \brief �������ݼ�
	void Dataset(GsTileDataset* pDataset);
	/// \brief ���ݼ�
	GsTileDataset* Dataset();

	/// \brief �����Ƿ�ɼ�
	void Visible(bool bVisible);
	/// \brief ��ȡ�Ƿ�ɼ�
	bool Visible();

	/// \brief �������ȼ�
	void Priority(int nPri);
	/// \brief ��ȡ���ȼ�
	int Priority();

	/// \brief ���ÿ��ӵĸ߶ȷ�Χ
	void ViewAltitude(double dMinAltitude, double dMaxAltitude);
	/// \brief ��ȡ��С���Ӹ߶�
	double MinViewAltitude();
	/// \brief ��ȡ�����Ӹ߶�
	double MaxViewAltitude();
	
};
GS_SMARTER_PTR(Gs3DLayer);

class GS_API Gs3DVectorLayer : public Gs3DLayer
{
	KERNEL_NAME::GsFeatureRendererPtr m_ptrRenderer;
public:
	Gs3DVectorLayer();
	virtual ~Gs3DVectorLayer() {}

	void Renderer(KERNEL_NAME::GsFeatureRenderer* pRenderer);
	KERNEL_NAME::GsFeatureRenderer* Renderer();
};
GS_SMARTER_PTR(Gs3DVectorLayer);

class GS_API Gs3DImageLayer : public Gs3DLayer
{
public:
	Gs3DImageLayer();
	virtual ~Gs3DImageLayer();
};
GS_SMARTER_PTR(Gs3DImageLayer);

class GS_API Gs3DTerrainLayer : public Gs3DLayer
{
public:
	Gs3DTerrainLayer();
	virtual ~Gs3DTerrainLayer();
};
GS_SMARTER_PTR(Gs3DTerrainLayer);

class GS_API Gs3DElementLayer : public Gs3DLayer
{
public:
	Gs3DElementLayer() {}
	virtual ~Gs3DElementLayer() {}
};
GS_SMARTER_PTR(Gs3DElementLayer);

class GS_API Gs3DPOILayer : public Gs3DLayer
{
public:
	Gs3DPOILayer() {}
	virtual ~Gs3DPOILayer() {}
};
GS_SMARTER_PTR(Gs3DPOILayer);

/// \brief ���η�����
class GS_API GsTerrainAccessor : public UTILITY_NAME::GsRefObject, UTILITY_NAME::GsRWLock
{
	friend class GsLayerContainer;

	// Ĭ�ϵ���
	Gs3DTerrainLayerPtr m_ptrDefaultTerrain;
	// �������ݱ�
	UTILITY_NAME::GsVector<Gs3DTerrainLayerPtr> m_vecTerrain;
	UTILITY_NAME::GsAtomic<long long> m_VerticalExaggeration;
	UTILITY_NAME::GsAtomic<long long> m_InvalidElevation;

	// ���ݱ仯
	void FireOnDatasetChanged();
public:
	GsTerrainAccessor();
	~GsTerrainAccessor();

	/// \brief Ĭ�ϵ���
	Gs3DTerrainLayer* DefaultTerrain();

	/// \brief �������ݼ�������
	int TerrainCount();

	/// \brief ����������ȡһ���������ݼ�
	Gs3DTerrainLayer* Terrain(int nIndex);

public:
	/// \brief ���ο��š�
	double VerticalExaggeration();
	/// \brief ���ο��š�
	void VerticalExaggeration(double value);

	/// \brief ��Ч�̡߳�
	double InvalidElevation();
	/// \brief ��Ч�̡߳�
	void InvalidElevation(double value);


	/// \brief ��ѯ��������ĸ̡߳�
	double QueryElevation(double x, double y);


	/// \brief �����Ƿ���ʾ����
	void TerrainVisible(bool bVisible);

	/// \brief ��ѯһ����ά����ĸ߲�
	/// \param p3DCoord �������飬��X��Y��Z��ʽ�洢
	int QueryElevation(double* p3DCoord, int nPointCount);


	/// \brief ��ͼ��������˳�����仯��ʱ����
	UTILITY_NAME::GsDelegate<void()> OnDatasetChanged;

private:
	/// \brief ����һ������ͼ��
	void AddTerrain(Gs3DTerrainLayer* terrain);

	/// \brief ���������Ƴ�һ������ͼ��
	Gs3DTerrainLayerPtr RemoveTerrain(int nIndex);

	/// \brief �Ƴ�һ������ͼ��
	Gs3DTerrainLayerPtr RemoveTerrain(Gs3DTerrainLayer* terrain);

	/// \brief ������еĵ���ͼ��
	void ClearTerrain();

	/// \brief ����һ������ͼ�㵽ָ��λ�á�
	void InsertTerrain(int nIndex, Gs3DTerrainLayer* terrain);

	/// \brief ��������ͼ���˳��
	/// \param nNewIndex �ö�2  �õ�-2   ����1  ����-1 ;������ƶ���˵��ͼ����vec�е��ƶ�
	void MoveTerrain(Gs3DTerrainLayer* terrain, int nNewIndex);
};
/// \brief TerrainAccessorPtr
GS_SMARTER_PTR(GsTerrainAccessor);


class GS_API GsPOIGeoDatabaseFactory : public KERNEL_NAME::GsGeoDatabaseFactory
{
public:
	/// \brief �������ݿ�������Ϣ��һ���ռ����ݿ�
	/// \param connProperty ���ݿ�������Ϣ
	/// \return ���ؿռ����ݿ����ʵ�����߿�
	virtual GsGeoDatabasePtr Open(const GsConnectProperty& connProperty);
};

class GS_API GsLayerContainer :public UTILITY_NAME::GsRefObject
{
	UTILITY_NAME::GsVector<UTILITY_NAME::GsSmarterPtr<Gs3DLayer>> m_vecLayers;
	GsTerrainAccessor* m_pTerrainAccessor;
public:
	GsLayerContainer(GsTerrainAccessor* pTerrain);
	~GsLayerContainer();

	/// \brief ���ͼ��
	void AddLayer(Gs3DLayer* pLayer);

	/// \brief ɾ��ͼ��
	void RemoveLayer(Gs3DLayer* pLayer);

	/// \brief ɾ��ͼ��
	void RemoveLayer(int nIndex);

	/// \brief ���ͼ��
	void ClearLayer();

	/// \brief ����ͼ��˳��
	/// \param nNewIndex �ö�2  �õ� - 2   ����1  ���� - 1; ������ƶ���˵��ͼ����vec�е��ƶ�
	void MoveLayer(Gs3DLayer* pLayer, int nIndex);

	/// \brief ͼ������
	int LayerCount();

	/// \brief ��ȡָ��λ�õ�ͼ��
	Gs3DLayer *Layer(int nIndex);

	/// \brief ��ȡָ�����ֵ�ͼ��
	Gs3DLayer *Layer(const char* strName);

	/// \brief ��ȡͼ�㴦����
	//GsTerrainAccessor* TerrainAccessor();

private:
	void OnLayerChanged();

};
GS_SMARTER_PTR(GsLayerContainer);

GLOBE_ENDNS