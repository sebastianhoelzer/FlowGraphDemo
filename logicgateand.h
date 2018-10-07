#ifndef ANDLOGICGATE_H
#define ANDLOGICGATE_H

#include <QGraphicsItem>

#include "port.h"
#include "basenode.h"

class AndLogicGate : public BaseNode
{
public:
    AndLogicGate(float x = 0.0, float y = 0.0);
    ~AndLogicGate();

    // EventDrivenNode interface
    virtual void recalculateValue(Port *sourcePort) override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
private:
    Port *m_inputPort1;
    Port *m_inputPort2;
    Port *m_outputPort;
};

#endif // ANDLOGICGATE_H
