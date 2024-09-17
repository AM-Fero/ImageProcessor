#ifndef CANVAS_H
#define CANVAS_H
#pragma once
#include <QPaintEvent>
#include <QWidget>
#include <QPainter>
#include <QImage>
#include <QDebug>
#include "math.h"
#include <QFileDialog>

class canvas:public QWidget
{
    Q_OBJECT

public:
    canvas(QImage*);
    void paintEvent(QPaintEvent*);
    QImage* image;
    QImage buffer;
    int offsetX=0;
    int offsetY=0;

public slots:
    void drawCanv();                // Подготовка к отрисовке изображения

    void calculateImage(QImage&);   // Рассчет значений пикселей изображения

    void saveImage(QImage&);        // Сохранение изображения

    void EXChange(int);             // При изменении значения exposure

    void HLChange(int);             // При изменении значения highlights

    void SHChange(int);             // При изменении значения shadows

    void CBChange(int);             // При изменении значения temperature

    void TIChange(int);             // При изменении значения tint

    void COChange(int);             // При изменении значения blur

    void keyPressEvent(QKeyEvent*e);// Для навигации по холсту чз WASD

private:
    int EXcoef=100;
    int HLcoef=0;
    int SHcoef=0;
    int COcoef=0;
    int CBcoef=100;
    int TIcoef=100;
};

#endif // CANVAS_H
