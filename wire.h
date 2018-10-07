#ifndef WIRE_H
#define WIRE_H

#include <QGraphicsPathItem>
#include <QGraphicsItem>
#include <QPointF>
#include "basenode.h"
class Port;

class Wire : public QGraphicsPathItem
{
public:
    Wire(QGraphicsItem *parent = 0);
    void setStartPosition(QPointF point);
    void setEndPosition(QPointF point);
    void updatePath();

    void moveStartPositionBy(QPointF vector);
    void moveEndPositionBy(QPointF vector);

    bool value() const;
    void setValue(bool value);

    void setEndPort(Port *endPort);

private:
    QPointF m_startPosition;
    QPointF m_endPostion;
    bool m_value;
    Port *m_endPort;
};

#endif // WIRE_H
