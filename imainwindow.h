#pragma once

#include <QtWidgets/QMainWindow>

QT_BEGIN_NAMESPACE
class QGridLayout;
class QSize;
QT_END_NAMESPACE

class Switcher;
class CentralWidget;

class IMainWindow : public QMainWindow
{
public:
    IMainWindow(const QSize &t_size, QWidget* t_parent = nullptr);

    virtual void setMainWidget(QWidget* t_switcher);

    virtual ~IMainWindow()
    {
    }

protected:
    QWidget* m_centralWidget;
    QGridLayout* m_mainLayout;

};

