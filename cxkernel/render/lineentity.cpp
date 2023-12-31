#include "lineentity.h"
#include "qtuser3d/geometry/linecreatehelper.h"
#include "cxkernel/render/purexeffect.h"
#include "cxkernel/render/coloreffect.h"
#include <Qt3DRender/QRenderPass>

namespace cxkernel
{
	LineEntity::LineEntity(Qt3DCore::QNode* parent)
		:XEntity(parent)
		, m_usePure(true)
	{
		m_colorParameter = setParameter("color", QVector4D(1.0f, 0.0f, 0.0f, 1.0f));

		Qt3DRender::QDepthTest* depthTest = new Qt3DRender::QDepthTest(m_material);
		depthTest->setDepthFunction(Qt3DRender::QDepthTest::Always);
		 
		m_colorEffect = new ColorEffect();
		m_colorEffect->addRenderState(0, depthTest);
		m_colorEffect->addPassFilter(0, QStringLiteral("overlayPass"));

		m_pureEffect = new PureXEffect();
		m_pureEffect->addRenderState(0, depthTest);
		m_pureEffect->addPassFilter(0, QStringLiteral("overlayPass"));
		
		m_lineWidth = new Qt3DRender::QLineWidth();
		m_pureEffect->addRenderState(0, m_lineWidth);
		m_colorEffect->addRenderState(0, m_lineWidth);

		setEffect(m_pureEffect);

	}
	
	LineEntity::~LineEntity()
	{
	}

	void LineEntity::setLineWidth(float width)
	{
		m_lineWidth->setValue(width);
	}

	void LineEntity::updateGeometry(const QVector<QVector3D>& positions, const QVector<QVector4D>& colors, bool loop)
	{
		int pointsNum = (int)positions.size();
		if (pointsNum <= 0)
			updateGeometry(pointsNum, nullptr, nullptr);
		else
		{
			updateGeometry(pointsNum, (float*)&positions.at(0), (colors.size() > 0 ? (float*)&colors.at(0) : nullptr));
		}
	}

	void LineEntity::updateGeometry(const QVector<QVector3D>& positions, bool loop)
	{
		updateGeometry(positions.size(), positions.size() > 0 ? (float*)&positions.at(0) : nullptr, nullptr);
	}

	void LineEntity::updateGeometry(int pointsNum, float* positions, float* colors, bool loop)
	{
		if (m_usePure && colors)
		{
			setEffect(m_colorEffect);
			m_usePure = false;
		}
		else if (!m_usePure && !colors)
		{
			setEffect(m_pureEffect);
			m_usePure = true;
		}

		Qt3DRender::QGeometryRenderer::PrimitiveType type = Qt3DRender::QGeometryRenderer::Lines;
		if (loop) type = Qt3DRender::QGeometryRenderer::LineLoop;
		setGeometry(qtuser_3d::LineCreateHelper::create(pointsNum, positions, colors), type);
	}

	void LineEntity::updateGeometry(Qt3DRender::QGeometry* geometry, bool color, bool loop)
	{
		if (m_usePure && color)
		{
			setEffect(m_colorEffect);
			m_usePure = false;
		}
		else if (!m_usePure && !color)
		{
			setEffect(m_pureEffect);
			m_usePure = true;
		}

		Qt3DRender::QGeometryRenderer::PrimitiveType type = Qt3DRender::QGeometryRenderer::Lines;
		if (loop) type = Qt3DRender::QGeometryRenderer::LineLoop;
		setGeometry(geometry, type);
	}

	void LineEntity::setColor(const QVector4D& color)
	{
		m_colorParameter->setValue(color);
	}
}