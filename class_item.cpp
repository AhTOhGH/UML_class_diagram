#include "class_item.h"
#include <QPainter>
#include <QGuiApplication>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>

CClassItem::CClassItem(QGraphicsItem* pParent_)
    : QGraphicsItem(pParent_),
      m_className(QObject::tr("Новый класс"))
{

}

QRectF CClassItem::boundingRect() const
{
    QFontMetrics fm(qGuiApp->font());
    QRect rcClassName = classNameRect(fm);
    QRect rcFields = fieldsRect(fm);
    rcFields.moveTop(rcClassName.bottom());

    return rcClassName.united(rcFields);
}

void CClassItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    const auto fm = option->fontMetrics;
    QRect rcClassName = classNameRect(fm);
    QRect rcFields = fieldsRect(fm);
    rcClassName.setWidth(std::max(rcClassName.width(), rcFields.width()));
    painter->drawRect(rcClassName);
    painter->drawText(rcClassName, m_className);

    if(!m_fields.empty())
    {
        rcFields.setWidth(std::max(rcClassName.width(), rcFields.width()));

        rcFields.moveTop(rcClassName.bottom());

        painter->drawRect(rcFields);

        const int nHeight = fm.height();
        for (size_t i = 0; i < m_fields.size(); ++i)
        {
            QPoint shift(0, i*nHeight + nHeight);
            painter->drawText(rcFields.topLeft() + shift, m_fields[i]);
        }
    }

    if(isSelected())
    {
        painter->setPen(QPen(Qt::DashLine));
        painter->drawRect(boundingRect());
    }
}

void CClassItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu menu;
    QAction *addField = menu.addAction("Добавить поле");
    QAction *addMethod = menu.addAction("Добавить метод");
    QAction *selectedAction = menu.exec(event->screenPos());

    if(selectedAction == addField)
    {
        m_fields.push_back(QObject::tr("Новое поле"));
        update(boundingRect());
    }
    else if(selectedAction == addMethod)
    {
        m_fields.push_back(QObject::tr("Новый метод"));
        update(boundingRect());
    }
}

QRect CClassItem::classNameRect(const QFontMetrics &fm_) const
{
    const int adjust = fm_.lineWidth()/2.;
    return fm_.boundingRect(m_className).adjusted(-adjust,-adjust,adjust,adjust);
}

QRect CClassItem::fieldsRect(const QFontMetrics &fm_) const
{
    int nMaxWidth = 0;
    for (size_t i = 0; i < m_fields.size(); ++i)
    {
        nMaxWidth = std::max(fm_.boundingRect(m_fields[i]).width(), nMaxWidth);
    }

    const int nHeight = fm_.height();
    const int adjust = fm_.lineWidth()/2.;
    return QRect(0,0, nMaxWidth, nHeight*m_fields.size()).adjusted(-adjust,-adjust,adjust,adjust);
}
