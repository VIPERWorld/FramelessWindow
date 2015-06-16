#include <QtWidgets>

#include "framelesswindow.h"
#include "windowtitlebar.h"
#include "switcher.h"


FramelessWindow::FramelessWindow(const QSize& t_size, QWidget* t_parent)
    : IMainWindow(t_size, t_parent),
    m_titleBar(new WindowTitleBar)
{
    setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);

    m_titleBar->setTitle("Custom Window");

    m_mainLayout->addWidget(m_titleBar, 0, 0, 1, 3);

    m_mainLayout->setRowStretch(1, 1);
    m_mainLayout->setColumnStretch(1, 1);
}


void FramelessWindow::setMainWidget(QWidget* t_centralWidget)
{
    m_mainLayout->addWidget(t_centralWidget, 1, 1);
}


void FramelessWindow::onFrameSizeDetected(int t_bottom, int t_top)
{
    auto hSpacer = new QSpacerItem(t_bottom, 0, QSizePolicy::Fixed, QSizePolicy::Expanding);
    m_mainLayout->addItem(hSpacer, 1, 0);
    m_mainLayout->addItem(hSpacer, 1, 2);

    auto vSpacer = new QSpacerItem(0, t_bottom, QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_mainLayout->addItem(vSpacer, 2, 0, 1, 3);
}

