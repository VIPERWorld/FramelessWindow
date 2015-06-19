#pragma once

#include <QObject>
#include <QSize>
#include <QPoint>
#include <QRect>


class AbstractMainWindow;
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
    void toogleFrame(bool t_framelesStyle);

    AbstractMainWindow* m_activeWindow;
    AbstractMainWindow* m_defaultWindow;
    AbstractMainWindow* m_framelessWindow;
    CentralWidget* m_centralWidget;

};

