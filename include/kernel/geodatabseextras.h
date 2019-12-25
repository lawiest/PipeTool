#pragma once
#include <preconfig.h>
#include <object.h>

#include <geodatabase.h> 
#include <timer.h>

KERNEL_NS
/// \brief ʱ���ѯ��ʽ,ͨ����GsTemporalTileClass ���ò�ͬ�Ĳ�ѯ��ʽ�õ���ͬ��ʱ�����Ч��
enum GsTemporalQueryType
{
	eOnTime,//�鿴��ǰʱ��
	eFromTime,//׷�ݷ�ʽ�鿴��ǰʱ��
};
/// \brief ��ʱ�����ݿ��೧
class GS_API GsTemporalDatabaseFactory :public GsGeoDatabaseFactory
{
public:
	GsTemporalDatabaseFactory();
	~GsTemporalDatabaseFactory();
	/// \brief �������ݿ�������Ϣ��һ���ռ����ݿ�
	///\param connProperty ���ݿ�������Ϣ
	///\return ���ؿռ����ݿ����ʵ�����߿�
	virtual GsGeoDatabasePtr Open(const GsConnectProperty & connProperty) override;
};
GS_SMARTER_PTR(GsTemporalDatabaseFactory);
/// \brief ��ʱ����Ƭ���ݼ��ӿ���
class GS_API GsTemporalTileClass :public GsTileClass
{
protected:
	///\brief ��ѯʱ���
	Utility::GsDateTime m_QueryTimePoint;
	///\brief ��ѯ��ʽ,׷�����ǲ鿴��ǰʱ��
	GsTemporalQueryType m_QueryType;

protected:
	GsTemporalTileClass(GsGeoDatabase* pDB);
public:
	///\brief ��������
	~GsTemporalTileClass();

	///\brief ����ʱ��
	///\param const char * ʱ������
	///\param GsDateTime& StartDate, ��ʼʱ��
	///\param GsDateTime& EndDate ,����ʱ��
	///\return bool �Ƿ񴴽��ɹ�
	virtual bool CreateTemporal(const char *TemporalName, const Utility::GsDateTime& StartDate, const  Utility::GsDateTime& EndDate) = 0;
	///\brief ɾ��ʱ��
	///\param const char * ʱ������
	///\return bool �Ƿ�ɾ���ɹ�
	virtual bool DeleteTemporal(const char *TemporalName) = 0;
	///\brief ��ѯʱ��ʱ�䷶Χ
	///\param const char * ʱ������
	///\param GsDateTime& StartDate, ��ʼʱ��
	///\param GsDateTime& EndDate ,����ʱ��
	///\return bool �Ƿ��ѯ�ɹ�
	virtual bool QueryTemporalDate(const char *TemporalName, Utility::GsDateTime& StartDate, Utility::GsDateTime &EndDate) = 0;
	///\brief ע����Ƭ���ݼ���ָ��ʱ��
	///\param const char * TemporalName ʱ������
	///\param GsTileClass * TileClass ��Ƭ���ݼ�
	///\param GsGeometry* pGeo ע��ķ�Χ,�˷�Χ������׷�ݲ�ѯ
	///\return bool �Ƿ�ɹ�
	virtual bool RegisterTileClass(const char * TemporalName, GsTileClass * TileClass, GsGeometry* pGeo) = 0;
	///\brief ע����Ƭ���ݼ�
	///\param GsTileClass * TileClass ��Ƭ���ݼ�
	///\param const char * TemporalName ʱ������
	///\return bool �Ƿ�ɹ�
	virtual bool UnRegisterTileClass(GsTileClass * TileClass, const char * TemporalName) = 0;
	///\brief ע����Ƭ���ݼ�
	///\param GsTileClass * TileClass ��Ƭ���ݼ�����
	///\param const char * TemporalName ʱ������
	///\return bool �Ƿ�ɹ�
	virtual bool UnRegisterTileClass(const char * TileClassName, const char * TemporalName) = 0;
	///\brief ö��ʱ������
	///\return GsVector<GsString> 
	virtual Utility::GsVector<Utility::GsString> EnumTemporalName() = 0;
	///\brief ö��ʱ�������ݼ�����
	///\param const char * TemporalName ʱ������
	///\return GsVector<GsString> 
	virtual Utility::GsVector<Utility::GsString> EnumRegisterTileClassName(const char * TemporalName) = 0;
	/// \brief ���ò�ѯ����
	///\param enumQueryType ��ѯ����
	///\return void
	virtual void QueryType(GsTemporalQueryType eType);
	/// \brief ��ȡ��ѯ����
	///\return void
	virtual GsTemporalQueryType QueryType();
	/// \brief ���ò�ѯʱ��
	///\param enumQueryType ��ѯʱ��
	///\return void
	virtual void QueryTimePoint(const Utility::GsDateTime & time);
	/// \brief ��ѯʱ��
	///\return GsDateTime
	virtual Utility::GsDateTime QueryTimePoint();
	/// \brief ͨ����������һ���Ѿ�ע�����Ƭ���ݼ�
	///\param const char* strTlsName ��Ƭ���ݼ�����
	///\return GsTileClass * ��Ƭ���ݼ�
	virtual GsTileClassPtr FindTileClass(const char* strTlsName) = 0;

	/// \brief ��ȡ��Ƭ���ݼ��ķ�Χ����
	virtual GsIndexGeometryPtr GeometryIndex(GsTileClass * TileClass) = 0;
};
GS_SMARTER_PTR(GsTemporalTileClass);
KERNEL_ENDNS