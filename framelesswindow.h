#pragma once

#include "imainwindow.h"

class WindowTitleBar;

class FramelessWindow : public IMainWindow
{
    Q_OBJECT
public:
    FramelessWindow(const QSize& t_size, QWidget* t_parent = nullptr);

    void setMainWidget(QWidget* t_centralWidget) override;

public slots:
    void onFrameSizeDetected(int t_bottom, int t_top);

private:
    WindowTitleBar* m_titleBar;

};