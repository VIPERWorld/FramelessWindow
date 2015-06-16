#include <QGridLayout>

#include "framelesswindow.h"
#include "windowtitlebar.h"


FramelessWindow::FramelessWindow(QWidget* t_parent)
    : IMainWindow(t_parent),
    m_titleBar(new WindowTitleBar)
{
    setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);

    setTitle(tr("Custom Window"));

    m_mainLayout->addWidget(m_titleBar, 0, 0, 1, 3);

    m_mainLayout->setRowStretch(1, 1);
    m_mainLayout->setColumnStretch(1, 1);

}


void FramelessWindow::setMainWidget(QWidget* t_centralWidget)
{
    m_mainLayout->addWidget(t_centralWidget, 1, 1);
}


void FramelessWindow::setTitle(const QString& t_title)
{
    m_titleBar->setTitle(t_title);
}


void FramelessWindow::onFrameSizeDetected(int t_bottom, int t_top)
{
    Q_UNUSED(t_top);

    auto hSpacer = new QSpacerItem(t_bottom, 0, QSizePolicy::Fixed, QSizePolicy::Expanding);
    m_mainLayout->addItem(hSpacer, 1, 0);
    m_mainLayout->addItem(hSpacer, 1, 2);

    auto vSpacer = new QSpacerItem(0, t_bottom, QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_mainLayout->addItem(vSpacer, 2, 0, 1, 3);
}

