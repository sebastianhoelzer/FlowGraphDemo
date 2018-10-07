#ifndef PORT_H
#define PORT_H

#include <QGraphicsItem>
#include "wire.h"

class Wire;

class Port : public QGraphicsItem
{

public:
    enum
    {
        InputPortType = UserType + 1,
        OutputPortType = UserType + 2
    };
    Port(float x, float y, float width, float height, QGraphicsItem *parent);

//    Port(QGraphicsItem *parent);

    int type() const;
    Wire *wire() const;
    void setWire(Wire *value);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    bool isInput() const;
    void setIsInput(bool isInput);

    void triggerParentToRecalculate();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);


private:
    double m_width;
    double m_height;
    bool m_isInput;
    Wire *m_wire;
};

#endif // PORT_H
