#include <QGridLayout>

#include "imainwindow.h"


const QSize IMainWindow::DEFAULT_WINDOW_SIZE{ 784, 539 };
const QColor IMainWindow::DEFAULT_BACKGROUND_COLOR{ Qt::white };


IMainWindow::IMainWindow(QWidget* t_parent)
    : QMainWindow(t_parent),
    m_centralWidget(new QWidget(this)),
    m_mainLayout(new QGridLayout(m_centralWidget))
{
    setContentsMargins(0, 0, 0, 0);
    layout()->setContentsMargins(0, 0, 0, 0);

    m_mainLayout->setMargin(0);
    m_mainLayout->setSpacing(0);

    setMinimumSize(DEFAULT_WINDOW_SIZE);

    setCentralWidget(m_centralWidget);

    setPalette(QPalette(DEFAULT_BACKGROUND_COLOR));

}


void IMainWindow::setMainWidget(QWidget* t_switcher)
{
    m_mainLayout->addWidget(t_switcher);
}

