#include "cxkernel/kernel/visualscene.h"

namespace cxkernel
{
	VisualScene::VisualScene(Qt3DCore::QNode* parent)
		:XRenderGraph(parent)
	{
		Qt3DCore::QEntity* root = rootEntity();
		m_printerEntity = new XEntity(root);
	}

	VisualScene::~VisualScene()
	{

	}
}