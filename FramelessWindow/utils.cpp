#include "utils.h"

#include <QFont>
#include <QFontDatabase>
#include <QPainter>


Utils::Utils()
{
    auto fontId = QFontDatabase::addApplicationFont(":/fonts/Resources/fonts/AlternateGotNo3D.ttf");
    auto loadedFontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    m_fontFamily = loadedFontFamilies.first();
}


Utils& Utils::instance()
{
    static Utils utils;
    return utils;
}


QFont Utils::font(int t_size)
{
    return{ m_fontFamily, t_size };
}


void Utils::setupAntializing(QPainter& t_painter)
{
    t_painter.setRenderHint(QPainter::Antialiasing);
    t_painter.setRenderHint(QPainter::HighQualityAntialiasing);
}

