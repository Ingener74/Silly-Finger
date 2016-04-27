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

    virtual void showEvent(QShowEvent *);
    virtual void closeEvent(QCloseEvent *);
    virtual void keyPressEvent(QKeyEvent *);

private:
    LifeWidget* m_life = nullptr;
    QTimer* m_timer = nullptr;
public slots:
};
