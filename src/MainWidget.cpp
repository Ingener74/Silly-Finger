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

    bugsSpinBox->setValue(m_life->randomCount());
    connect(bugsSpinBox, SIGNAL(valueChanged(int)), m_life, SLOT(setRandomCount(int)));

    rowsSpinBox->setValue(m_life->getRows());
    connect(rowsSpinBox, SIGNAL(valueChanged(int)), m_life, SLOT(setRows(int)));

    colsSpinBox->setValue(m_life->getCols());
    connect(colsSpinBox, SIGNAL(valueChanged(int)), m_life, SLOT(setCols(int)));

    connect(randomizePushButton, SIGNAL(clicked()), m_life, SLOT(randomize()));

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), m_life, SLOT(iterate()));

    m_speed = 500;
    speedHorizontalSlider->setValue(m_speed);
    m_timer->start(m_speed);
    speedValue(m_speed);

    connect(speedHorizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(speedValue(int)));
    connect(speedHorizontalSlider, SIGNAL(sliderReleased()), this, SLOT(speedReleased()));
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

void MainWidget::speedValue(int speed) {
    m_speed = speed;
    speedGroupBox->setTitle(QString("Скорость: ") + QString::number(m_speed));
}

void MainWidget::speedReleased() {
    m_timer->start(m_speed);
}
