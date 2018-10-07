#include "switch.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include <QPainter>
#include <QPen>


Switch::Switch(float x, float y) :
    m_inputValue(false),
    switchArea(QRect(- 20 / 2, - 20 / 2, 20, 20))
{
    this->setX(x);
    this->setY(y);
    m_width = 100.0;
    m_height = 50.0;

    m_outputPort = new Port(this->m_width/2.0 + 10.0/2.0, 0.0, 10.0, 10.0, this);
    m_outputPort->setIsInput(false);
}

void Switch::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter)
    Q_UNUSED(option)
    Q_UNUSED(widget)
    QRectF rect = boundingRect();
    QPen pen(Qt::black, 0);
    if(this->isSelected())
    {
        pen = QPen(Qt::red, 0);
    }
    painter->setPen(pen);

    QPainterPath path;
    path.addRoundedRect(rect, 0, 0);

    QLinearGradient gradient(rect.topLeft(), rect.bottomRight());
    gradient.setColorAt(0, QColor(255, 255, 255));
    gradient.setColorAt(1, QColor(128, 128, 128));

    painter->fillPath(path, gradient);
    painter->drawPath(path);

    painter->setPen(QPen(Qt::black, 0));
    if (m_inputValue)
    {
        painter->fillRect(switchArea, Qt::black);
    }
    else
    {
        painter->fillRect(switchArea, Qt::white);
    }
    painter->drawRect(switchArea);
}

void Switch::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    if (switchArea.contains(event->pos()))
    {
        m_inputValue = !m_inputValue;
        update();
        if(m_outputPort && m_outputPort->wire())
        {
            m_outputPort->wire()->setValue(m_inputValue);
        }
    }
    else
    {
        QGraphicsItem::mousePressEvent(event);
    }

    BaseNode::mousePressEvent(event);
}
