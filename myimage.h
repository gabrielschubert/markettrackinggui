#ifndef MYIMAGE_H
#define MYIMAGE_H

#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QSize>
#include <QColor>
#include <QMouseEvent>
#include <QDebug>

class Myimage : public QWidget
{
    Q_OBJECT
public:
    explicit Myimage(QWidget *parent = nullptr);

private:
    QPoint mPoint;

signals:

public slots:
    void paintEvent(QPaintEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
};

#endif // MYIMAGE_H
