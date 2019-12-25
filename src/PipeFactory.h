#pragma once
#include <utility.h>
#include <geodatabase.h>
#include "PipeLine.h"
#include "PipePoint.h"
#include "osg/Vec3d"
#include <osg/Node>
#include <QString>
#include <mutex>

GLOBE_NS

enum PipeType
{
	//����
	SQuare,
	//Բ��
	Circle,
	//���
	Mix
};

enum ErrorCode
{
	NoError,
	ZeroPipeSize,
	NoPipeLink
};

struct PipeProducePara
{
	std::vector<std::string> m_vecModel;
	std::map<std::string, std::string> m_lineFieldsMap;
	std::map<std::string, std::string> m_pointFieldsMap;
	std::map <std::string, std::string> m_mapColor;

	//����ʸ��·��
	std::string m_strLinePath;
	//�ܵ�ʸ��·��
	std::string m_strPointPath;

	//���ݼ�����
	std::string m_strDataSetName;
	//����������
	std::string m_strPipeTypeName;
	//����·��
	std::string m_strSavePath;

};

struct PipeSizePara
{
	PipeSizePara()
	{
		m_diameter = 0.0;
		m_width = 0.0;
		m_height = 0.0;
	}

	PipeType m_type;
	//ֱ��
	double m_diameter;
	//������ֱ��
	double thirdDiameter;

	//��
	double m_width;
	//��
	double m_height;
	//��������
	double m_thirdWidth;
	//��������
	double m_thirdHeight;
};

struct MyLineFeature
{
	osg::Vec3d m_spoint;
	osg::Vec3d m_epoint;

	double m_sheight;
	double m_eheight;

	double m_diameter;

	double m_width;
	double m_height;

	std::string m_id;
	std::string m_spointid;
	std::string m_epointid;

	PipeType m_type;
};

class PipeFactory :public GeoStar::Utility::GsRefObject
{
public:
	PipeFactory(PipeProducePara para);

	void BuildPipeLine();
	void BuildPipePoint();
	void CopyTexture();

	void getVector(osg::Vec3d pos, const std::vector<MyLineFeature>& vecLineFeatures, std::vector<osg::Vec3d>& vecDir, PipeSizePara& sizePara);
	PipeSizePara getThreeLinkVector(const std::vector<osg::Vec3d>& vecDir, const std::vector<MyLineFeature>& vecLineFeatures, std::vector<osg::Vec3d>& vecTempDir);
	PipeSizePara getFourLinkVector(const std::vector<osg::Vec3d>& vecDir, const std::vector<MyLineFeature>& vecLineFeatures, std::vector<osg::Vec3d>& vecTempDir);

	void DealWithPoint(osg::Vec3d pos, std::string strPointID);
	void DealWithStraightLink(const osg::Vec3d pos, const std::string strPointID, const std::vector<osg::Vec3d>& vecDir, const PipeSizePara& sizePara);
	void DealWith2Link(const osg::Vec3d pos, const std::string strPointID, const std::vector<osg::Vec3d>& vecDir, const PipeSizePara& sizePara);
	void DealWith3Link(const osg::Vec3d pos, const std::string strPointID, const std::vector<osg::Vec3d>& vecDir, const PipeSizePara& sizePara);
	void DealWith4Link(const osg::Vec3d pos, const std::string strPointID, const std::vector<osg::Vec3d>& vecDir, const PipeSizePara& sizePara);

	//�ҵ������������
	ErrorCode FindRelativeLine(std::string strPointID, std::vector<MyLineFeature>& vecFeatures);
	//���û�йܵ�̣߳���Ҫ��������ȥȡ
	double GetPointHeightInLine(std::string strPointID);

	void getLineFeature(std::string& strPipeSize, const GsFeaturePtr& ptrLineFea, MyLineFeature& feature);

	void DealWithAppendant(std::string strPointName, std::string strAppendantName, osg::Vec3d pos, double dbAngle);

	void SaveAndShowObj();
	void SaveMaterial(std::string strMaterialPath, osg::Vec3d color);
	void SaveMetaData();

	void traverseAllTexture(QString qstrFileName);

	osg::Vec3d getPipeColor();

	int EPSG();

	void safeCout(std::string strMessage);

	std::vector<PipeLinePtr>& GetPipeLines();
	std::vector<PipePointPtr>& GetPipePoints();

	std::string FindModelFile(std::string strModelName);

	virtual ~PipeFactory();

private:
	std::mutex m_mutex;

	std::vector<PipeLinePtr> m_vecPipeLine;
	std::vector<PipePointPtr> m_vecPipePoint;

	PipeProducePara m_ProducePara;

	KERNEL_NAME::GsFeatureClassPtr m_ptrLineFeatureClass;
	KERNEL_NAME::GsFeatureClassPtr m_ptrPointFeatureClass;

	//ƫ�Ƶ�
	osg::Vec3d m_originePoint;
	osg::Vec3d m_origineWgs84Point;
	bool m_bIsOriginSet;

	int m_nEPSG;

	//�渽����
	std::map<std::string, osg::ref_ptr<osg::Node> >m_mapAppendant;
	std::map<std::string, osg::ref_ptr<osg::Node> >m_mapAppendantUnique;

};

GS_SMARTER_PTR(PipeFactory);

GLOBE_ENDNS

