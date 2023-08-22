#ifndef CXKERNEL_GLOBALCONST_1672882923747_H
#define CXKERNEL_GLOBALCONST_1672882923747_H

#include <QtCore/QObject>
#include <QtCore/QString>

#include "cxkernel/cxkernelinterface.h"

namespace cxkernel {

  class CXKERNEL_API CXKernelConst : public QObject {
    Q_OBJECT;
    Q_PROPERTY(QString version READ version CONSTANT);
    Q_PROPERTY(QString versionExtra READ versionExtra CONSTANT);
    Q_PROPERTY(QString os READ os CONSTANT);
    Q_PROPERTY(QString bundleName READ bundleName CONSTANT);

   public:
    explicit CXKernelConst(QObject* parent = nullptr);
    virtual ~CXKernelConst() = default;

   public:
    QString version() const;
    QString versionExtra() const;
    QString os() const;
    QString bundleName() const;

    QString writableLocation(const QString& subDir, const QString& subSubDir = QString());
  };

}  // namespace cxkernel

#endif  // CXKERNEL_GLOBALCONST_1672882923747_H
