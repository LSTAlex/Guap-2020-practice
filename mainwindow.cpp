#include "mainwindow.h"
#include <QApplication> 
int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
Файл mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h" 
#include <QFileDialog>
#include <QDebug>
#include <QtMath> 
MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // создаем сцену и настраиваем просмотрщик (визуальное отображение сцены)
    scene = new QGraphicsScene(this);
    ui->viewer->setScene(scene);
    result_scene = new QGraphicsScene(this);
    ui->result_viewer->setScene(result_scene);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_btLoad_clicked()
{
    // Диалог выбора изображения для обработки
    QString file_path = QFileDialog::getOpenFileName(nullptr, "Select image",
        "", "*.jpeg *.jpg *.png *.bmp");
    // Загрузка изображения
    image = new QImage();
    image->load(file_path);
    // Добавление изображения на сцену
    scene->clear();
    scene->addPixmap(QPixmap::fromImage(*image));
}
void MainWindow::on_btProcess_clicked()
{
    // создаем новое изображение 
    result_image = new QImage(*image);
    // im - указатель для работы с изображением (для удобства)
    QImage* im = result_image;
    // определяем минимальную и максимальную интенсивность цвета пикселей
    qreal min_e = 255, max_e = 0;
    for (int x = 0; x < im->width(); x++)
    {
        for (int y = 0; y < im->height(); y++)
        {
            QColor color = im->pixelColor(x, y);
            int r = color.red();
            int g = color.green();
            int b = color.blue();
            qreal e = qSqrt((r * r + g * g + b * b) / 3);
            if (e < min_e)
                min_e = e;
            if (e > max_e)
                max_e = e;
        }
    }
    // разбиваем изображение по интенсивности цвета на 3 группы,
    // которые закрашиваем красным (темные участки), зеленым (средние) и
    синим цветом(яркие)
        for (int x = 0; x < im->width(); x++)
        {
            for (int y = 0; y < im->height(); y++)
            {
                // определяем цвет пикселя с координатами (x,y)
                QColor color = im->pixelColor(x, y);
                // получаем все три компоненты цвета
                int r = color.red();
                int g = color.green();
                int b = color.blue();
                qreal e = qSqrt((r * r + g * g + b * b) / 3);
                qreal p1 = (min_e + max_e) / 3;
                qreal p2 = 2 * (min_e + max_e) / 3;
                // перекрашиваем в зависимости от яркости пиксела
                if (e < p1) {
                    im->setPixelColor(x, y, QColor(100, 0, 0));
                }
                else if (e > p2) {
                    im->setPixelColor(x, y, QColor(0, 100, 0));
                }
                else {
                    im->setPixelColor(x, y, QColor(0, 0, 100));
                }
            }
        }
    // Добавление изображения на сцену
    result_scene->clear();
    result_scene->addPixmap(QPixmap::fromImage(*result_image));
}