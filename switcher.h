#pragma once

#include <QAbstractButton>
#include <QFrame>

QT_BEGIN_NAMESPACE
class QGridLayout;
class QLabel;
class QPixmap;
QT_END_NAMESPACE


class Circle : public QFrame
{
    Q_OBJECT

public:
    explicit Circle(QWidget* t_parent = nullptr);

    void animate();

    bool m_switchedOn = false;

signals:
    void toggled(bool);

public slots:
    void onToggled();
    void onChangeFrame();

protected:
    void paintEvent(QPaintEvent* t_event) override;
    void resizeEvent(QResizeEvent* t_event) override;

private:
    QColor m_switcherColor;
    QColor m_switchedOnColor;
    QColor m_switchedOffColor;

    QRect m_switcherRect;
    QRect m_switcherOnRect;
    QRect m_switcherOffRect;

    QPoint m_switchedOffPos;
    QPoint m_switchedOnPos;

};


class Switcher : public QAbstractButton
{
    Q_OBJECT

public:
    const static int WIDTH = 442;
    const static int HEIGHT = 240;
    const static int DIAMETER = 220;
    const static int SPACER = 10;
    const static int FONT_SIZE = 16;
    
    double static getAspectRatio() { return static_cast<double>(WIDTH) / HEIGHT; }
    double static getDiameterRatio() { return static_cast<double>(DIAMETER) / HEIGHT; }
    double static getSpacerRatio() { return static_cast<double>(SPACER) / HEIGHT; }
    double static getFontSizeRatio() { return static_cast<double>(FONT_SIZE) / HEIGHT; }

    explicit Switcher(QWidget* t_parent = nullptr);

signals:
    void changeFrame(bool t_swithedOn);

protected:
    virtual void resizeEvent(QResizeEvent* t_event) override;
    virtual void paintEvent(QPaintEvent* t_event) override;

private:
    QGridLayout* m_mainLayout;

    QColor m_switcherColor;
    QColor m_switchedOnColor;
    QColor m_switchedOffColor;
    QColor m_backgroundColor;

    QPixmap* m_circle = nullptr;
    Circle* m_circleSwitcher;

    QString m_fontFamily;
    QFont m_textFont;

};

