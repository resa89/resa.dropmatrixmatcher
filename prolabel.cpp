#include "prolabel.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QAction>
#include <QFileDialog>

ProLabel::ProLabel(QWidget *parent)
    : QLabel(parent)
{
    selectionStarted=false;

    QAction *saveAction=contextMenu.addAction("Save");

    connect(saveAction,SIGNAL(triggered()),this,SLOT(saveSlot()));
}

ProLabel::~ProLabel()
{

}

void ProLabel::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QLabel::paintEvent(e);
    painter.setPen(QPen(QBrush(QColor(0,0,0,180)),1,Qt::DashLine));
    painter.setBrush(QBrush(QColor(255,255,255,120)));

    painter.drawRect(selectionRect);
}

void ProLabel::mousePressEvent(QMouseEvent *e)
{
    if (e->button()==Qt::RightButton)
    {
        if (selectionRect.contains(e->pos())) contextMenu.exec(this->mapToGlobal(e->pos()));
    }
    else
    {
    selectionStarted=true;
    selectionRect.setTopLeft(e->pos());
    selectionRect.setBottomRight(e->pos());
    }

}

void ProLabel::mouseMoveEvent(QMouseEvent *e)
{
    if (selectionStarted)
    {
        selectionRect.setBottomRight(e->pos());
        repaint();
    }
}

void ProLabel::mouseReleaseEvent(QMouseEvent *e)
{
    selectionStarted=false;
}

void ProLabel::saveSlot()
{
    QString fileName = QFileDialog::getSaveFileName(this, QObject::tr("Save File"),
                                                    "/home",
                                                    QObject::tr("Images (*.jpg)"));
    this->pixmap()->copy(selectionRect).save(fileName);
}

QRect ProLabel::getQImageRect(float widthFactor, float heightFactor)
{
    QRect qimageSizedRect;
    int x = (float)selectionRect.x() * widthFactor;
    int y = (float)selectionRect.y() * heightFactor;
    int w = (float)selectionRect.width() * widthFactor;
    int h = (float)selectionRect.height() * heightFactor;

    qimageSizedRect.setX(x);
    qimageSizedRect.setY(y);
    qimageSizedRect.setWidth(w);
    qimageSizedRect.setHeight(h);

    return qimageSizedRect;
}
