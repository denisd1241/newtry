#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <qdebug.h>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_genbutton_clicked();
    QVector<QVector<int>> genMatrix();
    void displayMatrix(const QVector<QVector<int>> &matrix);
    QVector<QVector<int>> weightMatrix(const QVector<QVector<int>> &matrix);

private:
    Ui::MainWindow *ui;
    QVector<QVector<int>> matrix;
    QVector<QVector<int>> weight;
};
#endif // MAINWINDOW_H
