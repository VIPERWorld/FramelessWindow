#include <QDebug>
#include <QMenuBar>

#include "transparentwindow.h"
#include "defaultwindow.h"
#include "framelesswindow.h"
#include "switcher.h"
#include "centralwidget.h"


TransparentWindow::TransparentWindow(QWidget* t_parent)
    : QMainWindow(t_parent),
    m_switcher(new CentralWidget),
    m_defaultWindow(new DefaultWindow(DEFAULT_WINDOW_SIZE)),
    m_framelessWindow(new FramelessWindow(QSize{m_defaultWindow->width(), m_defaultWindow->height()}))
{
    connect(static_cast<CentralWidget*>(m_switcher), &CentralWidget::changeFrame, 
        this, &TransparentWindow::toogleFrameStyle);

    connect(static_cast<DefaultWindow*>(m_defaultWindow), &DefaultWindow::frameSizeDetected,
        static_cast<FramelessWindow*>(m_framelessWindow), &FramelessWindow::onFrameSizeDetected);

    m_defaultWindow->setMainWidget(m_switcher);
    m_defaultWindow->show();
    m_framelessWindow->move(m_defaultWindow->pos());

    m_frameTitleSize = { m_defaultWindow->frameGeometry().width() - m_defaultWindow->width(),
        m_defaultWindow->frameGeometry().height() - m_defaultWindow->height() };
}


void TransparentWindow::toogleFrameStyle(bool t_framelessStyle)
{
    if (t_framelessStyle) {
        auto width = m_defaultWindow->frameGeometry().width();
        auto height = m_defaultWindow->frameGeometry().height();

        m_defaultWindow->hide();
        m_framelessWindow->resize(width, height);
        m_framelessWindow->setMainWidget(m_switcher);
        m_framelessWindow->move(m_defaultWindow->pos());
        m_framelessWindow->show();

    } else {

        auto width = m_framelessWindow->width() - m_frameTitleSize.width();
        auto height = m_framelessWindow->height() - m_frameTitleSize.height();

        m_framelessWindow->hide();
        m_defaultWindow->resize(width, height);
        m_defaultWindow->setMainWidget(m_switcher);
        m_defaultWindow->move(m_framelessWindow->pos());
        m_defaultWindow->show();
    }
}

