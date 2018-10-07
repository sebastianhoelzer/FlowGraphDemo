#include "wire.h"

#include <QGraphicsPathItem>
#include <QPen>
#include <Qt>
#include <QDebug>
#include <QtMath>
#include <QTimeLine>

#include "port.h"
#include "basenode.h"

Wire::Wire(QGraphicsItem *parent) : QGraphicsPathItem(parent),
    m_startPosition(QPointF()),
    m_endPostion(QPointF()),
    m_value(false),
    m_endPort(nullptr)
{
    setPen(QPen(Qt::black, 2));
    setBrush(Qt::NoBrush);
    setZValue(-1);
}

void Wire::setEndPosition(QPointF point)
{
    m_endPostion = point;
}

void Wire::updatePath()
{
    QPainterPath p;

    p.moveTo(m_startPosition);

    qreal dx = m_endPostion.x() - m_startPosition.x();
    qreal dy = m_endPostion.y() - m_startPosition.y();

    QPointF controlPoint1(m_startPosition.x() + qFabs(dx * 0.5), (dx > 0) ? (m_startPosition.y() + dy * 0.1) : (m_startPosition.y() + dy * 0.5));
    QPointF controlPoint2(m_endPostion.x() - qFabs(dx * 0.5), (dx > 0) ? (m_startPosition.y() + dy * 0.9) : (m_startPosition.y() + dy * 0.5));

    p.cubicTo(controlPoint1, controlPoint2, m_endPostion);

    setPath(p);
}

void Wire::moveStartPositionBy(QPointF vector)
{
    m_startPosition = vector;
}

void Wire::moveEndPositionBy(QPointF vector)
{
    m_endPostion = vector;
    updatePath();
}

bool Wire::value() const
{
    return m_value;
}

void Wire::setValue(bool value)
{
    m_value = value;
    setPen(m_value?QPen(Qt::black, 4):QPen(Qt::black, 2));
    if(m_endPort)
    {
//        m_endPort->recalculateValue();
        m_endPort->triggerParentToRecalculate();
    }
    update();
}

void Wire::setEndPort(Port *endPort)
{
    m_endPort = endPort;
}


void Wire::setStartPosition(QPointF point)
{
    m_startPosition = point;
}
