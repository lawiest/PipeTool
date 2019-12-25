#pragma once
#include "dcoreader.h"
#include "dcowriter.h" 
GDC_NS

class GS_API GsDCOTranslater :public UTILITY_NAME::GsRefObject
{
	GsVector<Utility::GsString> m_vecParameter;
public:
	GsDCOTranslater(const GsVector<Utility::GsString>& vecParameter);
	~GsDCOTranslater();
	/// \brief ִ������ת��
	/// \param mapFile ӳ���ļ���·��
	bool Translate(const char* mapFile);
};

GDC_ENDNS