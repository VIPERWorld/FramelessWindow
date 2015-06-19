#pragma once

#include "abstractmainwindow.h"


class WindowTitleBar;

class FramelessWindow : public AbstractMainWindow
{
    Q_OBJECT

public:
    explicit FramelessWindow(QWidget* t_parent = nullptr);

    QRect getNormalGeometry() const override;
    void setMainWidget(QWidget* t_centralWidget) override;

signals:
    void windowMaximized(bool t_maximized);

public slots:
    void onFrameSizeDetected(int t_bottomBorder, int t_topBorder);
    void switchNormalMaximize();
    void minimize();
    void showSystemContextMenu();

protected:
    void resizeEvent(QResizeEvent* t_event) override;
    void mousePressEvent(QMouseEvent* t_event) override;
    void mouseDoubleClickEvent(QMouseEvent* t_event) override;
    void mouseReleaseEvent(QMouseEvent* t_event) override;
    void mouseMoveEvent(QMouseEvent* t_event) override;
    
private:
    void setupConnects();
    void createActions();
    void getContextMenu(QMenu& t_menu);
    void showContextMenu(const QPoint& t_pos);

    WindowTitleBar* m_titleBar;

    int m_bottomFrame = 0;
    int m_topFrame = 0;

    QPoint m_windowDragStartPos;

    QAction* m_restoreAction;
    QAction* m_minimizeAction;
    QAction* m_maximizeAction;
    QAction* m_closeAction;

};

