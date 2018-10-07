#include "port.h"

#include <QPainter>
#include <QDebug>
#include <QGraphicsScene>
#include "basenode.h"

int Port::type() const
{
    return (m_isInput ? InputPortType : OutputPortType);
}


Port::Port(float x, float y, float width, float height, QGraphicsItem* parent/*=0*/)
    : QGraphicsItem(parent),
      m_wire(nullptr)
{
    this->setX(x);
    this->setY(y);
    m_width = width;
    m_height = height;
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
}

QRectF Port::boundingRect() const
{
    return QRectF(- m_width / 2, - m_height / 2,
                  m_width, m_height);
}

void Port::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter)
    Q_UNUSED(option)
    Q_UNUSED(widget)
    QRectF rect = boundingRect();
    QPen pen(Qt::black, 0);
    painter->setPen(pen);
    painter->fillRect(rect, Qt::white);
    painter->drawRect(rect);
}

bool Port::isInput() const
{
    return m_isInput;
}

void Port::setIsInput(bool isInput)
{
    m_isInput = isInput;
}

void Port::triggerParentToRecalculate()
{
    if(m_isInput)
    {
        BaseNode *myParentNode = (BaseNode*) this->parentItem();
        myParentNode->recalculateValue(this);
    }
}

Wire *Port::wire() const
{
    if(m_wire)
        return m_wire;
    return nullptr;
}

void Port::setWire(Wire *value)
{
    m_wire = value;
}

QVariant Port::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{

    if(change == QGraphicsItem::ItemScenePositionHasChanged)
    {
        QPointF moveVector = value.toPointF();
        if(m_wire)
        {
            if(m_isInput)
            {
                m_wire->moveEndPositionBy(moveVector);
            }
            else
            {
                m_wire->moveStartPositionBy(moveVector);
            }
            m_wire->updatePath();
        }

    }
    return QGraphicsItem::itemChange(change, value);
}
