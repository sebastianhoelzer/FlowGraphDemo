#ifndef LOGICGATELED_H
#define LOGICGATELED_H

#include <QGraphicsItem>

#include "port.h"
#include "basenode.h"

class LogicGateLed : public BaseNode
{
public:
    LogicGateLed(float x = 0.0, float y = 0.0);
    ~LogicGateLed();

    // EventDrivenNode interface
    virtual void recalculateValue(Port *sourcePort) override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
private:
    bool m_inputValue;
    QRectF m_ledArea;
    Port *m_inputPort;
};

#endif // LOGICGATELED_H
