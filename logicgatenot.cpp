#include "logicgatenot.h"


#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include <QPainter>
#include <QPen>
#include <QFont>
#include <QFontMetrics>

LogicGateNot::LogicGateNot(float x, float y) :
    m_inputPort(nullptr),
    m_outputPort(nullptr)
{
    // set position width and height
    this->setX(x);
    this->setY(y);
    m_width = 100.0;
    m_height = 50.0;

    // initialize ports
    m_outputPort = new Port(this->m_width/2.0 + 5.0, 0.0, 10.0, 10.0, this);
    m_outputPort->setIsInput(false);
    m_inputPort = new Port(- 55.0, 0.0, 10.0, 10.0, this);
    m_inputPort->setIsInput(true);
}

LogicGateNot::~LogicGateNot()
{
}

void LogicGateNot::recalculateValue(Port* sourcePort)
{
    Q_UNUSED(sourcePort)
    if(m_inputPort && m_outputPort && m_inputPort->wire() && m_outputPort->wire())
    {
        m_outputPort->wire()->setValue(!m_inputPort->wire()->value());
        m_outputPort->wire()->update();
    }

}

void LogicGateNot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
    QFontMetrics fm(painter->font());
    QString label("NOT");
    painter->drawText(-fm.width(label)/2.0, painter->font().pointSize()/2.0,  label);
}
