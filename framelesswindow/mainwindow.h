#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "framelesswindow.h"
#include <QString>
#include <QQuickWidget>
namespace Ui {
class MainWindow;
}

class MainWindow : public CFramelessWindow
{
    Q_OBJECT
    Q_PROPERTY(bool isMax READ isMax)
    Q_PROPERTY(int width READ width NOTIFY resized) 
    Q_PROPERTY(int height READ height NOTIFY resized) 
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setCenterWidget(QQuickWidget *w);
    Q_INVOKABLE void showLessViewMinimized();
    Q_INVOKABLE void showLessViewMaximized();
    //Q_INVOKABLE void showLessViewNormal();
    bool isMax() const;
private slots:
    void on_btnClose_clicked();
    void on_bthFull_clicked();
    void on_btnIncreaseMargin_clicked();
    void on_btnDecreaseMargin_clicked();
    void on_btnResizeable_clicked();
protected:
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    QString currentMargins();
private:
    Ui::MainWindow *ui;
    QQuickWidget *m_quickview;
signals:
    void resized(QSize rect);
};

#endif // MAINWINDOW_H
