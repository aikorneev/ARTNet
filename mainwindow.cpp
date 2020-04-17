#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    image_pixels = NULL;
    input = -1;
    ARTnet = NULL;

}

MainWindow::~MainWindow()
{
    delete ui;
    if (image_pixels!=NULL)
    {
        free(image_pixels);
    }
}


void MainWindow::on_pushButton_clicked()
{
    QString bmppath = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.bmp");
    if (bmppath != "")
    {
        QImage pic(bmppath);
        ui->label_bmp->setPixmap(QPixmap::fromImage(pic.scaled(300, 300,Qt::KeepAspectRatio)));

        if (image_pixels!=NULL)
        {
            free(image_pixels);
        }

        width = pic.width();
        height = pic.height();
        image_pixels = (double*) malloc(sizeof(double)*width*height);
        if(image_pixels == NULL)
        {
            qDebug() << "Memory allocating error";
            exit(1);
        }
        qDebug() << width << height << pic.format();
        input = width*height;
        for(int i = 0; i < width; i++)
           for(int j = 0; j < height; j++)
           {
               if(pic.pixel(i,j) == 4294967295)
                   image_pixels[j*width+i] = 0;
               else
                   image_pixels[j*width+i] = 1;
           }
        qDebug() << "pixels";
        ui->pushButton_2->setEnabled(true);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if (ARTnet == NULL)
    {
        ARTnet = new net(input);
    }
    QString info = "";
    ARTnet->new_input(image_pixels, input, &info);
    ARTnet->get_info(&info);
    ui->textBrowser->append(info);

    ui->pushButton_3->setEnabled(true);
    ui->pushButton_4->setEnabled(true);
    ui->label_pat_name->setText("pattern 1");
    set_pattern(1);
    ui->pushButton_4->setEnabled(false);
}

void MainWindow::set_pattern(int index)
{
    if (ARTnet->compare->neuron_count <= index)
    {
        qDebug() << "bad index to set pattern";
        return;
    }
    QImage pic(width, height, QImage::Format_RGB32);
    for(int i = 0; i < width; i++)
       for(int j = 0; j < height; j++)
       {
           if(ARTnet->compare->neurons[index]->vector[j*width+i] == 0)
               pic.setPixel(i,j, QColor(255,255,255).rgb());
           else
               pic.setPixel(i,j, QColor(0,0,0).rgb());
       }
    ui->label_pat_name->setText("pattern #"+QString::number(index));
    ui->label_patterns->setPixmap(QPixmap::fromImage(pic.scaled(300, 300,Qt::KeepAspectRatio)));
    current_index = index;
}

void MainWindow::on_pushButton_3_clicked()
{
    set_pattern(current_index+1);
    ui->pushButton_4->setEnabled(true);
}

void MainWindow::on_pushButton_4_clicked()
{
    if (current_index == 2) ui->pushButton_4->setEnabled(false);
    set_pattern(current_index-1);
    ui->pushButton_3->setEnabled(true);

}
