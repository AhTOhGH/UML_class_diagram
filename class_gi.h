#ifndef CCLASSGI_H
#define CCLASSGI_H

#include <QGraphicsTextItem>

class CListGI : public QGraphicsRectItem
{
public:
    CListGI(QGraphicsItem* pParentItem_ = nullptr);

    void AddItem(const QString& item_);
};

class CClassGI : public QGraphicsTextItem
{
public:
    CClassGI(QGraphicsItem* pParent_ = nullptr);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    void AddFiled(const QString fileldName_);
    void AddMethod(const QString& methodName_);

protected:
     void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

private:
     void fitWidth();

private:
    CListGI* m_pLstFields;
    CListGI* m_pLstMethods;
};

#endif // CCLASSGI_H
