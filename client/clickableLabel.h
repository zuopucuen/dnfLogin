#include <QWidget>
#include <QLabel>
#include <QMouseEvent>

class ClickableLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ClickableLabel(QWidget* parent=0 );
    ~ClickableLabel();
signals:
    void clicked();
protected:
    int MyLabelPressed;

    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);

public slots:

};
