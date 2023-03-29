#ifndef AUTOLAYOUT_NEST2D_JOB_H
#define AUTOLAYOUT_NEST2D_JOB_H
#include "basickernelexport.h"
#include "data/modeln.h"
#include "nestplacer/nestplacer.h"

#include "qtusercore/module/job.h"

namespace creative_kernel
{
    struct NestResult
    {
        ModelN* model;
        nestplacer::TransMatrix trans;
    };

    class BASIC_KERNEL_API Nest2DJob : public qtuser_core::Job
    {
        Q_OBJECT
    public:
        Nest2DJob(QObject* parent = nullptr);
        virtual ~Nest2DJob();

        void setNestType(nestplacer::PlaceType type);
        void setInsertModelN(ModelN* model);
    protected:
        QString name();
        QString description();
        void failed();                        // invoke from main thread
        void successed(qtuser_core::Progressor* progressor);                     // invoke from main thread
        void work(qtuser_core::Progressor* progressor);    // invoke from worker thread

        void insert();
        void layoutAll();
    protected:
        QList<ModelN*> m_models;
        ModelN* m_insert;

        trimesh::vec3 m_size;
        nestplacer::PlaceType m_nestType;

        QList<NestResult> m_result;
    };
}

#endif // AUTOLAYOUT_NEST2D_JOB_H
