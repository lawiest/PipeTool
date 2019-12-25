#pragma once
#include <geodatabase.h>
#include <poi.h>

KERNEL_NS
class GsProxyPOIDatabase;

class GS_API GsProxyPOIDataRoom : public GsRefObject
{
public:
	/// \brief  ������ݿ�
	virtual Utility::GsSmarterPtr<GsProxyPOIDatabase> ProxyPOIDatabase() = 0;

	/// \brief  ��ù�����ʸ��������
	virtual GsFeatureClassPtr FeatureClass() = 0;

	/// \brief  ��÷�������Ƭ����
	virtual GsTileClassPtr PublishTileClass() = 0;

	/// \brief  ���Ԫ������Ϣ
	virtual GsPlaceNameMetadata Metadata() = 0;

	/// \brief  ����Ԫ������Ϣ
	virtual void Metadata(const GsPlaceNameMetadata& data) = 0;

	/// \brief  ����
	virtual int Count() = 0;

	/// \brief  ����������ѯ
	virtual bool QueryClassify(int nIndex, GsPlaceNameClassify& data) = 0;

	/// \brief  ���ݷ���ֵ
	virtual bool QueryClassify(const char* value, GsPlaceNameClassify& data) = 0;

	/// \brief ���ӻ��滻����ֵ
	virtual bool SaveClassify(GsPlaceNameClassify& data) = 0;

	/// \brief ɾ������ֵ
	virtual bool DeleteClassify(const char* value) = 0;

	/// \brief ɾ�����ݼ�
	virtual bool Delete() = 0;
};
GS_SMARTER_PTR(GsProxyPOIDataRoom)

class GS_API GsProxyPOIDatabase : public GsRefObject
{
public:
	/// \brief ö��POI���ݼ�����
	virtual void DataRoomNames(UTILITY_NAME::GsVector<Utility::GsString>& vecName) = 0;

	/// \brief  ��POI����
	virtual GsProxyPOIDataRoomPtr Open(const char* name) = 0;

	/// \brief  �������ݼ�
	virtual GsProxyPOIDataRoomPtr Create(GsPlaceNameMetadata& metadata) = 0;

	/// \brief  ��ȡͼ���
	virtual GsIconLibrary* IconLibrary() = 0;

	/// \brief  ��ȡ���ſ�
	virtual GsPlaceNameSymbolLibrary* SymbolLibrary() = 0;

};
GS_SMARTER_PTR(GsProxyPOIDatabase);

/// \brief Oracle POI���ݿ�ʵ��
class GS_API GsOracleProxyPOIDatabase :public GsProxyPOIDatabase
{
private :
	Utility::GsSmarterPtr<GsProxyPOIDatabase> m_PtrProxyPOIDatabaseImpl;
public:
	GsOracleProxyPOIDatabase(GsGeoDatabase* oracleDatabase);
	virtual ~GsOracleProxyPOIDatabase();

	virtual void DataRoomNames(UTILITY_NAME::GsVector<Utility::GsString>& vecName);
	/// \brief  ��POI����
	virtual GsProxyPOIDataRoomPtr Open(const char* name);

	/// \brief  ��ȡͼ���
	virtual GsIconLibrary* IconLibrary();

	/// \brief  ��ȡ���ſ�
	virtual GsPlaceNameSymbolLibrary* SymbolLibrary();

	/// \brief  �������ݼ�
	virtual GsProxyPOIDataRoomPtr Create(GsPlaceNameMetadata& metadata);
};
KERNEL_ENDNS