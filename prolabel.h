#ifndef PROLABEL_H
#define PROLABEL_H

//#include "qrect.h"
#include <QLabel>
#include <QMenu>

class ProLabel : public QLabel
{
    Q_OBJECT

public:
    ProLabel(QWidget *parent = 0);
    ~ProLabel();
    QRect getQImageRect(float widthFactor, float heightFactor);

protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private:
    bool selectionStarted;
    QRect selectionRect;
    QMenu contextMenu;

private slots:
    void saveSlot();

};

#endif // PROLABEL_H
