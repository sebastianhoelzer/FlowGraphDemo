#ifndef CUSTOMGRAPHICSSCENE_H
#define CUSTOMGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QPointF>

#include "wire.h"
#include "port.h"

class CustomGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit CustomGraphicsScene(QWidget *parent);


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
private:
    QGraphicsItem *itemAt(const QPointF& pos);

    bool m_pullingWireInProgress;
    Port *m_start;
    Port *m_end;
    Wire *m_previewWire;
    QGraphicsRectItem *m_selection;
    bool m_selectionInProgress;
    QPointF m_selectionStartingPoint;
};

#endif // CUSTOMGRAPHICSSCENE_H
