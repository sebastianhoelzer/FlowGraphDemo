#include "basenode.h"

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include "port.h"

BaseNode::BaseNode()
{
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable, true);
}

BaseNode::~BaseNode()
{
}

void BaseNode::removeWires()
{
    foreach (QGraphicsItem *myItem, this->childItems())
    {
        if ((myItem->type() == Port::InputPortType) or (myItem->type() == Port::OutputPortType))
        {
            Port *myPort = (Port*)myItem;
            if(myPort->wire())
            {
                this->scene()->removeItem(myPort->wire());
            }
        }
    }
}

void BaseNode::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //provide right click context menu
    if(event->button() == Qt::RightButton)
    {
        QPoint globalPos = event->screenPos();
        QMenu myMenu;
        myMenu.addAction("Delete");

        QAction* selectedItem = myMenu.exec(globalPos);
        if (selectedItem)
        {
            if (QString::compare( selectedItem->text(), "Delete") == 0)
            {
                removeWires();
                QGraphicsScene *myScene = scene();
                myScene->removeItem(this);
            }
        }
    }
}

QRectF BaseNode::boundingRect() const
{
    return QRectF(- m_width / 2, - m_height / 2, m_width, m_height);
}
