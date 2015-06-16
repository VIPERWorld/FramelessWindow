#pragma once

#include <QWidget>
#include <QPoint>

QT_BEGIN_NAMESPACE
class QMenu;
class QLabel;
class QPixmap;
class QAction;
QT_END_NAMESPACE


class WindowButton;

class WindowTitleBar : public QWidget
{
    Q_OBJECT

public:
    const static int HEIGHT = 41;
    const static int BOTTOM_LINE_WIDTH = 1;

    WindowTitleBar(QWidget *parent = nullptr);

    void setTitle(const QString& t_title);

signals:
    void maximize(bool t_maximized);

public slots:
    void updateWindowTitle();
    void minimized();
    void maximized();
    void quit();
    void showSystemContextMenu();

protected:
    void resizeEvent(QResizeEvent* t_event) override;
    void paintEvent(QPaintEvent* t_event) override;
    void mousePressEvent(QMouseEvent* t_event) override;
    void mouseReleaseEvent(QMouseEvent* t_event) override;
    void mouseMoveEvent(QMouseEvent* t_event) override;

private:
    void createActions();
    void getContextMenu(QMenu& t_menu);
    void showContextMenu(const QPoint& t_pos);

    QPixmap* m_cache;
    QLabel* m_title;
    WindowButton* m_minimize;
    WindowButton* m_maximize;
    WindowButton* m_close;
    WindowButton* m_icon;
    QPoint m_windowDragStartPos;

    QAction* m_restoreAction;
    QAction* m_minimizeAction;
    QAction* m_maximizeAction;
    QAction* m_closeAction;

};

