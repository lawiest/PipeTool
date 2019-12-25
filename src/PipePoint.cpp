#include "PipePoint.h"

GLOBE_NS

PipePoint::PipePoint(osg::Vec3d postion, std::string strPointID, std::string strTypeName)
{
	//���ĵ�
	m_centerPostion = postion;
	//�ܵ�ID����̽���
	m_strPointID = strPointID;
	m_strTypeName = strTypeName;
	m_originePoint = osg::Vec3d(0.0, 0.0, 0.0);

	m_ptrVetexArry = NULL;
	m_ptrNormal = NULL;
	m_ptrIndex = NULL;
}

void PipePoint::setOriginPoint(const osg::Vec3d& originPoint)
{
	m_originePoint = originPoint;
}

std::string PipePoint::getPipePointName()
{
	return m_strPointID;
}

osg::Vec3dArray* PipePoint::getVetexArray()
{
	return m_ptrVetexArry.get();
}

osg::Vec3dArray* PipePoint::getNormalArray()
{
	return m_ptrNormal.get();
}

osg::DrawElementsUShort* PipePoint::getIndexArray()
{
	return m_ptrIndex.get();
}

//���浽Obj
void PipePoint::SaveToObj(std::string strPath)
{
	if (m_ptrVetexArry == NULL)
		return;

	UTILITY_NAME::GsString gstrFileName = UTILITY_NAME::GsEncoding::ToUtf8(strPath.c_str());
	UTILITY_NAME::GsDir dir(gstrFileName);
	if (!dir.Exists())
		dir.Create();

	//�����obj
	std::string strObjPath = strPath + m_strPointID + ".obj";
	std::ofstream ofileObj;
	ofileObj.open(strObjPath);
	ofileObj.precision(18);

	if (!ofileObj.is_open() /*|| !ofileMaterial.is_open()*/)
		return;

	//�������ȴ浽obj
	ofileObj << "mtllib " + m_strTypeName + ".mtl" << std::endl;

	ofileObj << std::endl;

	//����
	osg::Vec3dArray::iterator it = m_ptrVetexArry->begin();
	for (it; it != m_ptrVetexArry->end(); it++)
	{
		ofileObj << "v " << (*it).x() << " " << (*it).y() << " " << (*it).z() << " " << std::endl;
	}

	ofileObj << std::endl;

	//����
	osg::Vec3dArray::iterator normalit = m_ptrNormal->begin();
	for (normalit; normalit != m_ptrNormal->end(); normalit++)
	{
		ofileObj << "vn " << (*normalit).x() << " " << (*normalit).y() << " " << (*normalit).z() << " " << std::endl;
	}

	ofileObj << std::endl;

	//ʹ�øò���
	ofileObj << "usemtl " + std::string(m_strTypeName + "_mtl") << std::endl;

	ofileObj << std::endl;

	//����Ϣ
	ofileObj << "g " + std::string(m_strPointID + "_0") << std::endl;

	ofileObj << std::endl;

	//����
	int nCount = m_ptrIndex->size();
	for (int i = 0; i < nCount; i += 3)
	{
		ofileObj << "f " << (*m_ptrIndex)[i] + 1 << "//" << (*m_ptrIndex)[i] + 1 << " "
			<< (*m_ptrIndex)[i + 1] + 1 << "//" << (*m_ptrIndex)[i + 1] + 1 << " "
			<< (*m_ptrIndex)[i + 2] + 1 << "//" << (*m_ptrIndex)[i + 2] + 1 << " " << std::endl;
	}
	ofileObj.close();
}

PipePoint::~PipePoint()
{

}

GLOBE_ENDNS