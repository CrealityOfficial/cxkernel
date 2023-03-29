#ifndef CREATIVE_KERNEL_HEADER_1595470868902_H
#define CREATIVE_KERNEL_HEADER_1595470868902_H
#include <memory>
#include <functional>

#include "trimesh2/TriMesh.h"
#include "trimesh2/TriMesh_algo.h"

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QDebug>

namespace cxkernel
{
	typedef std::shared_ptr<trimesh::TriMesh> TriMeshPtr;
}

#endif // CREATIVE_KERNEL_HEADER_1595470868902_H