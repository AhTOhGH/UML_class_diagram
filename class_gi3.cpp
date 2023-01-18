#include "class_gi3.h"

CBoxLayout::CBoxLayout(QGraphicsItem *pParent_)
    : QGraphicsRectItem(pParent_)
{

}

void CBoxLayout::AddItem(QGraphicsItem *pItem_)
{
    m_staff.emplace_back(pItem_);
    toPlace();
}

size_t CBoxLayout::getCountItems() const
{
    return m_staff.size();
}

QGraphicsItem *CBoxLayout::getItem(size_t nIndex_) const
{
    return m_staff[nIndex_];
}

CVBoxLayout::CVBoxLayout(QGraphicsItem *pParent_)
    : CBoxLayout(pParent_)
{

}

void CVBoxLayout::toPlace()
{
    QPointF newPos(0, 0);
    double dMaxWidth = 0;
    double dGeneralHeight = 0;
    size_t nCountItems = getCountItems();
    for (size_t index = 0; index < nCountItems; ++index)
    {
        QGraphicsItem* pItem = getItem(index);
        pItem->setPos(newPos);
        QRectF itemBoundingRect = pItem->boundingRect();
        newPos.ry() += itemBoundingRect.height();
        dMaxWidth = std::max(dMaxWidth, itemBoundingRect.width());
        dGeneralHeight+=itemBoundingRect.height();
    }

    QRectF myRc = rect();
    myRc.setWidth(dMaxWidth);
    myRc.setHeight(dGeneralHeight);
    setRect(myRc);
}

CClassGI3::CClassGI3(const QString &className_, QGraphicsItem *pParent_)
    : CVBoxLayout(pParent_),
      m_className(new QGraphicsTextItem(className_, this)),
      m_fields(nullptr),
      m_methods(nullptr)
{
    AddItem(m_className);
}

void CClassGI3::SetClassName(const QString &newClassName_)
{
    m_className->setPlainText(newClassName_);
}

QString CClassGI3::GetClassName() const
{
    return m_className->toPlainText();
}

void CClassGI3::InsertField(const QString &fieldName_)
{
    if(!m_fields)
    {
        m_fields = new CListGI2(this);
        AddItem(m_fields);
    }

    m_fields->InsertField(fieldName_);
}

size_t CClassGI3::GetFieldCount() const
{
    return m_fields->GetFieldCount();
}

QString CClassGI3::GetFieldName(size_t index_) const
{
    return m_fields->GetFieldName(index_);
}

void CClassGI3::InsertMethod(const QString &methodName_)
{
    if(!m_methods)
    {
        m_methods = new CListGI2(this);
        AddItem(m_methods);
    }

    m_methods->InsertField(methodName_);
}

size_t CClassGI3::GetMethodCount() const
{
    return m_methods->GetFieldCount();
}

QString CClassGI3::GetMethodName(size_t index_) const
{
    return m_methods->GetFieldName(index_);
}

void CListGI2::InsertField(const QString &fieldName_)
{
    AddItem(new QGraphicsTextItem(fieldName_, this));
}

size_t CListGI2::GetFieldCount() const
{
    return getCountItems();
}

QString CListGI2::GetFieldName(size_t index_) const
{
    if(QGraphicsTextItem* pItem = dynamic_cast<QGraphicsTextItem*>(getItem(index_)))
    {
        return pItem->toPlainText();
    }

    throw std::out_of_range(std::string("Нет элемента с порядковым номером") + std::to_string(index_));
}
