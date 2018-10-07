#include "flowgraphwidget.h"
#include <QLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>

//#include "node.h"
#include "port.h"
#include "customgraphicsscene.h"

FlowGraphWidget::FlowGraphWidget(QWidget *parent) :
    QWidget(parent),
    m_graphicsView(new QGraphicsView(this)),
    m_scene(new CustomGraphicsScene(this)),
    m_layout(new QHBoxLayout(this))
{
    m_scene->setSceneRect(QRect(0, 0, m_graphicsView->rect().width(), m_graphicsView->rect().height()));
    m_graphicsView->setScene(m_scene);
    m_graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    m_graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    m_layout->addWidget(m_graphicsView);
    this->setLayout(m_layout);
}
