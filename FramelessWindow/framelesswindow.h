#pragma once

#include "imainwindow.h"


class WindowTitleBar;

class FramelessWindow : public IMainWindow
{
    Q_OBJECT

public:
    explicit FramelessWindow(QWidget* t_parent = nullptr);

    void setMainWidget(QWidget* t_centralWidget) override;

public slots:
    void onFrameSizeDetected(int t_bottom, int t_top);
    void setTitle(const QString &t_title);

private:
    WindowTitleBar* m_titleBar;

};

