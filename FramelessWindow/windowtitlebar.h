#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLabel;
class QPixmap;
QT_END_NAMESPACE


class WindowButton;

class WindowTitleBar : public QWidget
{
    Q_OBJECT

public:
    const static int HEIGHT = 41;
    const static int BOTTOM_LINE_WIDTH = 1;

    WindowTitleBar(QWidget *parent = nullptr);

signals:
    void maximizeClicked();
    void minimizeClicked();
    void quitClicked();
    void iconClicked();

public slots:
    void setTitle(const QString& t_title);
    void onWindowMaximized(bool t_maximized);

protected:
    void resizeEvent(QResizeEvent* t_event) override;
    void paintEvent(QPaintEvent* t_event) override;

private:

    QPixmap* m_cache;
    QLabel* m_title;
    WindowButton* m_icon;
    WindowButton* m_minimize;
    WindowButton* m_maximize;
    WindowButton* m_close;

};

