#include <QMenuBar>

#include "controller.h"
#include "defaultwindow.h"
#include "framelesswindow.h"
#include "centralwidget.h"


Controller::Controller(QObject* t_parent)
    : QObject(t_parent),
    m_defaultWindow(new DefaultWindow),
    m_framelessWindow(new FramelessWindow),
    m_centralWidget(new CentralWidget)
{
    connect(m_centralWidget, &CentralWidget::changeFrame, this, &Controller::toogleFrame);


    connect(static_cast<DefaultWindow*>(m_defaultWindow), &DefaultWindow::frameSizeDetected,
        static_cast<FramelessWindow*>(m_framelessWindow), &FramelessWindow::onFrameSizeDetected);

    m_activeWindow = m_defaultWindow;
    connect(m_activeWindow, &AbstractMainWindow::enableSwitcherSignal, m_centralWidget, &CentralWidget::enableSwitcher);
    m_activeWindow->setMainWidget(m_centralWidget);
    m_activeWindow->showNormal();

}


void Controller::toogleFrame(bool t_framelessWindow)
{
    auto maximized = m_activeWindow->isMaximized();
    auto normalGeometry = m_activeWindow->getNormalGeometry();

    m_activeWindow->hide();

    m_activeWindow = t_framelessWindow ? m_framelessWindow : m_defaultWindow;
    connect(m_activeWindow, &AbstractMainWindow::enableSwitcherSignal, m_centralWidget, &CentralWidget::enableSwitcher);
        
    if (!maximized)
        m_activeWindow->setGeometry(normalGeometry);

    m_activeWindow->setMainWidget(m_centralWidget);

    if (!maximized)
        m_activeWindow->showNormal();
    else
        m_activeWindow->showMaximized();

}

