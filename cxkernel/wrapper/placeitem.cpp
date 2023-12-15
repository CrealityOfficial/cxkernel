#include "placeitem.h"

namespace cxkernel
{
    PlaceItemEx::PlaceItemEx(const std::vector<trimesh::vec3>& outline, QObject* parent)
        : QObject(parent)
    {
        m_outline = outline;
    }

    PlaceItemEx::~PlaceItemEx()
    {
    }

    void PlaceItemEx::polygon(nestplacer::PlacerItemGeometry& geometry)
    {
        geometry.outline = m_outline;
        //geometry.holes = 
    }

    void PlaceItemEx::setNestResult(const nestplacer::PlacerResultRT& _result)
    {
        result = _result;
    }
}