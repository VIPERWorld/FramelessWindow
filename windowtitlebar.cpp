#include <QtGui>
#include <QLabel>
#include <QMenu>

#include "windowtitlebar.h"
#include "windowbutton.h"


WindowTitleBar::WindowTitleBar(QWidget* t_parent) 
	: QWidget(t_parent),
	m_cache(nullptr),
    m_title(new QLabel(this)),
	m_minimize(new WindowButton(WindowButton::Type::Minimize, this)),
	m_maximize(new WindowButton(WindowButton::Type::Maximize, this)),
	m_close(new WindowButton(WindowButton::Type::Close, this)),
    m_icon(new WindowButton(WindowButton::Type::Icon, this))

{
    createActions();

    connect(m_icon, &WindowButton::clicked, this, &WindowTitleBar::showSystemContextMenu);

	connect(m_minimize, &WindowButton::clicked, this, &WindowTitleBar::minimized);
	connect(m_maximize, &WindowButton::clicked, this, &WindowTitleBar::maximized);
	connect(m_close,    &WindowButton::clicked, this, &WindowTitleBar::quit);

    connect(this, &WindowTitleBar::maximize, m_maximize, &WindowButton::onWindowMaximized);

	setFixedHeight(HEIGHT);

	m_title->setStyleSheet("color: rgb(21, 21, 20); font-family: Sans; font-size: 15px");
	updateWindowTitle();
}


void WindowTitleBar::setTitle(const QString& t_title)
{
    m_title->setText(t_title);
}


void WindowTitleBar::resizeEvent(QResizeEvent* t_event)
{
	Q_UNUSED(t_event);

	delete m_cache;
	m_cache = new QPixmap(size());

	m_cache->fill(Qt::transparent);
	QPainter painter(m_cache);

	/********** Title bar's frame **********/
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(252, 250, 247));
    painter.drawRect(QRect(0, 0, width(), height() - BOTTOM_LINE_WIDTH));

    painter.setPen(QPen(QColor(236, 234, 230), BOTTOM_LINE_WIDTH));
    painter.drawLine(QLine(0, height() - BOTTOM_LINE_WIDTH, 
        width(), height() - BOTTOM_LINE_WIDTH));
	/***************************************/

    m_icon->move(9, 10);

	m_title->move(39, -10);
	m_title->resize(width() - 116, 59);

	m_minimize->move(width() - 81, 10);
	m_maximize->move(width() - 56, 10);
	m_close->move(width() - 32, 10);

    emit maximize(window()->windowState() == Qt::WindowMaximized);
}


void WindowTitleBar::paintEvent(QPaintEvent* t_event)
{
	Q_UNUSED(t_event);

	if(m_cache) {
		QPainter painter(this);
		painter.drawPixmap(0, 0, *m_cache);
	}
}


void WindowTitleBar::updateWindowTitle()
{
	m_title->setText(window()->windowTitle());
}


void WindowTitleBar::minimized()
{
	window()->showMinimized();
}


void WindowTitleBar::maximized()
{
    if (window()->windowState() == Qt::WindowMaximized)
        window()->showNormal();
    else
        window()->showMaximized();
}


void WindowTitleBar::quit()
{
	qApp->quit();
}


void WindowTitleBar::mousePressEvent(QMouseEvent* t_event)
{
    if (t_event->button() == Qt::LeftButton) {

        if (!window()->isMaximized()
            && geometry().contains(t_event->pos()))
            m_windowDragStartPos = t_event->pos();

    } else if (t_event->button() == Qt::RightButton) {
        showContextMenu(t_event->globalPos());
        
    }
}


void WindowTitleBar::mouseReleaseEvent(QMouseEvent* t_event)
{
	Q_UNUSED(t_event);
    m_windowDragStartPos = QPoint(0, 0);
}


void WindowTitleBar::mouseMoveEvent(QMouseEvent* t_event)
{
    if (!m_windowDragStartPos.isNull()) {
        auto p = t_event->globalPos();
        window()->move(p - m_windowDragStartPos);
    }
}


void WindowTitleBar::createActions()
{
    auto path = QString(":/images/Resources/images/");

    m_restoreAction = new QAction(QIcon(path + "restore.png"), tr("Restore"), this);
    m_minimizeAction = new QAction(QIcon(path + "minimize.png"), tr("Minimize"), this);
    m_maximizeAction = new QAction(QIcon(path + "maximize.png"), tr("Maximize"), this);
    m_closeAction = new QAction(QIcon(path + "close.png"), tr("Close"), this);

	connect(m_minimizeAction, &QAction::triggered, this, &WindowTitleBar::minimized);
	connect(m_maximizeAction, &QAction::triggered, this, &WindowTitleBar::maximized);
	connect(m_restoreAction, &QAction::triggered, this, &WindowTitleBar::maximized);
	connect(m_closeAction, &QAction::triggered, this, &WindowTitleBar::quit);
}


void WindowTitleBar::getContextMenu(QMenu& t_menu)
{
    t_menu.clear();

    t_menu.addAction(m_restoreAction);
    t_menu.addAction(m_minimizeAction);
    t_menu.addAction(m_maximizeAction);
    t_menu.addAction(m_closeAction);
    t_menu.insertSeparator(m_closeAction);

    const auto &maximized = window()->isMaximized();
    m_restoreAction->setEnabled(maximized);
    m_maximizeAction->setEnabled(!maximized);
}

void WindowTitleBar::showContextMenu(const QPoint& t_pos)
{
    QMenu contextMenu;
    getContextMenu(contextMenu);
    contextMenu.exec(t_pos);
}


void WindowTitleBar::showSystemContextMenu()
{
    auto globalPos = window()->mapToGlobal({ 0, HEIGHT });
    showContextMenu(globalPos);
    
}