#include "defaultwindow.h"
#include "windowtitlebar.h"


DefaultWindow::DefaultWindow(QWidget* t_parent)
    : AbstractMainWindow(t_parent)
{
    setWindowTitle(tr("Standart Window"));
}


QRect DefaultWindow::getNormalGeometry() const
{
    return window()->frameGeometry();
}


void DefaultWindow::changeEvent(QEvent* t_event)
{
    Q_UNUSED(t_event);

    enableSwitcher();
}


void DefaultWindow::resizeEvent(QResizeEvent* t_event)
{
    Q_UNUSED(t_event);

    auto frameBottomBorder = static_cast<int>((frameGeometry().width() - width()) * 0.5);
    auto frameTopBorder =    static_cast<int>(frameGeometry().height() - height() - frameBottomBorder);
    setContentsMargins(0, qAbs(WindowTitleBar::HEIGHT - frameTopBorder), 0, 0);

    emit frameSizeDetected(frameBottomBorder, frameTopBorder);
}

