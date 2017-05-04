
#include <clickablelabel.h>
#include <QDialog>

ClickableLabel::ClickableLabel(QWidget* parent)
    : QLabel(parent)
{

}

ClickableLabel::~ClickableLabel()
{

}

void ClickableLabel::mousePressEvent(QMouseEvent * event)
{
    MyLabelPressed = 1;
    QLabel::mouseReleaseEvent(event);
}

void ClickableLabel::mouseReleaseEvent(QMouseEvent* event)
{
    if ( MyLabelPressed)
    {
        emit clicked();
        MyLabelPressed = 0;
    }
    QLabel::mouseReleaseEvent(event);
}
