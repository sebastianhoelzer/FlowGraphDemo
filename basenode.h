#ifndef EVENTDRIVENNODE_H
#define EVENTDRIVENNODE_H

#include <QDebug>
#include <QGraphicsItem>

#include "port.h"
class Port;

class BaseNode : public QGraphicsItem
{
public:
    BaseNode();
    ~BaseNode();

   void removeWires();
   void mousePressEvent(QGraphicsSceneMouseEvent *event);
   virtual void recalculateValue(Port*) {}
   QRectF boundingRect() const override;
//private:
    float m_width;
    float m_height;
};


#endif // EVENTDRIVENNODE_H
