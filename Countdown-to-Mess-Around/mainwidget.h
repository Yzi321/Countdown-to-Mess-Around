#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QSystemTrayIcon>
#include <QWidget>

#include "countdownlabel.h"

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private:
    QSystemTrayIcon *trayIcon;
    QPoint offset;

private:
    CountdownLabel *countdownLabel; // µπº∆ ±±Í«©

private slots:
    void onSetTimer();
    void onAbout();
    void onExit();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // MAINWIDGET_H
