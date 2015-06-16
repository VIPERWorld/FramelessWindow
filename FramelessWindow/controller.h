#pragma once

#include <QObject>
#include <QSize>
#include <QPoint>


class IMainWindow;
class CentralWidget;
class DefaultWindow;
class FramelessWindow;

class Controller : public QObject
{
    Q_OBJECT

public:
    const QSize DEFAULT_WINDOW_SIZE{ 784, 539 };

    Controller(QObject* t_parent = nullptr);

private:
    void toogleFrameStyle(bool t_defaultStyle);

    IMainWindow* m_activeWindow;
    CentralWidget* m_centralWidget;
    DefaultWindow* m_defaultWindow;
    FramelessWindow* m_framelessWindow;
    QSize m_frameTitleSize;
    bool m_framelessStyle = false;
    QPoint m_lastPos;

};

