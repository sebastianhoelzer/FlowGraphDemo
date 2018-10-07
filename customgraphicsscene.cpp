#include "customgraphicsscene.h"

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QGraphicsSceneWheelEvent>
#include <QGraphicsView>
#include <QMenu>
#include <QtMath>

//#include "node.h"
#include "port.h"
#include "wire.h"
#include "flowgraphwidget.h"
#include "switch.h"
#include "basenode.h"
#include "logicgateand.h"
#include "logicgateor.h"
#include "logicgatexor.h"
#include "logicgateflipflop.h"
#include "logicgatenot.h"
#include "logicgateled.h"

CustomGraphicsScene::CustomGraphicsScene(QWidget *parent = nullptr):
    QGraphicsScene(parent),
    m_pullingWireInProgress(false),
    m_selection(nullptr)
{

}

void CustomGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);
    if(!event->isAccepted()) {
        if(event->button() == Qt::LeftButton) {
            QGraphicsItem *item = itemAt(event->scenePos());

            if(item && (item->type() == Port::OutputPortType))
            {
                m_start = (Port*)item;
                if (m_start->wire())
                {
                    removeItem(m_start->wire());
                    m_start->setWire(nullptr);
                }
                m_previewWire = new Wire();
                m_previewWire->setStartPosition(m_start->scenePos());
                addItem(m_previewWire);
                m_pullingWireInProgress = true;
            }

            if (item == nullptr)
            {
                m_selection = new QGraphicsRectItem();
                m_selection->setRect(event->scenePos().x(), event->scenePos().y(), 0.0, 0.0);
                this->addItem(m_selection);

                m_selectionInProgress = true;
                m_selectionStartingPoint = QPoint(event->scenePos().x(), event->scenePos().y());
            }


        } else if(event->button() == Qt::RightButton) {

            QPoint globalPos = event->screenPos();

            QMenu myMenu;
            myMenu.addAction("Switch");
            myMenu.addSeparator();
            myMenu.addAction("And");
            myMenu.addAction("OR");
            myMenu.addAction("XOR");
            myMenu.addAction("NOT");
            myMenu.addSeparator();
            myMenu.addAction("Flip Flop");
            myMenu.addSeparator();
            myMenu.addAction("LED");

            QAction* selectedItem = myMenu.exec(globalPos);
            if (selectedItem)
            {
                if (QString::compare( selectedItem->text(), "Switch") == 0)
                {
                    Switch *node = new Switch(event->scenePos().x(), event->scenePos().y());
                    this->addItem(node);
                }
                else if (QString::compare( selectedItem->text(), "And") == 0)
                {
                    AndLogicGate *node = new AndLogicGate(event->scenePos().x(), event->scenePos().y());
                    this->addItem(node);
                }
                else if (QString::compare( selectedItem->text(), "OR") == 0)
                {
                    OrLogicGate *node = new OrLogicGate(event->scenePos().x(), event->scenePos().y());
                    this->addItem(node);
                }
                else if (QString::compare( selectedItem->text(), "XOR") == 0)
                {
                    XorLogicGate *node = new XorLogicGate(event->scenePos().x(), event->scenePos().y());
                    this->addItem(node);
                }
                else if (QString::compare( selectedItem->text(), "Flip Flop") == 0)
                {
                    LogicGateFlipFlop *node = new LogicGateFlipFlop(event->scenePos().x(), event->scenePos().y());
                    this->addItem(node);
                }
                else if (QString::compare( selectedItem->text(), "NOT") == 0)
                {
                    LogicGateNot *node = new LogicGateNot(event->scenePos().x(), event->scenePos().y());
                    this->addItem(node);
                }
                else if (QString::compare( selectedItem->text(), "LED") == 0)
                {
                    LogicGateLed *node = new LogicGateLed(event->scenePos().x(), event->scenePos().y());
                    this->addItem(node);
                }
            }
            else
            {
                // nothing was chosen
            }


        }
    }
}

void CustomGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseReleaseEvent(event);
    QGraphicsItem *item = itemAt(event->scenePos());
    if(item && (item->type() == Port::InputPortType) && m_pullingWireInProgress)
    {
        // complete the wire
        m_end = (Port*)item;

        if (m_end->wire())
        {
            removeItem(m_end->wire());
        }

        m_previewWire->setEndPosition(m_end->scenePos());
        m_previewWire->updatePath();

        m_previewWire->setEndPort(m_end);

        m_end->setWire(m_previewWire);
        m_start->setWire(m_previewWire);
    }

    else
    {
        // mouse not released on a port
        // cancel pulling wire
        if (m_pullingWireInProgress && m_previewWire)
        {
           removeItem(m_previewWire);
           m_previewWire = nullptr;
        }

        // finish rubber band selection
        if (m_selectionInProgress && m_selection)
        {
            QPainterPath selectionArea;
            selectionArea.addRect(m_selection->rect());
            setSelectionArea(selectionArea);
            removeItem(m_selection);
            m_selection = nullptr;
        }

    }
    m_selectionInProgress = false;
    m_pullingWireInProgress = false;
}



void CustomGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);

    // pulling wire
    if (m_pullingWireInProgress)
    {
        m_previewWire->setEndPosition(event->scenePos());
        m_previewWire->updatePath();
    }

    // rubberband selection
    if (m_selectionInProgress)
    {
        qreal width = qAbs(event->scenePos().x() - m_selectionStartingPoint.x());
        qreal height = qAbs(event->scenePos().y() - m_selectionStartingPoint.y());

        qreal upperLeftX = qMin(m_selectionStartingPoint.x(), event->scenePos().x());
        qreal upperLeftY = qMin(m_selectionStartingPoint.y(), event->scenePos().y());

        if (m_selection)
        {
            m_selection->setRect(upperLeftX, upperLeftY, width, height);
        }
    }
}

QGraphicsItem *CustomGraphicsScene::itemAt(const QPointF &pos)
{
    QList<QGraphicsItem*> items = this->items(QRectF(pos - QPointF(1,1), QSize(3,3)));

    foreach(QGraphicsItem *item, items)
        if (item->type() > QGraphicsItem::UserType)
            return item;

    return 0;
}
