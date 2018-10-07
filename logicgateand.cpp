#include "logicgateand.h"


#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include <QPainter>
#include <QPen>
#include <QFont>
#include <QFontMetrics>

AndLogicGate::AndLogicGate(float x, float y) :
    m_inputPort1(nullptr),
    m_inputPort2(nullptr),
    m_outputPort(nullptr)
{
    // set position width and height
    this->setX(x);
    this->setY(y);
    m_width = 100.0;
    m_height = 100.0;

    // initialize ports
    m_outputPort = new Port(this->m_width/2.0 + 5.0, 0.0, 10.0, 10.0, this);
    m_outputPort->setIsInput(false);
    m_inputPort1 = new Port(- 55.0, - 25.0, 10.0, 10.0, this);
    m_inputPort1->setIsInput(true);
    m_inputPort2 = new Port(- 55.0, + 25.0, 10.0, 10.0, this);
    m_inputPort2->setIsInput(true);
}

AndLogicGate::~AndLogicGate()
{
}

void AndLogicGate::recalculateValue(Port* sourcePort)
{
    Q_UNUSED(sourcePort)
    if(m_inputPort1 && m_inputPort2 && m_outputPort && m_inputPort1->wire() && m_inputPort2->wire() && m_outputPort->wire())
    {
        m_outputPort->wire()->setValue(m_inputPort1->wire()->value() && m_inputPort2->wire()->value());
        m_outputPort->wire()->update();
    }

}

void AndLogicGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
    QString label("AND");
    painter->drawText(-fm.width(label)/2.0, painter->font().pointSize()/2.0,  label);
}
