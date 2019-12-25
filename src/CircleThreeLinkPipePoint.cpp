#include "CircleThreeLinkPipePoint.h"
#include <utility.h>
#include "CircleTwoLinkPipePoint.h"
#include "CircleStraightLinkPipePoint.h"

GLOBE_NS

CircleThreeLinkPipePoint::CircleThreeLinkPipePoint(std::vector<osg::Vec3d> vecDir, osg::Vec3d postion, double diameter, double thirdDiameter, std::string strPointID, std::string strTypeName)
										:PipePoint(postion, strPointID, strTypeName)
{
	m_vecDir = vecDir;
	m_radius = diameter / 2000.0;
	m_thirdRadius = thirdDiameter / 2000.0;
	m_nPointCnt = 36;

	//�Ӵ�
	m_dbBold = 1.3;
	//��ͷ�ӳ�
	m_dbExtend = 1.8;
	//��Ȧ�Ӵ�
	m_dbOuterBold = 1.06;

	//����ܾ��Ƚϴ����Ӧ��һЩ��ϸһЩ
	if (m_radius > 0.8)
	{
		m_dbBold = 1.2;
		m_dbExtend = 1.6;
	}
	else if (m_radius < 0.1)
	{
		//������Ӻ�ϸ��������΢����һЩ
		m_dbExtend = 1.8;
	}
}

bool CircleThreeLinkPipePoint::build()
{	
	m_ptrVetexArry = new osg::Vec3dArray();
	m_ptrNormal = new osg::Vec3dArray();
	m_ptrIndex = new osg::DrawElementsUShort(osg::PrimitiveSet::TRIANGLES);

	//���Ƕȶ�������
	std::vector<osg::Vec3d> vecDir;
	vecDir.push_back(m_vecDir[0]);
	vecDir.push_back(m_vecDir[1]);

	//�Ƚ�һ����ͨ������֮ǰ���ǳ��˸�2000�����ö�ͨ��ģҪ�����˻���
	CircleTwoLinkPipePointPtr ptrTwoLink = new CircleTwoLinkPipePoint(vecDir, m_centerPostion, m_radius*2000.0, m_strPointID, m_strTypeName);
	ptrTwoLink->setOriginPoint(m_originePoint);
	bool bIsOk = ptrTwoLink->build();

	m_ptrVetexArry = ptrTwoLink->getVetexArray();
	m_ptrNormal = ptrTwoLink->getNormalArray();
	m_ptrIndex = ptrTwoLink->getIndexArray();

	//�ٽ�һ��ֱͨ
	CircleStraightLinkPipePointPtr ptrStraight = new CircleStraightLinkPipePoint(m_vecDir[2], m_centerPostion, m_radius*2000.0,m_strPointID,m_strTypeName);
	ptrStraight->setOriginPoint(m_originePoint);
	bIsOk = ptrStraight->build();

	osg::Vec3dArray* ptrVetexArray = ptrStraight->getVetexArray();
	osg::Vec3dArray* ptrNormalArray = ptrStraight->getNormalArray();
	osg::DrawElementsUShort* ptrIndexArray = ptrStraight->getIndexArray();

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

	return true;
}

CircleThreeLinkPipePoint::~CircleThreeLinkPipePoint()
{

}

GLOBE_ENDNS