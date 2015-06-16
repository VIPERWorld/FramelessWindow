#include <QDebug>
#include <QMenuBar>

#include "controller.h"
#include "defaultwindow.h"
#include "framelesswindow.h"
#include "centralwidget.h"


Controller::Controller(QObject* t_parent)
    : QObject(t_parent),
    m_centralWidget(new CentralWidget),
    m_defaultWindow(new DefaultWindow),
    m_framelessWindow(new FramelessWindow)
{
    connect(m_centralWidget, &CentralWidget::changeFrame, this, &Controller::toogleFrameStyle);

    connect(m_defaultWindow, &DefaultWindow::frameSizeDetected,
        m_framelessWindow, &FramelessWindow::onFrameSizeDetected);

    m_activeWindow = m_defaultWindow;
    m_activeWindow->setMainWidget(m_centralWidget);
    m_activeWindow->show();

    m_frameTitleSize = { m_defaultWindow->frameGeometry().width() - m_defaultWindow->width(),
        m_defaultWindow->frameGeometry().height() - m_defaultWindow->height() };
}


void Controller::toogleFrameStyle(bool t_framelessStyle)
{
    auto isMaximized = m_activeWindow->isMaximized();
    auto width = m_activeWindow->frameGeometry().width();
    auto height = m_activeWindow->frameGeometry().height();

    if (!isMaximized)
        m_lastPos = m_activeWindow->pos();


    if (t_framelessStyle) {
        m_activeWindow->hide();
        m_activeWindow = m_framelessWindow;
    } else {
        width = m_activeWindow->width() - m_frameTitleSize.width();
        height = m_activeWindow->height() - m_frameTitleSize.height();
        m_activeWindow->hide();
        m_activeWindow = m_defaultWindow;
    }
    m_activeWindow->setMainWidget(m_centralWidget);

    if (isMaximized) {
        m_activeWindow->showMaximized();
    } else {
        m_activeWindow->resize(width, height);
        m_activeWindow->move(m_lastPos);
        m_activeWindow->show();
    }
}

