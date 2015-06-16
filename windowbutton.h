#pragma once

#include <QPushButton>

QT_BEGIN_NAMESPACE
class QPixmap;
QT_END_NAMESPACE


class WindowButton : public QPushButton
{
	Q_OBJECT

public:
	enum class Type { Minimize, Maximize, Close, Icon };

	WindowButton(Type t_type, QWidget* t_parent = nullptr);

public slots:
    void onWindowMaximized(bool t_maximize);

protected:
	void resizeEvent(QResizeEvent* t_event) override;
	void paintEvent(QPaintEvent* t_event) override;
	void enterEvent(QEvent* t_event) override;
	void leaveEvent(QEvent* t_event) override;
	void mousePressEvent(QMouseEvent* t_event) override;
	void mouseReleaseEvent(QMouseEvent* t_event) override;

private:
	enum class State { Normal, Hovered, Clicked };

	Type m_type;
	State m_state = State::Normal;
	QPixmap* m_normal = nullptr;
	QPixmap* m_hovered = nullptr;
	QPixmap* m_clicked = nullptr;
    bool m_maximized = false;

    void initButton(const QPixmap& t_icon) const;
    void initIcon(const QPixmap& t_icon);
    void initPixmaps();
	void initPixmap(QPixmap** t_pixmap) const;

};

