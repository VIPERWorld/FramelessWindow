#pragma once

#include <QtWidgets/QMainWindow>
#include <QAction>

#include "imainwindow.h"

class Switcher;
class IMainWindow;

class TransparentWindow : public QMainWindow
{
    Q_OBJECT
public:
    const QSize DEFAULT_WINDOW_SIZE{ 784, 539 };
    //const QSize FRAMELESS_WINDOW_SIZE{ 800, 578 };

    TransparentWindow(QWidget* t_parent = nullptr);

private:
    void toogleFrameStyle(bool t_defaultStyle);

    QWidget* m_switcher;
    IMainWindow* m_defaultWindow;
    IMainWindow* m_framelessWindow;

    QSize m_frameTitleSize;

    bool m_framelessStyle = false;
};