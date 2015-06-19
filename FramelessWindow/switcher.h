#pragma once

#include <QAbstractButton>
#include <QFrame>
#include "utils.h"

QT_BEGIN_NAMESPACE
class QGridLayout;
class QLabel;
class QPixmap;
QT_END_NAMESPACE


class Circle;
class Capsule;

class Switcher : public QAbstractButton
{
    Q_OBJECT

public:
    const static int WIDTH{ 442 };
    const static int HEIGHT{ 240 };
    const static int DIAMETER{ 220 };
    const static int SPACER{ 10 };
    const static int FONT_SIZE{ 16 };
    const static int ANIMATION_DURATION{ 450 }; //msec
    const static QColor SWITCHER_COLOR;
    const static QColor TEXT_COLOR;
    const static QColor SWITCHED_ON_COLOR;
    const static QColor SWITCHED_OFF_COLOR;
    
    double static getAspectRatio() { return static_cast<double>(WIDTH) / HEIGHT; }
    double static getDiameterRatio() { return static_cast<double>(DIAMETER) / HEIGHT; }
    double static getSpacerRatio() { return static_cast<double>(SPACER) / HEIGHT; }

    explicit Switcher(QWidget* t_parent = nullptr);

    static bool switchedOn() { return m_switchedOn; }
    static void toogle() { m_switchedOn = !m_switchedOn; }

signals:
    void toggled(bool t_swithedOn);

protected:
    virtual void resizeEvent(QResizeEvent* t_event) override;
    virtual void paintEvent(QPaintEvent* /*t_event*/) override {}

private:
    QGridLayout* m_mainLayout;

    QPixmap* m_circle = nullptr;
    Capsule* m_capsule;

private:
    static bool m_switchedOn;
};



class Capsule : public QFrame
{
    Q_OBJECT
        Q_PROPERTY(QColor color MEMBER m_color)

public:
    explicit Capsule(QWidget* t_parent = nullptr);

    void animate();

signals:
    void toggled(bool);

    public slots:
    void onToggled();

protected:
    void paintEvent(QPaintEvent* t_event) override;

private:
    QFont m_textFont{ Utils::instance().font(Switcher::FONT_SIZE) };
    QColor m_color{ Switcher::SWITCHED_OFF_COLOR };
    Circle* m_circle;

};



class Circle : public QFrame
{
    Q_OBJECT

public:
    explicit Circle(QWidget* t_parent = nullptr);

    void animate();

signals:
    void toggled(bool);

protected:
    void paintEvent(QPaintEvent* t_event) override;

};

