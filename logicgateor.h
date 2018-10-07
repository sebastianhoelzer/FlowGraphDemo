#ifndef ORLOGICGATE_H
#define ORLOGICGATE_H

#include <QGraphicsItem>

#include "port.h"
#include "basenode.h"

class OrLogicGate : public BaseNode
{
public:
    OrLogicGate(float x = 0.0, float y = 0.0);
    ~OrLogicGate();

    // EventDrivenNode interface
    virtual void recalculateValue(Port *sourcePort) override;
//        void removeWires();

    // QGraphicsItem interface
//    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
//    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
//    float m_width;
//    float m_height;
    Port *m_inputPort1;
    Port *m_inputPort2;
    Port *m_outputPort;
};

#endif // ORLOGICGATE_H
