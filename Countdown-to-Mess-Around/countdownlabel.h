#ifndef COUNTDOWNLABEL_H
#define COUNTDOWNLABEL_H

#include <QLabel>
#include <QMenu>
#include <QTimer>
class CountdownLabel : public QLabel
{
    Q_OBJECT

public:
    CountdownLabel(QWidget *parent = nullptr);

public slots:
    void updateTimerDisplay();
protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QTimer* timer_work;
    QTimer* timer_rest;
    QMenu *labelContextMenu;

};


#endif // COUNTDOWNLABEL_H
