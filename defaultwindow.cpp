#include <QtWidgets>
#include <QDebug>

#include "defaultwindow.h"
#include "windowtitlebar.h"


DefaultWindow::DefaultWindow(const QSize& t_size, QWidget* t_parent)
    : IMainWindow(t_size, t_parent)
{
    setWindowTitle("Standart Window");
}


void DefaultWindow::resizeEvent(QResizeEvent* t_event)
{
    auto frameBottom = static_cast<int>((frameGeometry().width() - width()) * 0.5);
    auto frameTop = static_cast<int>(frameGeometry().height() - height() - frameBottom);
    setContentsMargins(0, qAbs(WindowTitleBar::HEIGHT - frameTop), 0, 0);

    emit frameSizeDetected(frameBottom, frameTop);
}

