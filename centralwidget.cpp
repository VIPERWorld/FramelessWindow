#include <QPushButton>
#include <QFontDatabase>
#include <QLabel>
#include <QVBoxLayout>

#include "centralwidget.h"
#include "switcher.h"


CentralWidget::CentralWidget(QWidget* t_parent)
    : QWidget(t_parent),
    m_mainLayout(new QVBoxLayout),
    m_switcher(new Switcher),
    m_captionLabel(new QLabel(tr("Use slider to switch window states").toUpper()))
{
    styleCaptionLabel();

    setLayout(m_mainLayout);
    setContentsMargins(0, 0, 0, 0);
    layout()->setContentsMargins(0, 0, 0, 0);

    connect(static_cast<Switcher*>(m_switcher), &Switcher::changeFrame, this, &CentralWidget::changeFrame);

    auto vSpacerTop = new QSpacerItem(0, 109, QSizePolicy::Expanding, QSizePolicy::Fixed);
    auto vSpacerCenter = new QSpacerItem(0, 76, QSizePolicy::Expanding, QSizePolicy::Fixed);

    m_mainLayout->addSpacing(109);
    m_mainLayout->addWidget(m_switcher, 1, Qt::AlignCenter);
    m_mainLayout->addWidget(m_captionLabel, 1, Qt::AlignCenter);

}


void CentralWidget::styleCaptionLabel()
{
    auto fontId = QFontDatabase::addApplicationFont(":/fonts/Resources/fonts/AlternateGotNo3D.ttf");
    auto loadedFontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    auto m_fontFamily = loadedFontFamilies.first();

    m_captionLabel->setFont(QFont(m_fontFamily, 11));
    auto palette = m_captionLabel->palette();
    palette.setColor(m_captionLabel->foregroundRole(), QColor(204, 204, 204));
    m_captionLabel->setPalette(palette);
}

