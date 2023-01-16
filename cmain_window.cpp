#include "main_window.h"
#include "./ui_main_window.h"
#include <QGraphicsScene>
#include "class_item.h"
#include "class_gi.h"

CMainWindow::CMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CMainWindow)
{
    ui->setupUi(this);
    m_pScene = new QGraphicsScene(this);

    ui->graphicsView->setScene(m_pScene);

    connect(ui->actAddClass, &QAction::triggered, this, &CMainWindow::onAddClass);
}

CMainWindow::~CMainWindow()
{
    delete ui;
}

void CMainWindow::onAddClass()
{
    auto* pNewClass = new CClassGI();
    pNewClass->setTextInteractionFlags(pNewClass->textInteractionFlags().setFlag(Qt::TextEditable));
    pNewClass->setFlag(QGraphicsItem::GraphicsItemFlag::ItemIsMovable);
    pNewClass->setFlag(QGraphicsItem::GraphicsItemFlag::ItemIsSelectable);
    m_pScene->addItem(pNewClass);
}

