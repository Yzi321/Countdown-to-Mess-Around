#ifndef _GLOBAL_H
#define _GLOBAL_H

#include <QColor>

typedef struct _DisplaySetting
{
    int countdown_work;
    int countdown_rest;
    int transparency_work;
    int transparency_rest;
    QColor background_work;
    QColor background_reset;
    QColor font_color;

}DisplaySetting;

void saveSettings(const DisplaySetting& settings);

void loadSettings(DisplaySetting& settings);

class _Global
{
public:
    _Global();
    static DisplaySetting displaySetting;
};

#endif // _GLOBAL_H
