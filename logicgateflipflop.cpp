#include "logicgateflipflop.h"


#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include <QPainter>
#include <QPen>
#include <QFont>
#include <QFontMetrics>

LogicGateFlipFlop::LogicGateFlipFlop(float x, float y) :
    m_outputValue(false),
    m_previousClockInput(false),
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

LogicGateFlipFlop::~LogicGateFlipFlop()
{
}

void LogicGateFlipFlop::recalculateValue(Port* sourcePort)
{
    if(sourcePort && m_inputPort1 && m_inputPort2 && m_outputPort && m_inputPort1->wire() && m_inputPort2->wire() && m_outputPort->wire())
    {
        if (sourcePort == m_inputPort2)
        {
            bool newClockValue = m_inputPort2->wire()->value();
            if ((newClockValue == true) and (m_previousClockInput == false))
            {
                m_outputValue = m_inputPort1->wire()->value();
            }
            m_previousClockInput = newClockValue;
        }
        m_outputPort->wire()->setValue(m_outputValue);
        m_outputPort->wire()->update();
    }

}

void LogicGateFlipFlop::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
    QString label("D");
    painter->drawText(-rect.width()/2.0 + fm.width(label) - 7.0, painter->font().pointSize()/2.0 - 25.0,  label);
    QString label3("Q");
    painter->drawText(rect.width()/2.0 - fm.width(label3) - 7.0, painter->font().pointSize()/2.0,  label3);

    QString label2(">");
    painter->drawText(-rect.width()/2.0 + fm.width(label2) - 9.0, painter->font().pointSize()/2.0 + 25.0,  label2);
}
