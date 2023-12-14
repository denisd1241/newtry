#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <qdebug.h>
#include <QDebug>
#include <QInputDialog>
#include <QCheckBox>
#include <QLabel>

bool check = false;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}

QVector<QVector<int>> MainWindow::genMatrix() {
    bool test;
    QCheckBox *check = ui->checkBox;

    // Очищаем предыдущее содержимое матрицы
    matrix.clear();

    srand(time(0));

    if (check->isChecked()) {
        int cols = QInputDialog::getInt(nullptr, "Размер матрицы", "Введите количество столбцов", 0, 1, 60, 1, &test);
        int rows = QInputDialog::getInt(nullptr, "Размер матрицы", "Введите количество строк", 0, 1, 60, 1, &test);

        // Устанавливаем размер матрицы
        matrix.resize(cols, QVector<int>(rows, 0));

        for (int i = 0; i < cols; ++i) {
            for (int j = 0; j < rows; ++j) {
                int randomValue = rand() % 2;
                matrix[i][j] = randomValue;
            }
        }
    } else {
        int cols = QInputDialog::getInt(nullptr, "Размер матрицы", "Введите размер матрицы", 0, 1, 60, 1, &test);
        int rows = cols;

        // Устанавливаем размер матрицы
        matrix.resize(cols, QVector<int>(rows, 0));

        // Заполнение матрицы случайными значениями 0 или 1
        for (int i = 0; i < cols; ++i) {
            for (int j = 0; j < rows; ++j) {
                int randomValue = rand() % 2;
                matrix[i][j] = randomValue;
            }
        }
    }

    return matrix;
}

void MainWindow::displayMatrix(const QVector<QVector<int>> &matrix) {
    // Очистим предыдущее содержимое GridLayout, если оно есть
    QLayoutItem *item;
    QGridLayout *gridLayout = ui->gridLayout;

    while ((item = gridLayout->takeAt(0)) != nullptr) {
    delete item->widget();
    delete item;
    }

    // Выведем новую матрицу в GridLayout
    for (int i = 0; i < matrix.size(); ++i) {
    for (int j = 0; j < matrix[i].size(); ++j) {
        QLabel *label = new QLabel(QString::number(matrix[i][j]));
        gridLayout->addWidget(label, i, j);
    }
    }
}

void MainWindow::on_genbutton_clicked()
{
    matrix = genMatrix();
    displayMatrix(matrix);
}






