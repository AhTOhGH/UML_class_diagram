#include "main_window.h"
#include "./ui_main_window.h"
#include <QGraphicsScene>
#include "class_gi3.h"
#include <QGraphicsItem>

CMainWindow::CMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CMainWindow)
{
    ui->setupUi(this);
    m_pScene = new QGraphicsScene(this);

    ui->graphicsView->setScene(m_pScene);

    connect(ui->actAddClass, &QAction::triggered, this, &CMainWindow::onAddClass);
    connect(ui->actTest, &QAction::triggered, this, &CMainWindow::onTest);
}

CMainWindow::~CMainWindow()
{
    delete ui;
}

void CMainWindow::onAddClass()
{
//    auto* pNewClass = new CClassGI();
//    pNewClass->setTextInteractionFlags(pNewClass->textInteractionFlags().setFlag(Qt::TextEditable));
//    pNewClass->setFlag(QGraphicsItem::GraphicsItemFlag::ItemIsMovable);
//    pNewClass->setFlag(QGraphicsItem::GraphicsItemFlag::ItemIsSelectable);
//    m_pScene->addItem(pNewClass);

    CClassGI3* pNewClass = new CClassGI3("adassdfavx");
    pNewClass->InsertField("dsdfa");
    pNewClass->InsertField("dsdfa");
    pNewClass->InsertField("dsdfa");
    m_pScene->addItem(pNewClass);
}

void CMainWindow::onTest()
{
    CVBoxLayout* pLayout = new CVBoxLayout();
    pLayout->AddItem(new QGraphicsTextItem("test", pLayout));
    pLayout->AddItem(new QGraphicsTextItem("test", pLayout));
    pLayout->AddItem(new QGraphicsTextItem("test", pLayout));
    m_pScene->addItem(pLayout);
}

