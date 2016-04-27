#pragma once

#include <vector>

#include <QtWidgets/QWidget>

class LifeWidget: public QWidget {
    Q_OBJECT
public:
    LifeWidget(QWidget* parent = 0, Qt::WindowFlags f = 0);
    virtual ~LifeWidget();

    virtual void mouseMoveEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void paintEvent(QPaintEvent *);

public slots:
    void iterate();
    void randomize();

    int randomCount() const {
        return m_randomCount;
    }
    void setRandomCount(int randomCount) {
        m_randomCount = randomCount;
    }

    int getCols() const {
        return m_cols;
    }

    void setCols(int cols = 40);

    int getRows() const {
        return m_rows;
    }

    void setRows(int rows = 40);

private:
    int m_randomCount = 20 * 20;

    int m_x = -1; int m_y = -1;

    int m_rows = 40, m_cols = 40, m_side = 10;
    std::vector<std::vector<int>> m_world;

    void resizeAndClear(std::vector<std::vector<int>>& world, int rows, int cols);
    int getNeighbors(const std::vector<std::vector<int>>& world, int rows, int cols, int row, int col);
};
