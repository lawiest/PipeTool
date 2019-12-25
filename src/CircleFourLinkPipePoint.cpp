#include "CircleFourLinkPipePoint.h"
#include <utility.h>
#include "CircleTwoLinkPipePoint.h"

GLOBE_NS

CircleFourLinkPipePoint::CircleFourLinkPipePoint(std::vector<osg::Vec3d> vecDir, osg::Vec3d postion, double diameter, double thirdDiameter, std::string strPointID, std::string strTypeName)
	:PipePoint(postion, strPointID, strTypeName)
{
	m_vecDir = vecDir;
	m_radius = diameter / 2000.0;
	m_thirdRadius = thirdDiameter / 2000.0;
}

bool CircleFourLinkPipePoint::build()
{	
	m_ptrVetexArry = new osg::Vec3dArray();
	m_ptrNormal = new osg::Vec3dArray();
	m_ptrIndex = new osg::DrawElementsUShort(osg::PrimitiveSet::TRIANGLES);

	//���Ƕȶ�������
	std::vector<osg::Vec3d> vecDir1;
	vecDir1.push_back(m_vecDir[0]);
	vecDir1.push_back(m_vecDir[1]);

	//�Ƚ�һ����ͨ������֮ǰ���ǳ��˸�2000�����ö�ͨ��ģҪ�����˻���
	CircleTwoLinkPipePointPtr ptrTwoLink1 = new CircleTwoLinkPipePoint(vecDir1, m_centerPostion, m_radius*2000.0, m_strPointID, m_strTypeName);
	ptrTwoLink1->setOriginPoint(m_originePoint);
	bool bIsOk = ptrTwoLink1->build();

	m_ptrVetexArry = ptrTwoLink1->getVetexArray();
	m_ptrNormal = ptrTwoLink1->getNormalArray();
	m_ptrIndex = ptrTwoLink1->getIndexArray();

	std::vector<osg::Vec3d> vecDir2;
	vecDir2.push_back(m_vecDir[2]);
	vecDir2.push_back(m_vecDir[3]);
	//�ٽ�һ����ͨ
	CircleTwoLinkPipePointPtr ptrTwoLink2 = new CircleTwoLinkPipePoint(vecDir2, m_centerPostion, m_thirdRadius*2000.0, m_strPointID,m_strTypeName);
	ptrTwoLink2->setOriginPoint(m_originePoint);
	bIsOk = ptrTwoLink2->build();

	osg::Vec3dArray* ptrVetexArray = ptrTwoLink2->getVetexArray();
	osg::Vec3dArray* ptrNormalArray = ptrTwoLink2->getNormalArray();
	osg::DrawElementsUShort* ptrIndexArray = ptrTwoLink2->getIndexArray();

	int nIndexCnt = m_ptrVetexArry->size();
	//�ϲ�����ͷ���
	for (int i = 0; i < ptrVetexArray->size(); i++)
	{
		m_ptrVetexArry->push_back((*ptrVetexArray)[i]);
		m_ptrNormal->push_back((*ptrNormalArray)[i]);
	}

	//�ϲ�����
	for (int i = 0; i < ptrIndexArray->size(); i++)
	{
		m_ptrIndex->push_back((*ptrIndexArray)[i] + nIndexCnt);
	}

	return bIsOk;
}

CircleFourLinkPipePoint::~CircleFourLinkPipePoint()
{

}

GLOBE_ENDNS