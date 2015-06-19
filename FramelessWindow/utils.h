#pragma once

#include <QFont>

class QPainter;

class Utils
{
    Utils();

public:
    static Utils& instance();
    QFont font(int t_size);

    void setupAntializing(QPainter& t_painter);

private:
    QString m_fontFamily;

};

