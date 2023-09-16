#include "_global.h"

#define H_countdown_work        32
#define H_countdown_rest        5
#define H_transparency_work     130
#define H_transparency_rest     255

DisplaySetting _Global::displaySetting = {
    H_countdown_work,
    H_countdown_rest,
    H_transparency_work,
    H_transparency_rest,
    QColor(0, 128, 0, H_transparency_work),
    QColor(128, 128, 0, H_transparency_work),
    QColor(255, 255, 255, H_transparency_rest)
};

//displaySetting.background_work.setAlpha(displaySetting.transparency_work);
//displaySetting.background_reset.setAlpha(displaySetting.transparency_work);
//displaySetting.font_color.setAlpha(displaySetting.transparency_rest);
_Global::_Global()
{
    loadSettings(_Global::displaySetting);
}



#include <QSettings>

void saveSettings(const DisplaySetting& settings) {

    QSettings qsettings("./MessAroundConfig.ini", QSettings::IniFormat);
    qsettings.beginGroup("user_settings");
    qsettings.setValue("countdown_work", settings.countdown_work);
    qsettings.setValue("countdown_rest", settings.countdown_rest);
    qsettings.setValue("transparency_work", settings.transparency_work);
    qsettings.setValue("transparency_rest", settings.transparency_rest);
    qsettings.setValue("background_work", settings.background_work);
    qsettings.setValue("background_reset", settings.background_reset);
    qsettings.setValue("font_color", settings.font_color);
    qsettings.endGroup();
}

void loadSettings(DisplaySetting& settings) {
    QSettings qsettings("./MessAroundConfig.ini", QSettings::IniFormat);
    qsettings.beginGroup("user_settings");
    settings.countdown_work = qsettings.value("countdown_work", 0).toInt();
    settings.countdown_rest = qsettings.value("countdown_rest", 0).toInt();
    settings.transparency_work = qsettings.value("transparency_work", 255).toInt();
    settings.transparency_rest = qsettings.value("transparency_rest", 255).toInt();
    settings.background_work = qsettings.value("background_work", QColor(Qt::white)).value<QColor>();
    settings.background_reset = qsettings.value("background_reset", QColor(Qt::white)).value<QColor>();
    settings.font_color = qsettings.value("font_color", QColor(Qt::black)).value<QColor>();
    qsettings.endGroup();
}

