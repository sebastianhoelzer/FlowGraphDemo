#ifndef XORLOGICGATE_H
#define XORLOGICGATE_H

#include <QGraphicsItem>

#include "port.h"
#include "basenode.h"

class XorLogicGate : public BaseNode
{
public:
    XorLogicGate(float x = 0.0, float y = 0.0);
    ~XorLogicGate();

    // EventDrivenNode interface
    virtual void recalculateValue(Port *sourcePort) override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
private:
    Port *m_inputPort1;
    Port *m_inputPort2;
    Port *m_outputPort;
};

#endif // XORLOGICGATE_H
