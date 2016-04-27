#pragma once

#include <memory>

#include <QtWidgets/QWidget>
#include <QtCore/QFutureWatcher>
#include <QtGui/QImage>

#include "ui_mainwidget.h"

class LifeWidget;

class MainWidget: public QWidget, public Ui_MainWidget {
    Q_OBJECT
public:
    MainWidget(QWidget* parent = 0, Qt::WindowFlags f = 0);
    virtual ~MainWidget();

    virtual void keyPressEvent(QKeyEvent *);

private:
    LifeWidget* m_life = nullptr;
    QTimer* m_timer = nullptr;
    int m_speed = 0;

public slots:
    void speedValue(int speed);
    void speedReleased();
};
