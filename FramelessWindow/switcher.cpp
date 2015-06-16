#include <QPainter>
#include <QAbstractAnimation>
#include <QPropertyAnimation>
#include <QFontDatabase>
#include <QGridLayout>

#include "switcher.h"


Circle::Circle(QWidget* t_parent)
    : QFrame(t_parent),
    m_switcherColor(Qt::white)
{
}


void Circle::paintEvent(QPaintEvent* t_event)
{
    Q_UNUSED(t_event);

    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);

    auto diameter = Switcher::getDiameterRatio() * height();
    auto spacer = static_cast<int>(Switcher::getSpacerRatio() * height());
    
    m_switcherRect = QRect(spacer, spacer, diameter, diameter);
    painter.setPen(Qt::NoPen);
    painter.setBrush(m_switcherColor);
    painter.drawEllipse(m_switcherRect);
}


void Circle::animate()
{
    auto switcherAnimation = new QPropertyAnimation(this, "pos");
    connect(switcherAnimation, &QPropertyAnimation::finished, this, &Circle::onChangeFrame);
    switcherAnimation->setDuration(350);
    switcherAnimation->setEasingCurve(QEasingCurve::Linear);

    QPoint startPos{ 0, 0 };
    auto diameter = Switcher::getDiameterRatio() * height();
    auto spacer = static_cast<int>(Switcher::getSpacerRatio() * height());
    QPoint endPos{ static_cast<int>(width() - diameter - 2 * spacer), 0 };
    if (!m_switchedOn) {
        startPos = endPos;
        endPos = { 0, 0 };
    }
    switcherAnimation->setStartValue(startPos);
    switcherAnimation->setEndValue(endPos);
    switcherAnimation->start(QAbstractAnimation::DeleteWhenStopped);

}


void Circle::onToggled()
{
    m_switchedOn = !m_switchedOn;
    animate();
}


void Circle::onChangeFrame()
{
    emit toggled(m_switchedOn);
}


Switcher::Switcher(QWidget* t_parent)
    : QAbstractButton(t_parent),
    m_mainLayout(new QGridLayout),
    m_switchedOnColor(QColor(146, 220, 92)),
    m_switchedOffColor(QColor(230, 222, 211)),
    m_circleSwitcher(new Circle(this))

{
    setLayout(m_mainLayout);
    m_mainLayout->addWidget(m_circleSwitcher, 0, 0);

    setContentsMargins(0, 0, 0, 0);
    layout()->setContentsMargins(0, 0, 0, 0);

    setCheckable(true);

    auto fontId = QFontDatabase::addApplicationFont(":/fonts/Resources/fonts/AlternateGotNo3D.ttf");
    auto loadedFontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    m_fontFamily = loadedFontFamilies.first();

    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    setMinimumWidth(WIDTH);
    setMinimumHeight(HEIGHT);


    connect(this, &QAbstractButton::toggled, m_circleSwitcher, &Circle::onToggled);
    connect(m_circleSwitcher, &Circle::toggled, this, &Switcher::toggled);
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


void Switcher::paintEvent(QPaintEvent* t_event)
{
    Q_UNUSED(t_event);

    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);

    painter.setPen(Qt::NoPen);

    auto switchedColor = m_switchedOffColor;
    if (m_circleSwitcher->m_switchedOn) {
        switchedColor = m_switchedOnColor;
    }

    auto outerDiameter = height();
    painter.setBrush(switchedColor);
    painter.drawEllipse(QRect(0.0, 0.0, outerDiameter, outerDiameter));
    painter.drawEllipse(QRect(width() - outerDiameter, 0, outerDiameter, outerDiameter));
    painter.drawRect(QRect(outerDiameter / 2, 0, width() - outerDiameter, outerDiameter));

    auto diameter = getDiameterRatio() * height();
    auto spacer = static_cast<int>(getSpacerRatio() * height());
    auto onTextRect = QRect(spacer, spacer, diameter, diameter);
    auto offTextRect = QRect(width() - diameter - spacer, spacer, diameter, diameter);

    painter.setPen(Qt::white);
    m_textFont = QFont(m_fontFamily, 16);
    painter.setFont(m_textFont);
    painter.drawText(onTextRect, Qt::AlignCenter, tr("ON"));
    painter.drawText(offTextRect, Qt::AlignCenter, tr("OFF"));
}

