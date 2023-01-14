#ifndef CCLASSITEM_H
#define CCLASSITEM_H

#include <QGraphicsItem>

class CClassItem : public QGraphicsItem
{
public:
    CClassItem(QGraphicsItem* pParent_ = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

protected:
     void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

private:
     QRect classNameRect(const QFontMetrics& fm_) const;
     QRect fieldsRect(const QFontMetrics& fm_) const;

private:
    QString m_className;
    std::vector<QString> m_fields;
    std::vector<QString> m_methods;
};

#endif // CCLASSITEM_H
