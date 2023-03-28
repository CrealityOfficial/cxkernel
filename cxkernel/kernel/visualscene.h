#ifndef CXKERNEL_VISUALSCENE_1679908098344_H
#define CXKERNEL_VISUALSCENE_1679908098344_H
#include "qtuser3d/prospective/xrendergraph.h"

namespace cxkernel
{
	class VisualScene : public qtuser_3d::XRenderGraph
	{
	public:
		VisualScene(Qt3DCore::QNode* parent = nullptr);
		virtual ~VisualScene();
	};
}

#endif // CXKERNEL_VISUALSCENE_1679908098344_H