#ifndef FLOWGRAPHWIDGET_H
#define FLOWGRAPHWIDGET_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QLayout>

#include "customgraphicsscene.h"

class FlowGraphWidget : public QWidget
{
public:
    FlowGraphWidget(QWidget *parent = nullptr);
    
private:
    QGraphicsView *m_graphicsView;
    CustomGraphicsScene *m_scene;
    QHBoxLayout *m_layout;
};

#endif // FLOWGRAPHWIDGET_H
