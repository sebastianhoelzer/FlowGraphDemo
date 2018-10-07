#ifndef SWITCH_H
#define SWITCH_H

#include <QGraphicsItem>
#include <QRectF>
#include <QDebug>
#include <QMouseEvent>

#include "port.h"
#include "wire.h"
#include "basenode.h"

class Switch : public BaseNode
{
public:
    explicit Switch(float x = 0.0, float y = 0.0);

    void removeWires();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    Port *m_outputPort;
//    float m_width;
//    float m_height;
    bool m_inputValue;
    QRectF switchArea;
};

#endif // SWITCH_H
