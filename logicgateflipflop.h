#ifndef LOGICGATEFLIPFLOP_H
#define LOGICGATEFLIPFLOP_H

#include <QGraphicsItem>

#include "port.h"
#include "basenode.h"

class LogicGateFlipFlop : public BaseNode
{
public:
    LogicGateFlipFlop(float x = 0.0, float y = 0.0);
    ~LogicGateFlipFlop();

    // EventDrivenNode interface
    virtual void recalculateValue(Port* sourcePort) override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
private:
    bool m_outputValue;
    bool m_previousClockInput;
    Port *m_inputPort1;
    Port *m_inputPort2;
    Port *m_outputPort;
};

#endif // LOGICGATEFLIPFLOP_H
