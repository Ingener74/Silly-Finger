#include <iostream>

#include <QtGui/QKeyEvent>
#include <QtCore/QTimer>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>

#include "LifeWidget.h"
#include "MainWidget.h"

using namespace std;

MainWidget::MainWidget(QWidget* parent, Qt::WindowFlags f) :
    QWidget(parent, f) {
    setupUi(this);
    m_life = new LifeWidget();
    paintLayout->addWidget(m_life);

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), m_life, SLOT(iterate()));
    m_timer->start(500);
}

MainWidget::~MainWidget() {
    delete m_life;
    delete m_timer;
}

void MainWidget::closeEvent(QCloseEvent*) {
}

void MainWidget::showEvent(QShowEvent*) {
}

void MainWidget::keyPressEvent(QKeyEvent* e) {
    if (e->key() == Qt::Key_Escape) {
        close();
    }
}
