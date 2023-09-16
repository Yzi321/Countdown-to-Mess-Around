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

    // 设置窗口大小为50x50像素
    int width = 70;
    int height = 70;

    setFixedSize(width, height);


    countdownLabel = new CountdownLabel(this);
    countdownLabel->setGeometry(0, 0, width, height); // 设置标签的位置和大小
    countdownLabel->setStyleSheet("background-color: transparent; color: transparent;"
                                  "border:none;"); // 设置标签的样式



    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setVisible(true);
    trayIcon->setIcon(QIcon(":/my/icon.ico"));

    connect(trayIcon, &QSystemTrayIcon::activated, [this](QSystemTrayIcon::ActivationReason reason) {
        if (reason == QSystemTrayIcon::Trigger) {
            // 单击托盘图标的操作
        } else if (reason == QSystemTrayIcon::MiddleClick) {
            // 中键单击托盘图标的操作
        } else if (reason == QSystemTrayIcon::Context) {
            // 右键单击托盘图标的操作
            show();
        }
    });

    QMenu *trayMenu = new QMenu(this);
    QAction *setTimerAction = new QAction(u8"设置", this);
    QAction *aboutAction = new QAction(u8"关于", this);
    QAction *exitAction = new QAction(u8"退出", this);

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
    QAction *setLabelAction = new QAction(u8"设置", this);
    QAction *aboutLabelAction = new QAction(u8"关于", this);
    QAction *exitLabelAction = new QAction(u8"退出", this);

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
        // 用户点击了确定按钮
    }
}



void MainWidget::onAbout()
{
    // 显示关于信息
}

void MainWidget::onExit()
{
    // 退出应用程序
    qApp->quit();
}


void MainWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        // 捕获鼠标按下事件以支持拖动
        offset = event->pos();
    }
}

void MainWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        // 拖动窗口
        QPoint newPos = mapToGlobal(event->pos() - offset);
        move(newPos);
    }
}
