#ifndef CCLASSGI3_H
#define CCLASSGI3_H

#include <QGraphicsItem>

class CBoxLayout : public QGraphicsRectItem
{
public:
    CBoxLayout(QGraphicsItem* pParent_ = nullptr);

    //  TODO: Реализовать вставку в конкретное место
    void AddItem(QGraphicsItem* pItem_);

protected:
    virtual void toPlace() = 0;

    size_t getCountItems() const;
    QGraphicsItem* getItem(size_t nIndex_) const;

private:
    std::vector<QGraphicsItem*> m_staff;
};

class CVBoxLayout : public CBoxLayout
{
public:
    CVBoxLayout(QGraphicsItem* pParent_ = nullptr);

protected:
    void toPlace() override;
};

class CListGI2 : public CVBoxLayout
{
public:
    CListGI2(QGraphicsItem* pParent_ = nullptr);

    //  TODO: Реализовать вставку в конкретное место
    void InsertField(const QString& fieldName_/*, size_t after_*/);
    size_t GetFieldCount() const;
    QString GetFieldName(size_t index_) const;
};

class CClassGI3 : public CVBoxLayout
{
public:
    CClassGI3(const QString& className_ /*= QObject::tr("Новый класс")*/, QGraphicsItem* pParent_ = nullptr);

    void SetClassName(const QString& newClassName_);
    QString GetClassName() const;

    //  TODO: Реализовать вставку в конкретное место
    void InsertField(const QString& fieldName_/*, size_t after_*/);
    size_t GetFieldCount() const;
    QString GetFieldName(size_t index_) const;

    //  TODO: Реализовать вставку в конкретное место
    void InsertMethod(const QString& methodName_/*, size_t after_*/);
    size_t GetMethodCount() const;
    QString GetMethodName(size_t index_) const;

private:
    QGraphicsTextItem* m_className;
    CListGI2* m_fields;
    CListGI2* m_methods;
};

#endif // CCLASSGI3_H
