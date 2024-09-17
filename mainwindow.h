#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QImage>
#include <canvas.h>
#include <QKeyEvent>
#include <QSlider>

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
    void on_pbOpen_clicked();                           // (кнопка) Открытие изображения

    void on_pbZoomIn_clicked();                         // (кнопка) Приблизить изображение

    void on_pbZoomOut_clicked();                        // (кнопка) Отдалить изображение

    void keyPressEvent(QKeyEvent*e);                    // Для навигации с помощью WASD

    bool eventFilter(QObject *object, QEvent *event);   // Для перехвата двойного клика

    void on_pbSave_clicked();                           // (кнопка) Сохранить изображение

    void initializeSlider(QSlider* slider, int min,     // Задать начальное состояние для слайдера
                          int max, int val);

    void initializeSliders();                           // Задать начальное состояние для всех слайдеров

    void createCanvas();                                // Создать холст

    void flickButtons(bool isImageOpened);              // Переключатель для кнопок
                                                        //               - сохранения
                                                        //               - открытия
                                                        //               - приближения
                                                        //               - отдаления

private:
    Ui::MainWindow *ui;
    QImage mainImage;
    QImage copyImage;
    canvas *canv=nullptr;
    double coef = 1;
    int initialW=0;
    int initialH=0;
};
#endif // MAINWINDOW_H
