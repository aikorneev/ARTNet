#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "net.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    net* ARTnet;
    int input;
    int height;
    int width;
    int current_index;
    double *image_pixels;
private:
    void set_pattern(int index);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
