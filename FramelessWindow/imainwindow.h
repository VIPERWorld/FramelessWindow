#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QGridLayout;
QT_END_NAMESPACE


class IMainWindow : public QMainWindow
{
public:
    const static QSize DEFAULT_WINDOW_SIZE;
    const static QColor DEFAULT_BACKGROUND_COLOR;

    explicit IMainWindow(QWidget* t_parent = nullptr);

    virtual ~IMainWindow()
    {
    }

    virtual void setMainWidget(QWidget* t_switcher);


protected:
    QWidget* m_centralWidget;
    QGridLayout* m_mainLayout;

};

