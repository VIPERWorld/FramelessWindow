#include <QtWidgets>
#include <QSize>

#include "imainwindow.h"
#include "switcher.h"

IMainWindow::IMainWindow(const QSize &t_size, QWidget* t_parent)
    : QMainWindow(t_parent),
    m_centralWidget(new QWidget(this)),
    m_mainLayout(new QGridLayout(m_centralWidget))
{
    resize(t_size);
    setCentralWidget(m_centralWidget);

    QPalette p(palette());
    p.setColor(QPalette::Background, QColor(Qt::white));
    setPalette(p);

    setContentsMargins(0, 0, 0, 0);
    layout()->setContentsMargins(0, 0, 0, 0);

    m_mainLayout->setMargin(0);
    m_mainLayout->setSpacing(0);
}


void IMainWindow::setMainWidget(QWidget* t_switcher)
{
    m_mainLayout->addWidget(t_switcher);
}
