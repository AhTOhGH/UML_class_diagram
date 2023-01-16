#include "class_gi.h"
#include <QPainter>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>

CClassGI::CClassGI(QGraphicsItem *pParent_)
    :QGraphicsTextItem(QObject::tr("Новый класс"), pParent_),
      m_pLstFields(nullptr),
      m_pLstMethods(nullptr)
{

}

void CClassGI::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawRect(boundingRect());
    QGraphicsTextItem::paint(painter, option, widget);
}

QPointF BottomLeftGI(const QGraphicsItem* pItem_)
{
    QPointF itemPos = pItem_->pos();
    const int nItemHeight = pItem_->boundingRect().height();
    itemPos.ry()+=nItemHeight;

    return itemPos;
}

void CClassGI::AddFiled(const QString fieldName_)
{
    if(!m_pLstFields)
    {
        QPointF myPos = boundingRect().bottomLeft();

        m_pLstFields = new CListGI(this);
        m_pLstFields->setPos(myPos);
    }

    m_pLstFields->AddItem(fieldName_);

    if(m_pLstMethods)
    {
        QPointF lstFieldPos = BottomLeftGI(m_pLstFields);
        m_pLstMethods->setPos(lstFieldPos);
    }

    fitWidth();
}

void CClassGI::AddMethod(const QString &methodName_)
{
    if(!m_pLstMethods)
    {
        m_pLstMethods = new CListGI(this);
        QPointF bottomLeft = boundingRect().bottomLeft();
        if(m_pLstFields)
            bottomLeft.ry() += m_pLstFields->rect().height();

        m_pLstMethods->setPos(bottomLeft);
    }
    m_pLstMethods->AddItem(methodName_);

    fitWidth();
}

void CClassGI::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu menu;
    QAction *addField = menu.addAction("Добавить поле");
    QAction *addMethod = menu.addAction("Добавить метод");
    QAction *selectedAction = menu.exec(event->screenPos());

    if(selectedAction == addField)
    {
        AddFiled(QObject::tr("Новое поле"));
    }
    else if(selectedAction == addMethod)
    {
        AddMethod(QObject::tr("Новый метод"));
    }
}

void CClassGI::fitWidth()
{
    int nMaxWidth = boundingRect().width();
    if(m_pLstFields)
        nMaxWidth = std::max(nMaxWidth, int(m_pLstFields->rect().width()));
    if(m_pLstMethods)
        nMaxWidth = std::max(nMaxWidth, int(m_pLstMethods->rect().width()));

    if(m_pLstFields)
    {
        QRectF sourceRect = m_pLstFields->rect();
        sourceRect.setWidth(nMaxWidth);
        m_pLstFields->setRect(sourceRect);
    }
    if(m_pLstMethods)
    {
        QRectF sourceRect = m_pLstMethods->rect();
        sourceRect.setWidth(nMaxWidth);
        m_pLstMethods->setRect(sourceRect);
    }
}

CListGI::CListGI(QGraphicsItem *pParentItem_)
    : QGraphicsRectItem(pParentItem_)
{
#ifdef QT_DEBUG
    setFlag(QGraphicsItem::ItemIsSelectable);
    setPen(QPen(Qt::white));
#endif
}

void CListGI::AddItem(const QString &item_)
{
    QPointF bottomLeft(0, 0);
    auto children = childItems();
    if(!children.isEmpty())
        bottomLeft = BottomLeftGI(children.last());

    QGraphicsTextItem* pNewItem = new QGraphicsTextItem(item_, this);
    pNewItem->setTextInteractionFlags(pNewItem->textInteractionFlags().setFlag(Qt::TextEditable));
    pNewItem->setPos(bottomLeft);

    QRectF rc = rect();
    int nMaxWidth = rc.width();
    children = childItems();
    for (int i = 0; i < children.size(); ++i)
    {
        nMaxWidth = std::max(nMaxWidth, int(children[i]->boundingRect().width()));
    }

    rc.setHeight(rc.height()+pNewItem->boundingRect().height());
    rc.setWidth(nMaxWidth);
    setRect(rc);
}
