#pragma once
#include "preconfig.h"
#include "linesymbol.h"
#include "pointsymbol.h"

namespace GeoStar
{
	namespace Electric
	{ 
		class GS_API GsElectricMarkerLineSymbol :public KERNEL_NAME::GsLineSymbol
		{
			KERNEL_NAME::GsLineSymbolPtr m_ptrBaseLine;
			KERNEL_NAME::GsPointSymbolPtr m_ptrMarker;
		protected:
			/// \brief �����Ƶ�ʱ����
			/// \details ����ͨ�����Ǵ˷���ʵ��ʵ�ʵĻ���
			virtual void OnDraw(KERNEL_NAME::GsGeometryBlob* pBuffer);

			/// \brief �������ݲ���
			/// \details ����ͨ�����Ǵ˺���ʵ�ֻ���ǰ�Լ������ݵĴ����������ƽ����
			virtual geostar::gobjptr GeometryOperator(geostar::gobjptr& pPath);

			/// \brief ����ʼ���Ƶ�ʱ����
			/// \details ����ͨ�����Ǵ˷���ʵ���Զ��������׼��
			virtual void OnStartDrawing();
			/// \brief ���������Ƶ�ʱ����
			/// \details ����ͨ�����Ǵ˷���ʵ���Զ�������ݻ��չ���
			virtual void OnEndDrawing();
		public:
			GsElectricMarkerLineSymbol(KERNEL_NAME::GsLineSymbol* baseLine, KERNEL_NAME::GsPointSymbol* pMarker);
			~GsElectricMarkerLineSymbol();

		};
		GS_SMARTER_PTR(GsElectricMarkerLineSymbol);

	}
}

