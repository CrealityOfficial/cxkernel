#ifndef CXKERNEL_HEADER_1681019989189_H
#define CXKERNEL_HEADER_1681019989189_H
#include "cxkernel/cxkernelinterface.h"
#include "trimesh2/TriMesh.h"
#include "trimesh2/TriMesh_algo.h"
#include "trimesh2/quaternion.h"
#include "ccglobal/tracer.h"
#include <memory>
#include <functional>

#include <QtCore/QDebug>

typedef std::shared_ptr<trimesh::TriMesh> TriMeshPtr;

typedef std::function<void()> anonymous_func;
namespace cxkernel
{
	CXKERNEL_API TriMeshPtr loadFromFile(const QString& fileName);
}

#endif // CXKERNEL_HEADER_1681019989189_H