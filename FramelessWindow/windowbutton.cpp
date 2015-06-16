#include <QPainter>
#include <QBitmap>

#include "windowbutton.h"


WindowButton::WindowButton(Type t_type, QWidget* t_parent)
    : QPushButton(t_parent),
    m_type(t_type)
{
}


void WindowButton::onWindowMaximized(bool t_maximized)
{
    if (m_type != Type::Maximize)
        return;
    m_maximized = t_maximized;
    initPixmaps();
}


void WindowButton::resizeEvent(QResizeEvent* t_event)
{
    Q_UNUSED(t_event);

    initPixmaps();
}


void WindowButton::paintEvent(QPaintEvent* t_event)
{
    Q_UNUSED(t_event);

    QPainter painter(this);

    if(isEnabled()) {
        switch(m_state)
        {
        case State::Normal:
            if(m_normal)
                painter.drawPixmap(0, 0, *m_normal );
            break;
        case State::Hovered:
            if(m_hovered)
                painter.drawPixmap(0, 0, *m_hovered);
            break;
        case State::Clicked:
            if(m_clicked)
                painter.drawPixmap(0, 0, *m_clicked);
            break;
        }
    } else if(m_normal) {
            painter.drawPixmap(0, 0, *m_normal);
    }
}


void WindowButton::initButton(const QPixmap& t_icon) const
{
    QPainter painter;

    /********** Normal **********/
    painter.begin(m_normal);

    painter.drawPixmap(0, 0, t_icon);

    painter.end();
    /****************************/

    /********** Hovered **********/
    painter.begin(m_hovered);

    QPixmap hoveredIcon = t_icon;
    hoveredIcon.fill(Qt::white);
    hoveredIcon.setMask(t_icon.createMaskFromColor(QColor(165, 164, 161)));

    painter.drawPixmap(0, 0, hoveredIcon);
    painter.drawPixmap(0, 0, t_icon);

    painter.end();
    /*****************************/

    /********** Clicked **********/
    painter.begin(m_clicked);

    QPixmap clickedIcon = t_icon;
    clickedIcon.fill(QColor(233, 231, 228));
    clickedIcon.setMask(t_icon.createMaskFromColor(QColor(165, 164, 161)));

    painter.drawPixmap(0, 0, clickedIcon);
    painter.drawPixmap(0, 0, t_icon);

    painter.end();
    /*****************************/
}


void WindowButton::initIcon(const QPixmap& t_icon)
{
    QPainter painter(m_normal);
    painter.drawPixmap(0, 0, t_icon);

    m_hovered = m_normal;
    m_clicked = m_normal;
}


void WindowButton::initPixmaps()
{
    initPixmap(&m_normal);
    initPixmap(&m_hovered);
    initPixmap(&m_clicked);

    auto path = QString(":/images/Resources/images/");
    QPixmap icon;
    switch(m_type)
    {
    case Type::Minimize:
        icon = QPixmap(path + "minimize.png");
        break;
    case Type::Maximize:
        icon = QPixmap(path + (m_maximized ? "restore.png" : "maximize.png"));
        break;
    case Type::Close: 
        icon = QPixmap(path + "close.png");
        break;
    case Type::Icon:
        icon = QPixmap(path + "custom_icon.png");
        break;
    }

    if (m_type != Type::Icon)
        initButton(icon);
    else
        initIcon(icon);
}


void WindowButton::initPixmap(QPixmap** t_pixmap) const
{
    delete *t_pixmap;
    *t_pixmap = new QPixmap(size());
    (*t_pixmap)->fill(Qt::transparent);
}


void WindowButton::enterEvent(QEvent *event)
{
    Q_UNUSED(event);

    m_state = State::Hovered;

    update();
}


void WindowButton::leaveEvent(QEvent* t_event)
{
    Q_UNUSED(t_event);

    m_state = State::Normal;

    update();
}


void WindowButton::mousePressEvent(QMouseEvent* t_event)
{
    QPushButton::mousePressEvent(t_event);

    m_state = State::Clicked;

    update();
}


void WindowButton::mouseReleaseEvent(QMouseEvent* t_event)
{
    QPushButton::mouseReleaseEvent(t_event);

    m_state = underMouse() ? State::Hovered : State::Normal;

    update();
}

