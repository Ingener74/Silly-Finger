#include <iostream>

#include <QtGui/QPainter>
#include <QtGui/QBrush>
#include <QtGui/QPen>
#include <QtGui/QMouseEvent>
#include "LifeWidget.h"

using namespace std;

LifeWidget::LifeWidget(QWidget* parent, Qt::WindowFlags f) {
    setMinimumSize(m_side * m_cols + 1, m_side * m_rows + 1);
    resizeAndClear(m_world, m_rows, m_cols);
    randomize();
}

LifeWidget::~LifeWidget() {
}

void LifeWidget::mouseMoveEvent(QMouseEvent* e) {
    m_x = e->x();
    m_y = e->y();
    repaint();
}

void LifeWidget::mouseReleaseEvent(QMouseEvent* e) {
    if (m_x > 0 && m_x < m_side * m_cols && m_y > 0 && m_y < m_side * m_rows && m_side > 0){
        m_world[m_y / m_side][m_x / m_side] = 1;
        m_y = -1;
        m_x = -1;
    }
}

void LifeWidget::paintEvent(QPaintEvent*) {
    QPainter painter { this };

    QBrush empty { QColor { 255, 255, 255 } };
    QBrush alive { QColor { 30, 30, 30 } };
    QBrush select { QColor { 30, 255, 30 } };
    QPen pen { QColor { 0, 0, 0 } };

    for (int row = 0; row < m_rows; ++row) {
        for (int col = 0; col < m_cols; ++col) {
            if (m_side * col <= m_x && m_x < (m_side * col + m_side) &&
                m_side * row <= m_y && m_y < (m_side * row + m_side)) {
                painter.setBrush(select);
                painter.drawRect(col * m_side, row * m_side, m_side, m_side);
            }else{
                painter.setBrush(m_world[row][col] == 0 ? empty : alive);
                painter.drawRect(col * m_side, row * m_side, m_side, m_side);
            }
        }
    }
}

void LifeWidget::iterate() {
    vector<vector<int>> world;

    resizeAndClear(world, m_rows, m_cols);

    for (int row = 0; row < m_rows; ++row) {
        for (int col = 0; col < m_cols; ++col) {

            int neighbors = getNeighbors(m_world, m_rows, m_cols, row, col);

            if (m_world[row][col] == 0 && neighbors == 3) {
                world[row][col] = 1;
            } else if (m_world[row][col] == 1 && (neighbors == 2 || neighbors == 3)) {
                world[row][col] = 1;
            } else {
                world[row][col] = 0;
            }
        }
    }

    for (int row = 0; row < m_rows; ++row)
        for (int col = 0; col < m_cols; ++col)
            m_world[row][col] = world[row][col];

    repaint();
}

void LifeWidget::randomize() {
    for (int i = 0; i < m_randomCount; /*++i*/) {
		int random_row = static_cast<int>((m_rows - 1) * (rand() / double(RAND_MAX)));
		int random_col = static_cast<int>((m_cols - 1) * (rand() / double(RAND_MAX)));
        if (m_world[random_row][random_col] == 0) {
            m_world[random_row][random_col] = 1;
            ++i;
        }
    }
}

void LifeWidget::setCols(int cols) {
    m_cols = cols;
    setMinimumSize(m_side * m_cols + 1, m_side * m_rows + 1);
    resizeAndClear(m_world, m_rows, m_cols);
    randomize();
}

void LifeWidget::setRows(int rows) {
    m_rows = rows;
    setMinimumSize(m_side * m_cols + 1, m_side * m_rows + 1);
    resizeAndClear(m_world, m_rows, m_cols);
    randomize();
}

void LifeWidget::resizeAndClear(vector<vector<int> >& world, int rows, int cols) {
    world.resize(rows);
    for (auto& i : world)
        i.resize(cols);

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            world[row][col] = 0;
        }
    }
}

int offset[8][2]{
    { 0,  1},
    { 1,  1},
    { 1,  0},
    { 1, -1},

    { 0, -1},
    {-1, -1},
    {-1,  0},
    {-1,  1},
};

int LifeWidget::getNeighbors(const vector<vector<int>>& world, int rows, int cols, int row, int col) {
    int neighbors = 0;
    for (int o = 0; o < 8; ++o) {
        int r = row + offset[o][0];
        int c = col + offset[o][1];

        r = r >= rows ? 0 : r < 0 ? rows - 1 : r;
        c = c >= cols ? 0 : c < 0 ? cols - 1 : c;

        neighbors += world[r][c];
    }
    return neighbors;
}

