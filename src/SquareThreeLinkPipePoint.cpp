#include "SquareThreeLinkPipePoint.h"
#include "PipeUntility.h"
#include <utility.h>
#include "Cuboid.h"
#include "SquareTwoLinkPipePoint.h"
#include "SquareStraightLinkPipePoint.h"

GLOBE_NS

SquareThreeLinkPipePoint::SquareThreeLinkPipePoint(std::vector<osg::Vec3d> vecDir, osg::Vec3d postion, double dbWidth, double dbHeight, double dbThirdWidth, double dbthirdHeight, std::string strPointID, std::string strTypeName)
									:PipePoint(postion, strPointID,strTypeName)
{
	//������������
	m_vecDir = vecDir;
	//�ܾ���
	m_dbWidth = dbWidth / 1000.0;
	//�ܾ���
	m_dbHeight = dbHeight / 1000.0;

	//�������ܾ���
	m_dbThirdWidth = dbThirdWidth / 1000.0;
	//�������ܾ���
	m_dbthirdHeight = dbthirdHeight / 1000.0;

	m_originePoint = osg::Vec3d(0.0,0.0,0.0);

	m_ptrVetexArry = NULL;
	m_ptrNormal = NULL;
	m_ptrIndex = NULL;

	//�Ӵ�
	m_dbBold = 1.2;
	//��ͷ�ӳ�
	m_dbExtend = 1.1;
	m_dbOuterExtend = 0.3;
	//��Ȧ�Ӵ�
	m_dbOuterBold = 1.06;
}

void SquareThreeLinkPipePoint::setOuterExtend(double dbOuterExtend)
{
	m_dbOuterExtend = dbOuterExtend;
}

bool SquareThreeLinkPipePoint::build()
{	
	if (fabs(m_dbWidth) <= DBL_EPSILON || fabs(m_dbHeight) <= DBL_EPSILON)
	{
		//m_dbPipeSize = 0.05*1.2;
		return false;
	}

	m_ptrVetexArry = new osg::Vec3dArray();
	m_ptrNormal = new osg::Vec3dArray();
	m_ptrIndex = new osg::DrawElementsUShort(osg::PrimitiveSet::TRIANGLES);
	
	std::vector<osg::Vec3d> m_TowLink;
	m_TowLink.push_back(m_vecDir[0]);
	m_TowLink.push_back(m_vecDir[1]);
	//���Ƚ�һ����ͨ
	SquareTwoLinkPipePoint squareTwoLink(m_TowLink, m_centerPostion, m_dbWidth * 1000, m_dbHeight * 1000, m_strPointID,m_strTypeName);
	squareTwoLink.setOriginPoint(m_originePoint);
	squareTwoLink.setExtend(1.3);
	bool bIsOk = squareTwoLink.build();

	m_ptrVetexArry = squareTwoLink.getVetexArray();
	m_ptrNormal = squareTwoLink.getNormalArray();
	m_ptrIndex = squareTwoLink.getIndexArray();

	//�ٽ�һ��ֱͨ
	SquareStraightLinkPipePointPtr ptrStraight = new SquareStraightLinkPipePoint(m_vecDir[2], m_centerPostion, m_dbWidth * 1000, m_dbHeight * 1000, m_strPointID,m_strTypeName);
	ptrStraight->setOriginPoint(m_originePoint);
	//���ܵĵ�������΢ϸһЩ������Ƴ���
	ptrStraight->setBold(1.2);
	//���ܵĵ�������΢��һЩ
	//ptrStraight->setExtend(2.5);
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

SquareThreeLinkPipePoint::~SquareThreeLinkPipePoint()
{

}

GLOBE_ENDNS