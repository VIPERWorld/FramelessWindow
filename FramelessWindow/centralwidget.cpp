#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

#include "centralwidget.h"
#include "switcher.h"
#include "utils.h"


CentralWidget::CentralWidget(QWidget* t_parent)
    : QWidget(t_parent),
    m_mainLayout(new QVBoxLayout(this)),
    m_switcher(new Switcher(this)),
    m_captionLabel(new QLabel(tr("Use slider to switch window states").toUpper()))
{
    styleCaptionLabel();

    setLayout(m_mainLayout);
    setContentsMargins(0, 0, 0, 0);
    layout()->setContentsMargins(0, 0, 0, 0);

    connect(m_switcher, &Switcher::toggled, this, &CentralWidget::changeFrame);

    m_mainLayout->addSpacing(109);
    m_mainLayout->addWidget(m_switcher, 1, Qt::AlignCenter);
    m_mainLayout->addWidget(m_captionLabel, 1, Qt::AlignCenter);

}


void CentralWidget::enableSwitcher(bool t_enable)
{
    m_switcher->setEnabled(t_enable);
}


void CentralWidget::styleCaptionLabel()
{
    m_captionLabel->setFont(Utils::instance().font(11));
    auto palette = m_captionLabel->palette();
    palette.setColor(m_captionLabel->foregroundRole(), QColor(204, 204, 204));
    m_captionLabel->setPalette(palette);
}


