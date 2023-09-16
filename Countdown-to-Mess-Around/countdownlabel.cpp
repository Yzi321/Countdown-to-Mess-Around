#include "countdownlabel.h"
#include "_global.h"

#include <QPainter>
#include <QFont>
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>


CountdownLabel::CountdownLabel(QWidget *parent)
    : QLabel(parent)// 初始倒计时时间为30分钟
{
    this->setStyleSheet("border-radius:3px;border:10px solid black;");
    // 创建一个定时器，每隔一分钟触发一次
    timer_work = new QTimer(this);
    connect(timer_work, &QTimer::timeout, this, &CountdownLabel::updateTimerDisplay);
    timer_work->start(60000); // 每隔一分钟（60,000毫秒）触发一次

    timer_rest = new QTimer(this);
    connect(timer_rest, &QTimer::timeout, this, &CountdownLabel::updateTimerDisplay);
    timer_rest->start(60000); // 每隔一分钟（60,000毫秒）触发一次


}

void CountdownLabel::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.fillRect(rect(), _Global::displaySetting.background_work); // 设置矩形的背景颜色


    QString countdownText = QString::number(_Global::displaySetting.countdown_work);

    painter.setPen(_Global::displaySetting.font_color);
    painter.setFont(QFont("Arial", 33));
    painter.drawText(this->rect(), Qt::AlignCenter, countdownText);

    // 绘制带有圆角的矩形
    int radius = 10; // 圆角半径
    QRegion region;
    painter.setRenderHint(QPainter::Antialiasing, true); // 启用抗锯齿
    QPainterPath path;
    path.addRoundedRect(QRectF(QPointF(0, 0), size()), radius, radius);
    region = QRegion(path.toFillPolygon().toPolygon());
    setMask(region);
}


void CountdownLabel::updateTimerDisplay()
{
    if(timer_work->isActive())
        _Global::displaySetting.countdown_work--;
    if(timer_rest->isActive())
        _Global::displaySetting.countdown_rest--;

    update();
}
