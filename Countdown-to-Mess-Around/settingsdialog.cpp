#include "settingsdialog.h"
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QColorDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QApplication>
#include <QMouseEvent>
#include "_global.h"

#pragma execution_character_set("utf-8")

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("设置");
    // 创建控件
    QLabel *workDurationLabel = new QLabel("工作时长（分钟）：");
    QComboBox *workDurationComboBox = new QComboBox;
    workDurationComboBox->addItems({"10", "20", "30", "40", "50", "60", "70", "80", "90", "99"});

    QLabel *breakDurationLabel = new QLabel("休息时长（分钟）：");
    QComboBox *breakDurationComboBox = new QComboBox;
    breakDurationComboBox->addItems({"2", "3", "5", "8", "10", "15", "20", "30"});

    QLabel *backgroundOpacityLabel = new QLabel("背景透明度：");
    QSpinBox *backgroundOpacitySpinBox = new QSpinBox;
    backgroundOpacitySpinBox->setRange(0, 255);

    QLabel *fontBackgroundOpacityLabel = new QLabel("字体背景透明度：");
    QSpinBox *fontBackgroundOpacitySpinBox = new QSpinBox;
    fontBackgroundOpacitySpinBox->setRange(0, 255);

    QLabel *workBackgroundColorLabel = new QLabel("工作状态背景色：");
    QLabel *workBackgroundColorButton = new QLabel();

    QLabel *breakBackgroundColorLabel = new QLabel("休息状态背景色：");
    QLabel *breakBackgroundColorButton = new QLabel();

    QLabel *fontColorLabel = new QLabel("字体颜色：");
    QLabel *fontColorButton = new QLabel();

    // 创建布局
    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addWidget(workDurationLabel);
    layout->addWidget(workDurationComboBox);
    layout->addWidget(breakDurationLabel);
    layout->addWidget(breakDurationComboBox);
    layout->addWidget(backgroundOpacityLabel);
    layout->addWidget(backgroundOpacitySpinBox);
    layout->addWidget(fontBackgroundOpacityLabel);
    layout->addWidget(fontBackgroundOpacitySpinBox);
    layout->addWidget(workBackgroundColorLabel);
    layout->addWidget(workBackgroundColorButton);
    layout->addWidget(breakBackgroundColorLabel);
    layout->addWidget(breakBackgroundColorButton);
    layout->addWidget(fontColorLabel);
    layout->addWidget(fontColorButton);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    QPushButton *okButton = new QPushButton("确定");
    QPushButton *cancelButton = new QPushButton("取消");
    QPushButton *applyButton = new QPushButton("应用");
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(applyButton);
    layout->addLayout(buttonLayout);

    // 连接按钮信号槽
    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    connect(applyButton, &QPushButton::clicked, this, &SettingsDialog::applySettings);

    // 存储控件指针以供以后使用
    workDurationComboBoxPtr = workDurationComboBox;
    breakDurationComboBoxPtr = breakDurationComboBox;
    backgroundOpacitySpinBoxPtr = backgroundOpacitySpinBox;
    fontBackgroundOpacitySpinBoxPtr = fontBackgroundOpacitySpinBox;
    workBackgroundColorLabelPtr = workBackgroundColorButton;
    breakBackgroundColorLabelPtr = breakBackgroundColorButton;
    fontColorLabelPtr = fontColorButton;
}

void SettingsDialog::chooseColor(QLabel *label)
{
    QColor color = QColorDialog::getColor(Qt::white, this, "选择颜色");
    if (color.isValid()) {
        label->setStyleSheet(QString("background-color: %1;").arg(color.name()));
    }
}


// 重写QLabel的鼠标点击事件
void SettingsDialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        QLabel *label = qobject_cast<QLabel*>(sender());
        if (label) {
            chooseColor(label);
        }
    }
}

void SettingsDialog::applySettings()
{
    // 在这里应用用户的设置
    QString workDuration = workDurationComboBoxPtr->currentText();
    QString breakDuration = breakDurationComboBoxPtr->currentText();
    int backgroundOpacity = backgroundOpacitySpinBoxPtr->value();
    int fontBackgroundOpacity = fontBackgroundOpacitySpinBoxPtr->value();

    QString workBackgroundColor = workBackgroundColorLabelPtr->styleSheet();
    QString breakBackgroundColor = breakBackgroundColorLabelPtr->styleSheet();
    QString fontColor = fontColorLabelPtr->styleSheet();

    // 在这里处理设置，可以将这些设置保存到配置文件或其他地方
}
