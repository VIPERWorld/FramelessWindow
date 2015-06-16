#pragma once

#include "imainwindow.h"

class Switcher;

class DefaultWindow : public IMainWindow
{
    Q_OBJECT

public:
    DefaultWindow(const QSize& t_size, QWidget* t_parent = nullptr);

signals:
    void frameSizeDetected(int t_bottom, int t_top);

protected:
    void resizeEvent(QResizeEvent* t_event) override;

private slots:
};
