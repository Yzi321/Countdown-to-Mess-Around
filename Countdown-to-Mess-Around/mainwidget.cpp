// mainwidget.cpp
#include "mainwidget.h"
#include <QPainter>
#include <QMenu>
#include <QAction>
#include <QInputDialog>
#include <QDesktopWidget>
#include <QApplication>
#include <QCloseEvent>
#include <QTimer>
#include "countdownlabel.h"
#include "settingsdialog.h"
#include "_global.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent), offset(QPoint())
{
    loadSettings(_Global::displaySetting);

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground);

    // ���ô��ڴ�СΪ50x50����
    int width = 70;
    int height = 70;

    setFixedSize(width, height);


    countdownLabel = new CountdownLabel(this);
    countdownLabel->setGeometry(0, 0, width, height); // ���ñ�ǩ��λ�úʹ�С
    countdownLabel->setStyleSheet("background-color: transparent; color: transparent;"
                                  "border:none;"); // ���ñ�ǩ����ʽ



    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setVisible(true);
    trayIcon->setIcon(QIcon(":/my/icon.ico"));

    connect(trayIcon, &QSystemTrayIcon::activated, [this](QSystemTrayIcon::ActivationReason reason) {
        if (reason == QSystemTrayIcon::Trigger) {
            // ��������ͼ��Ĳ���
        } else if (reason == QSystemTrayIcon::MiddleClick) {
            // �м���������ͼ��Ĳ���
        } else if (reason == QSystemTrayIcon::Context) {
            // �Ҽ���������ͼ��Ĳ���
            show();
        }
    });

    QMenu *trayMenu = new QMenu(this);
    QAction *setTimerAction = new QAction(u8"����", this);
    QAction *aboutAction = new QAction(u8"����", this);
    QAction *exitAction = new QAction(u8"�˳�", this);

    connect(setTimerAction, &QAction::triggered, this, &MainWidget::onSetTimer);
    connect(aboutAction, &QAction::triggered, this, &MainWidget::onAbout);
    connect(exitAction, &QAction::triggered, this, &MainWidget::onExit);

    trayMenu->addAction(setTimerAction);
    trayMenu->addAction(aboutAction);
    trayMenu->addSeparator();
    trayMenu->addAction(exitAction);

    trayIcon->setContextMenu(trayMenu);
    trayIcon->show();

    countdownLabel->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(countdownLabel, &CountdownLabel::customContextMenuRequested,
            countdownLabel, [&](const QPoint &pos){
    QMenu labelContextMenu(this);
    QAction *setLabelAction = new QAction(u8"����", this);
    QAction *aboutLabelAction = new QAction(u8"����", this);
    QAction *exitLabelAction = new QAction(u8"�˳�", this);

    connect(setLabelAction, &QAction::triggered, this, &MainWidget::onSetTimer);
    connect(aboutLabelAction, &QAction::triggered, this, &MainWidget::onAbout);
    connect(exitLabelAction, &QAction::triggered, this, &MainWidget::onExit);

    labelContextMenu.addAction(setLabelAction);
    labelContextMenu.addAction(aboutLabelAction);
    labelContextMenu.addSeparator();
    labelContextMenu.addAction(exitLabelAction);

    labelContextMenu.exec(mapToGlobal(pos));

    });


}

MainWidget::~MainWidget()
{
}

void MainWidget::onSetTimer()
{
    SettingsDialog dialog;
    if (dialog.exec() == QDialog::Accepted) {
        // �û������ȷ����ť
    }
}



void MainWidget::onAbout()
{
    // ��ʾ������Ϣ
}

void MainWidget::onExit()
{
    // �˳�Ӧ�ó���
    qApp->quit();
}


void MainWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        // ������갴���¼���֧���϶�
        offset = event->pos();
    }
}

void MainWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        // �϶�����
        QPoint newPos = mapToGlobal(event->pos() - offset);
        move(newPos);
    }
}
