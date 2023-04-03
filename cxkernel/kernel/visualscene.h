#ifndef CXKERNEL_VISUALSCENE_1679908098344_H
#define CXKERNEL_VISUALSCENE_1679908098344_H
#include "cxkernel/render/xrendergraph.h"
#include "cxkernel/render/xentity.h"

namespace cxkernel
{
	class VisualScene : public XRenderGraph
	{
	public:
		VisualScene(Qt3DCore::QNode* parent = nullptr);
		virtual ~VisualScene();

	protected:
		XEntity* m_printerEntity;
	};
}

#endif // CXKERNEL_VISUALSCENE_1679908098344_H