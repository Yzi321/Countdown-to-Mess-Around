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
    setWindowTitle("����");
    // �����ؼ�
    QLabel *workDurationLabel = new QLabel("����ʱ�������ӣ���");
    QComboBox *workDurationComboBox = new QComboBox;
    workDurationComboBox->addItems({"10", "20", "30", "40", "50", "60", "70", "80", "90", "99"});

    QLabel *breakDurationLabel = new QLabel("��Ϣʱ�������ӣ���");
    QComboBox *breakDurationComboBox = new QComboBox;
    breakDurationComboBox->addItems({"2", "3", "5", "8", "10", "15", "20", "30"});

    QLabel *backgroundOpacityLabel = new QLabel("����͸���ȣ�");
    QSpinBox *backgroundOpacitySpinBox = new QSpinBox;
    backgroundOpacitySpinBox->setRange(0, 255);

    QLabel *fontBackgroundOpacityLabel = new QLabel("���屳��͸���ȣ�");
    QSpinBox *fontBackgroundOpacitySpinBox = new QSpinBox;
    fontBackgroundOpacitySpinBox->setRange(0, 255);

    QLabel *workBackgroundColorLabel = new QLabel("����״̬����ɫ��");
    QLabel *workBackgroundColorButton = new QLabel();

    QLabel *breakBackgroundColorLabel = new QLabel("��Ϣ״̬����ɫ��");
    QLabel *breakBackgroundColorButton = new QLabel();

    QLabel *fontColorLabel = new QLabel("������ɫ��");
    QLabel *fontColorButton = new QLabel();

    // ��������
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
    QPushButton *okButton = new QPushButton("ȷ��");
    QPushButton *cancelButton = new QPushButton("ȡ��");
    QPushButton *applyButton = new QPushButton("Ӧ��");
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(applyButton);
    layout->addLayout(buttonLayout);

    // ���Ӱ�ť�źŲ�
    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    connect(applyButton, &QPushButton::clicked, this, &SettingsDialog::applySettings);

    // �洢�ؼ�ָ���Թ��Ժ�ʹ��
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
    QColor color = QColorDialog::getColor(Qt::white, this, "ѡ����ɫ");
    if (color.isValid()) {
        label->setStyleSheet(QString("background-color: %1;").arg(color.name()));
    }
}


// ��дQLabel��������¼�
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
    // ������Ӧ���û�������
    QString workDuration = workDurationComboBoxPtr->currentText();
    QString breakDuration = breakDurationComboBoxPtr->currentText();
    int backgroundOpacity = backgroundOpacitySpinBoxPtr->value();
    int fontBackgroundOpacity = fontBackgroundOpacitySpinBoxPtr->value();

    QString workBackgroundColor = workBackgroundColorLabelPtr->styleSheet();
    QString breakBackgroundColor = breakBackgroundColorLabelPtr->styleSheet();
    QString fontColor = fontColorLabelPtr->styleSheet();

    // �����ﴦ�����ã����Խ���Щ���ñ��浽�����ļ��������ط�
}
