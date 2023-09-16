#include "countdownlabel.h"
#include "_global.h"

#include <QPainter>
#include <QFont>
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>


CountdownLabel::CountdownLabel(QWidget *parent)
    : QLabel(parent)// ��ʼ����ʱʱ��Ϊ30����
{
    this->setStyleSheet("border-radius:3px;border:10px solid black;");
    // ����һ����ʱ����ÿ��һ���Ӵ���һ��
    timer_work = new QTimer(this);
    connect(timer_work, &QTimer::timeout, this, &CountdownLabel::updateTimerDisplay);
    timer_work->start(60000); // ÿ��һ���ӣ�60,000���룩����һ��

    timer_rest = new QTimer(this);
    connect(timer_rest, &QTimer::timeout, this, &CountdownLabel::updateTimerDisplay);
    timer_rest->start(60000); // ÿ��һ���ӣ�60,000���룩����һ��


}

void CountdownLabel::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.fillRect(rect(), _Global::displaySetting.background_work); // ���þ��εı�����ɫ


    QString countdownText = QString::number(_Global::displaySetting.countdown_work);

    painter.setPen(_Global::displaySetting.font_color);
    painter.setFont(QFont("Arial", 33));
    painter.drawText(this->rect(), Qt::AlignCenter, countdownText);

    // ���ƴ���Բ�ǵľ���
    int radius = 10; // Բ�ǰ뾶
    QRegion region;
    painter.setRenderHint(QPainter::Antialiasing, true); // ���ÿ����
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
