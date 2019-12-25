#include "PipeLine.h"

using namespace KERNEL_NAME;
using namespace UTILITY_NAME;

GLOBE_NS

PipeLine::PipeLine(osg::Vec3d p1, osg::Vec3d p2, std::string strPipeID, std::string strTypeName)
{
	m_ptrVetexArry = NULL;
	m_ptrNormal = NULL;
	m_ptrIndex = NULL;

	m_p1 = p1;
	m_p2 = p2;

	m_bIsMinus = true;
	m_strPipeName = strPipeID;
	m_strTypeName = strTypeName;
}

PipeLine::PipeLine()
{

}

void PipeLine::setOriginePoint(osg::Vec3d point)
{
	m_originePoint = point;
	m_IsSetOriginPoint = true;
}


void PipeLine::setMinus(bool isMinus)
{
	m_bIsMinus = isMinus;
}

bool PipeLine::IsSetOriginePoint()
{
	return m_IsSetOriginPoint;
}

std::string PipeLine::getPipeName()
{
	return m_strPipeName;
}

void PipeLine::SaveToObj(std::string strPath)
{
	if (m_ptrVetexArry == NULL)
		return;

	GsString gstrFileName = GsEncoding::ToUtf8(strPath.c_str());
	GsDir dir(gstrFileName);
	if (!dir.Exists())
		dir.Create();

	//存管线obj
	std::string strObjPath = strPath + m_strPipeName + ".obj";
	std::ofstream ofileObj;
	ofileObj.open(strObjPath);
	ofileObj.precision(18);

	if (!ofileObj.is_open()/* || !ofileMaterial.is_open()*/)
		return;

	//材质名先存到obj
	ofileObj << "mtllib " + m_strTypeName + ".mtl" << std::endl << std::endl;

	//顶点
	osg::Vec3dArray::iterator it = m_ptrVetexArry->begin();
	for (it; it != m_ptrVetexArry->end(); it++)
	{
		ofileObj << "v " << (*it).x() << " " << (*it).y() << " " << (*it).z() << " " << std::endl;
	}

	ofileObj << std::endl;

	//法线
	osg::Vec3dArray::iterator normalit = m_ptrNormal->begin();
	for (normalit; normalit != m_ptrNormal->end(); normalit++)
	{
		ofileObj << "vn " << (*normalit).x() << " " << (*normalit).y() << " " << (*normalit).z() << " " << std::endl;
	}

	ofileObj << std::endl;

	//使用该材质
	ofileObj << "usemtl " + std::string(m_strTypeName + "_mtl") << std::endl;

	ofileObj << std::endl;

	//组信息
	ofileObj << "g " + std::string(m_strPipeName + "_0") << std::endl;

	ofileObj << std::endl;

	//索引
	int nCount = m_ptrIndex->size();
	for (int i = 0; i < nCount; i += 3)
	{
		ofileObj << "f " << (*m_ptrIndex)[i] + 1 << "//" << (*m_ptrIndex)[i] + 1 << " "
			<< (*m_ptrIndex)[i + 1] + 1 << "//" << (*m_ptrIndex)[i + 1] + 1 << " "
			<< (*m_ptrIndex)[i + 2] + 1 << "//" << (*m_ptrIndex)[i + 2] + 1 << " " << std::endl;
	}

	ofileObj.close();
	//ofileMaterial.close();
}

void PipeLine::setVetexArray(const osg::Vec3dArray* ptrVetexArray)
{
	m_ptrVetexArry = const_cast<osg::Vec3dArray*>(ptrVetexArray);
}

osg::Vec3dArray* PipeLine::getVetexArray()
{
	return m_ptrVetexArry.get();
}

osg::Vec3dArray* PipeLine::getNormalArray()
{
	return m_ptrNormal.get();
}

osg::DrawElementsUShort* PipeLine::getIndexArray()
{
	return m_ptrIndex.get();
}

PipeLine::~PipeLine()
{

}

GLOBE_ENDNS