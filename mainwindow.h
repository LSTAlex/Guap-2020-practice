#ifndef MAINWINDOW_H
#define MAINWINDOW_H 
#include <QMainWindow>
#include <QImage>
#include <QGraphicsScene>
#include <QPixmap> 
namespace Ui {
    class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
private slots:
    void on_btLoad_clicked();
    void on_btProcess_clicked();
private:
    Ui::MainWindow* ui;
    // исходное изображение и сцена для размещения
    QImage* image;
    QGraphicsScene* scene;
    // результат (обработанное изображение)
    QImage* result_image;
    QGraphicsScene* result_scene;
};
#endif // MAINWINDOW_H