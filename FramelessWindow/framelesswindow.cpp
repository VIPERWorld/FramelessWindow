#include <QAction>
#include <QMenu>
#include <QApplication>
#include <QGridLayout>
#include <QMouseEvent>

#include "framelesswindow.h"
#include "windowtitlebar.h"


FramelessWindow::FramelessWindow(QWidget* t_parent)
    : AbstractMainWindow(t_parent),
    m_titleBar(new WindowTitleBar)
{
    setupConnects();
    createActions();

    setWindowFlags(Qt::FramelessWindowHint);
    setWindowTitle(tr("Custom Window"));

    m_mainLayout->addWidget(m_titleBar, 0, 0, 1, 3);

    m_mainLayout->setRowStretch(1, 1);
    m_mainLayout->setColumnStretch(1, 1);

}


QRect FramelessWindow::getNormalGeometry() const
{
    auto point = window()->geometry().topLeft() + QPoint{ m_bottomFrame, m_topFrame };
    auto size = window()->geometry().size() - 
        QSize{ 2 * m_bottomFrame, m_topFrame + m_bottomFrame };
    return{ point, size };
}


void FramelessWindow::setMainWidget(QWidget* t_centralWidget)
{
    m_mainLayout->addWidget(t_centralWidget, 1, 1);
}


void FramelessWindow::mousePressEvent(QMouseEvent* t_event)
{
    if (t_event->button() == Qt::LeftButton) {
        if (!isMaximized()
            && t_event->y() < m_titleBar->height()
            && t_event->x() < m_titleBar->width()) {
            m_windowDragStartPos = t_event->pos();
        }
    } else if (t_event->button() == Qt::RightButton) {
        showContextMenu(t_event->globalPos());
    }

}


void FramelessWindow::mouseDoubleClickEvent(QMouseEvent* t_event)
{
    if (t_event->y() < m_titleBar->height()
        && t_event->x() < m_titleBar->width()) {
        switchNormalMaximize();
        t_event->accept();
        return;
    }
    t_event->ignore();
}


void FramelessWindow::mouseReleaseEvent(QMouseEvent* t_event)
{
    Q_UNUSED(t_event);
    m_windowDragStartPos = QPoint(0, 0);
}


void FramelessWindow::mouseMoveEvent(QMouseEvent* t_event)
{
    if (!m_windowDragStartPos.isNull()) {
        auto p = t_event->globalPos();
        window()->move(p - m_windowDragStartPos);
    }
}


void FramelessWindow::setupConnects()
{
    connect(this, &QWidget::windowTitleChanged,      m_titleBar, &WindowTitleBar::setTitle);
    connect(this, &FramelessWindow::windowMaximized, m_titleBar, &WindowTitleBar::onWindowMaximized);

    connect(m_titleBar, &WindowTitleBar::iconClicked,     this, &FramelessWindow::showSystemContextMenu);
    connect(m_titleBar, &WindowTitleBar::maximizeClicked, this, &FramelessWindow::switchNormalMaximize);
    connect(m_titleBar, &WindowTitleBar::minimizeClicked, this, &FramelessWindow::minimize);
    connect(m_titleBar, &WindowTitleBar::quitClicked,     qApp, &QApplication::quit);
}


void FramelessWindow::createActions()
{
    auto path = QString(":/images/Resources/images/");

    m_restoreAction = new QAction(QIcon(path + "restore.png"), tr("Restore"), this);
    m_minimizeAction = new QAction(QIcon(path + "minimize.png"), tr("Minimize"), this);
    m_maximizeAction = new QAction(QIcon(path + "maximize.png"), tr("Maximize"), this);
    m_closeAction = new QAction(QIcon(path + "close.png"), tr("Close"), this);

    connect(m_minimizeAction, &QAction::triggered, this, &FramelessWindow::minimize);
    connect(m_maximizeAction, &QAction::triggered, this, &FramelessWindow::switchNormalMaximize);
    connect(m_restoreAction, &QAction::triggered,  this, &FramelessWindow::switchNormalMaximize);
    connect(m_closeAction, &QAction::triggered,    qApp, &QApplication::quit);
}


void FramelessWindow::getContextMenu(QMenu& t_menu)
{
    t_menu.clear();

    t_menu.addAction(m_restoreAction);
    t_menu.addAction(m_minimizeAction);
    t_menu.addAction(m_maximizeAction);
    t_menu.addAction(m_closeAction);
    t_menu.insertSeparator(m_closeAction);

    auto maximized = isMaximized();
    m_restoreAction->setEnabled(maximized);
    m_maximizeAction->setEnabled(!maximized);
}


void FramelessWindow::showContextMenu(const QPoint& t_pos)
{
    QMenu contextMenu;
    getContextMenu(contextMenu);
    contextMenu.exec(t_pos);
}


void FramelessWindow::onFrameSizeDetected(int t_bottomBorder, int t_topBorder)
{
    static bool once = true;
    if (once) {
        once = !once;
        m_bottomFrame = t_bottomBorder;
        m_topFrame = t_topBorder;

        auto hSpacer = new QSpacerItem(t_bottomBorder, 0, QSizePolicy::Fixed, QSizePolicy::Expanding);
        m_mainLayout->addItem(hSpacer, 1, 0);
        m_mainLayout->addItem(hSpacer, 1, 2);

        auto vSpacer = new QSpacerItem(0, t_bottomBorder, QSizePolicy::Expanding, QSizePolicy::Fixed);
        m_mainLayout->addItem(vSpacer, 2, 0, 1, 3);
    }
}


void FramelessWindow::switchNormalMaximize()
{
    auto maximized = isMaximized();
    emit windowMaximized(!maximized);

    if (maximized) {
        showNormal();
        return;
    }

    showMaximized();
}


void FramelessWindow::minimize()
{
    window()->showMinimized();
}


void FramelessWindow::showSystemContextMenu()
{
    auto globalPos = window()->mapToGlobal({ 0, WindowTitleBar::HEIGHT });
    showContextMenu(globalPos);
}


void FramelessWindow::resizeEvent(QResizeEvent* t_event)
{
    Q_UNUSED(t_event);

    enableSwitcher();
}
