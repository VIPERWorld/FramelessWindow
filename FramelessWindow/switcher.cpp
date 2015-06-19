#include <QPainter>
#include <QAbstractAnimation>
#include <QPropertyAnimation>
#include <QGridLayout>

#include "switcher.h"


const QColor Switcher::SWITCHER_COLOR{ 255, 255, 255 };
const QColor Switcher::TEXT_COLOR{ 255, 255, 255 };
const QColor Switcher::SWITCHED_ON_COLOR{ 146, 220, 92 };
const QColor Switcher::SWITCHED_OFF_COLOR{ 230, 222, 211 };


bool Switcher::m_switchedOn{ false };


Switcher::Switcher(QWidget* t_parent)
    : QAbstractButton(t_parent),
    m_mainLayout(new QGridLayout),
    m_capsule(new Capsule(this))
{
    setLayout(m_mainLayout);
    m_mainLayout->addWidget(m_capsule, 0, 0);

    setContentsMargins(0, 0, 0, 0);
    layout()->setContentsMargins(0, 0, 0, 0);

    setCheckable(true);

    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    setMinimumWidth(WIDTH);
    setMinimumHeight(HEIGHT);

    connect(this, &QAbstractButton::toggled, m_capsule, &Capsule::onToggled);
    connect(m_capsule, &Capsule::toggled, this, &Switcher::toggled);
}


void Switcher::resizeEvent(QResizeEvent* t_event)
{
    Q_UNUSED(t_event);

    auto containerWidth = geometry().width();
    auto containerHeight = geometry().height();

    auto contentsHeight = containerHeight;
    auto contentsWidth = static_cast<int>(containerHeight * getAspectRatio());
    if (contentsWidth > containerWidth) {
        contentsWidth = containerWidth;
        contentsHeight = containerWidth / getAspectRatio();
    }

    resize(contentsWidth, contentsHeight);
}


Capsule::Capsule(QWidget* t_parent)
    : QFrame(t_parent), m_circle(new Circle(this))
{
    auto *mainLayout = new QGridLayout(this);
    setLayout(mainLayout);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(m_circle);

    connect(m_circle, &Circle::toggled, this, &Capsule::toggled);
}


void Capsule::animate()
{
    auto animation = new QPropertyAnimation(this, "color");
    animation->setDuration(Switcher::ANIMATION_DURATION);
    animation->setEasingCurve(QEasingCurve::Linear);
    animation->setDirection(Switcher::switchedOn() ? animation->Forward : animation->Backward);

    animation->setStartValue(Switcher::SWITCHED_OFF_COLOR);
    animation->setEndValue(Switcher::SWITCHED_ON_COLOR);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}


void Capsule::onToggled()
{
    Switcher::toogle();
    m_circle->animate();
    animate();
}


void Capsule::paintEvent(QPaintEvent* t_event)
{
    Q_UNUSED(t_event);

    QPainter painter(this);

    Utils::instance().setupAntializing(painter);

    painter.setPen(Qt::NoPen);
    painter.setBrush(m_color);

    auto outerDiameter = height();
    painter.drawEllipse(QRect(0.0, 0.0, outerDiameter, outerDiameter));
    painter.drawEllipse(QRect(width() - outerDiameter, 0, outerDiameter, outerDiameter));
    painter.drawRect(QRect(outerDiameter / 2, 0, width() - outerDiameter, outerDiameter));

    auto diameter = Switcher::getDiameterRatio() * height();
    auto spacer = static_cast<int>(Switcher::getSpacerRatio() * height());
    auto onTextRect = QRect(spacer, spacer, diameter, diameter);
    auto offTextRect = QRect(width() - diameter - spacer, spacer, diameter, diameter);

    painter.setPen(Switcher::TEXT_COLOR);
    painter.setFont(m_textFont);
    painter.drawText(onTextRect, Qt::AlignCenter, tr("ON"));
    painter.drawText(offTextRect, Qt::AlignCenter, tr("OFF"));
}


Circle::Circle(QWidget* t_parent)
    : QFrame(t_parent)
{
}


void Circle::paintEvent(QPaintEvent* t_event)
{
    Q_UNUSED(t_event);

    QPainter painter(this);

    Utils::instance().setupAntializing(painter);

    auto diameter = Switcher::getDiameterRatio() * height();
    auto spacer = static_cast<int>(Switcher::getSpacerRatio() * height());
    
    auto rect = QRect(spacer, spacer, diameter, diameter);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Switcher::SWITCHER_COLOR);
    painter.drawEllipse(rect);
}


void Circle::animate()
{
    auto animation = new QPropertyAnimation(this, "pos");
    connect(animation, &QPropertyAnimation::finished, this, [&](){ emit toggled(Switcher::switchedOn()); });
    animation->setDuration(Switcher::ANIMATION_DURATION);
    animation->setDirection(Switcher::switchedOn() ? animation->Forward : animation->Backward);
    animation->setEasingCurve(QEasingCurve::Linear);

    QPoint startPos{ 0, 0 };
    auto diameter = Switcher::getDiameterRatio() * height();
    auto spacer = static_cast<int>(Switcher::getSpacerRatio() * height());
    QPoint endPos{ static_cast<int>(width() - diameter - 2 * spacer), 0 };

    animation->setStartValue(startPos);
    animation->setEndValue(endPos);
    animation->start(QAbstractAnimation::DeleteWhenStopped);

}

