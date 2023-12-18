#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <qdebug.h>
#include <QDebug>
#include <QInputDialog>
#include <QCheckBox>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <cmath>

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
    int cols = QInputDialog::getInt(nullptr, "Размер матрицы", "Введите размер матрицы", 0, 1, 60, 1, &test);
    int rows = cols;

    if (check->isChecked()) {
        // Устанавливаем размер матрицы
        matrix.resize(rows, QVector<int>(rows, 0));
        for (int i = 0; i < cols; ++i) {
            for (int j = 0; j < rows; ++j) {
                int randomValue = rand() % 2;
                matrix[i][j] = randomValue;
            }
        }
    } else {
        // Устанавливаем размер матрицы
        matrix.resize(cols, QVector<int>(rows, 0));
        // Заполнение матрицы случайными значениями 0 или 1
        for (int i = 0; i < cols; ++i) {
            for (int j = 0; j < rows; ++j) {
                matrix[i][j] = rand() % 2;
                matrix[j][i] = matrix[i][j];
            }
        }
    }
    return matrix;
}
QVector<QVector<int>> MainWindow::weightMatrix(const QVector<QVector<int>> &matrix){
    int cols = matrix.size();
    int rows = cols;
    weight = QVector<QVector<int>>(cols, QVector<int>(rows, 0));
    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < rows; ++j) {
            if(matrix[i][j] == 1){
               weight[i][j] = (rand() % 20) - 10;
            }
            //proverka
            if(matrix[i][j] == 0){
               weight[i][j] = 0;
            }
        }
    }


    qDebug() << "Contents of weight:" << weight;
    return weight;
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
    weightMatrix(matrix);
}






