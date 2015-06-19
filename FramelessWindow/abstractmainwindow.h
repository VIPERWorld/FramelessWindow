#pragma once

#include <QMainWindow>


QT_BEGIN_NAMESPACE
class QGridLayout;
QT_END_NAMESPACE


class AbstractMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    const static QSize DEFAULT_WINDOW_SIZE;
    const static QColor DEFAULT_BACKGROUND_COLOR;

    explicit AbstractMainWindow(QWidget* t_parent = nullptr);

    virtual ~AbstractMainWindow()
    {
    }

    virtual QRect getNormalGeometry() const = 0;

    virtual void setMainWidget(QWidget* t_switcher);

signals:
    void enableSwitcherSignal(bool);

protected:
    QWidget* m_centralWidget;
    QGridLayout* m_mainLayout;

    void enableSwitcher();
};

