#include "logicgateled.h"


#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include <QPainter>
#include <QPen>
#include <QFont>
#include <QFontMetrics>

LogicGateLed::LogicGateLed(float x, float y) :
    m_inputValue(false),
    m_ledArea(QRect(- 20 / 2, - 20 / 2, 20, 20)),
    m_inputPort(nullptr)
{
    // set position width and height
    this->setX(x);
    this->setY(y);
    m_width = 100.0;
    m_height = 50.0;

    // initialize ports
    m_inputPort = new Port(- 55.0, 0.0, 10.0, 10.0, this);
    m_inputPort->setIsInput(true);
}

LogicGateLed::~LogicGateLed()
{
}

void LogicGateLed::recalculateValue(Port* sourcePort)
{
    Q_UNUSED(sourcePort)
    if(m_inputPort && m_inputPort->wire())
    {
        m_inputValue = m_inputPort->wire()->value();
        update();
    }

}

void LogicGateLed::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
        painter->setBrush(Qt::red);
//        painter->fillRect(m_ledArea, Qt::black);
    }
    else
    {
        painter->setBrush(Qt::white);
//        painter->fillRect(m_ledArea, Qt::white);
    }
    painter->drawEllipse(m_ledArea);
}
