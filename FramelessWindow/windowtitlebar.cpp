#include <QLabel>
#include <QPainter>

#include "windowtitlebar.h"
#include "windowbutton.h"


WindowTitleBar::WindowTitleBar(QWidget* t_parent)
    : QWidget(t_parent),
    m_cache(nullptr),
    m_title(new QLabel(this)),
    m_icon(new WindowButton(WindowButton::Type::Icon, this)),
    m_minimize(new WindowButton(WindowButton::Type::Minimize, this)),
    m_maximize(new WindowButton(WindowButton::Type::Maximize, this)),
    m_close(new WindowButton(WindowButton::Type::Close, this))

{
    connect(m_icon,     &WindowButton::clicked, this, &WindowTitleBar::iconClicked);
    connect(m_minimize, &WindowButton::clicked, this, &WindowTitleBar::minimizeClicked);
    connect(m_maximize, &WindowButton::clicked, this, &WindowTitleBar::maximizeClicked);
    connect(m_close,    &WindowButton::clicked, this, &WindowTitleBar::quitClicked);

    setFixedHeight(HEIGHT);

    m_title->setStyleSheet("color: rgb(21, 21, 20); font-size: 15px");
}


void WindowTitleBar::setTitle(const QString& t_title)
{
    m_title->setText(t_title);
}


void WindowTitleBar::onWindowMaximized(bool t_maximized)
{
    m_maximize->setMaximized(t_maximized);
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
}


void WindowTitleBar::paintEvent(QPaintEvent* t_event)
{
    Q_UNUSED(t_event);

    if(m_cache) {
        QPainter painter(this);
        painter.drawPixmap(0, 0, *m_cache);
    }
}

