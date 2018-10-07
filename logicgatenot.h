#ifndef LOGICGATENOT_H
#define LOGICGATENOT_H

#include <QGraphicsItem>

#include "port.h"
#include "basenode.h"

class LogicGateNot : public BaseNode
{
public:
    LogicGateNot(float x = 0.0, float y = 0.0);
    ~LogicGateNot();

    // EventDrivenNode interface
    virtual void recalculateValue(Port *sourcePort) override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
private:
    Port *m_inputPort;
    Port *m_outputPort;
};

#endif // LOGICGATENOT_H
