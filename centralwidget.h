#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLabel;
class QVBoxLayout;
QT_END_NAMESPACE

class Switcher;

class CentralWidget : public QWidget
{
    Q_OBJECT

public:
    CentralWidget(QWidget* t_parent = nullptr);

signals:
    void changeFrame(bool t_switchedOn);

protected:

private:
    void styleCaptionLabel();

    QVBoxLayout* m_mainLayout;
    Switcher* m_switcher;
    QLabel* m_captionLabel;
    QString m_fontFamily;

};
