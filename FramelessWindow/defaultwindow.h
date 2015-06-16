#pragma once

#include "imainwindow.h"


class DefaultWindow : public IMainWindow
{
    Q_OBJECT

public:
    explicit DefaultWindow(QWidget* t_parent = nullptr);

signals:
    void frameSizeDetected(int t_bottom, int t_top);

protected:
    void resizeEvent(QResizeEvent* t_event) override;

};

