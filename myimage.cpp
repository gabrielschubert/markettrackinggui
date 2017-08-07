#include "myimage.h"

Myimage::Myimage(QWidget *parent) : QWidget(parent)
{
    setMouseTracking(true); // E.g. set in your constructor of your widget.

}
void Myimage::mouseMoveEvent(QMouseEvent *event)
{
    mPoint = event->pos();
    update();
}

void Myimage::paintEvent(QPaintEvent * event)
{

    event->accept();
    QPixmap pixmap(":/Images/Store_top_view.jpg");

    QRect rectangle(0, 0, width()-1, height()-1);

    QPainter painter(this);
    painter.drawRect(rectangle);

    float comprimento = 1.0*width()/pixmap.width();
    float altura = 1.0*height()/pixmap.height();
    float ratio = 0.;

    if (comprimento<=altura)
        ratio = comprimento;
    else
        ratio = altura;

    QSize size = ratio*pixmap.size();
    size.setHeight(size.height()-10);

    QPoint p;
    p.setX(0 + (width()-size.width())/2);
    p.setY(5);

    painter.drawPixmap(QRect(p, size), pixmap.scaled(size, Qt::KeepAspectRatio));
    painter.setPen(QPen(Qt::red, 10, Qt::SolidLine));

    if(!mPoint.isNull()){
        //qDebug() << mPoint;
        painter.drawEllipse(mPoint, 10 ,10 );
    }

}
