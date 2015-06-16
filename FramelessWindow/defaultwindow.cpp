#include "defaultwindow.h"
#include "windowtitlebar.h"


DefaultWindow::DefaultWindow(QWidget* t_parent)
    : IMainWindow(t_parent)
{
    setWindowTitle(tr("Standart Window"));
}


void DefaultWindow::resizeEvent(QResizeEvent* t_event)
{
    Q_UNUSED(t_event);

    auto frameBottom = static_cast<int>((frameGeometry().width() - width()) * 0.5);
    auto frameTop =    static_cast<int>(frameGeometry().height() - height() - frameBottom);
    setContentsMargins(0, qAbs(WindowTitleBar::HEIGHT - frameTop), 0, 0);

    emit frameSizeDetected(frameBottom, frameTop);
}

