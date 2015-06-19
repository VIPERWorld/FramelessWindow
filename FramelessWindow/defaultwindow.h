#pragma once

#include "abstractmainwindow.h"


class DefaultWindow : public AbstractMainWindow
{
    Q_OBJECT

public:
    explicit DefaultWindow(QWidget* t_parent = nullptr);
    QRect getNormalGeometry() const override;

signals:
    void frameSizeDetected(int t_bottomBorder, int t_topBorder);

protected:
    void changeEvent(QEvent* t_event) override;
    void resizeEvent(QResizeEvent* t_event) override;

};

