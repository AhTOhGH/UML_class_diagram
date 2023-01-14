#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <QMainWindow>

class QGraphicsScene;

QT_BEGIN_NAMESPACE
namespace Ui { class CMainWindow; }
QT_END_NAMESPACE

class CMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    CMainWindow(QWidget *parent = nullptr);
    ~CMainWindow();

private:
    void onAddClass();

private:
    Ui::CMainWindow *ui;
    QGraphicsScene* m_pScene;
};
#endif // CMAINWINDOW_H
