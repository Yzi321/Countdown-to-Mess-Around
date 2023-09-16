#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QComboBox>
#include <QDialog>
#include <QLabel>
#include <QSpinBox>

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    SettingsDialog(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event);

private slots:
    void chooseColor(QLabel *label);
    void applySettings();

private:
    QComboBox *workDurationComboBoxPtr;
    QComboBox *breakDurationComboBoxPtr;
    QSpinBox *backgroundOpacitySpinBoxPtr;
    QSpinBox *fontBackgroundOpacitySpinBoxPtr;
    QLabel *workBackgroundColorLabelPtr;
    QLabel *breakBackgroundColorLabelPtr;
    QLabel *fontColorLabelPtr;
};

#endif // SETTINGSDIALOG_H
