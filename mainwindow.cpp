#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) // Конструктор
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    flickButtons(false);
    this->setFocusPolicy(Qt::StrongFocus);
    setWindowTitle("Lightroom v2");
    initializeSliders();
}

MainWindow::~MainWindow() // Деструктор
{
    if (canv!=nullptr) delete canv;
    delete ui;
}

void MainWindow::on_pbOpen_clicked() // Открытие картинки
{
    QString ret = QFileDialog::getOpenFileName(this,"Open image","","*.png *.jpg");
    if (ret=="")return;

    mainImage.load(ret);
    copyImage = mainImage.copy();
    initialW = mainImage.width();
    initialH = mainImage.height();

    createCanvas();
    initializeSliders();

    connect(ui->SlidExp, SIGNAL(valueChanged(int)), canv, SLOT(EXChange(int)));
    connect(ui->SlidHl, SIGNAL(valueChanged(int)), canv, SLOT(HLChange(int)));
    connect(ui->SlidSh, SIGNAL(valueChanged(int)), canv, SLOT(SHChange(int)));
    connect(ui->SlidTp, SIGNAL(valueChanged(int)), canv, SLOT(CBChange(int)));
    connect(ui->SlidTi, SIGNAL(valueChanged(int)), canv, SLOT(TIChange(int)));
    connect(ui->SlidBl, SIGNAL(valueChanged(int)), canv, SLOT(COChange(int)));

    flickButtons(true);
}

void MainWindow::on_pbZoomIn_clicked() // Приблизить
{
    coef = coef*1.25;
    mainImage = copyImage.scaled(int(initialW*coef),int(initialH*coef),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    canv->drawCanv();
}

void MainWindow::on_pbZoomOut_clicked() // Отдалить
{
    coef = coef/1.25;
    mainImage = copyImage.scaled(int(initialW*coef),int(initialH*coef),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    canv->drawCanv();
}

void MainWindow::keyPressEvent(QKeyEvent *e) // Сдвинуть холст
{
    if (canv!=nullptr){
        bool canvasMoved=false;
        if (e->key()==Qt::Key_W||e->key()==1062){canv->offsetY = canv->offsetY+10; canvasMoved=true;}
        if (e->key()==Qt::Key_A||e->key()==1060){canv->offsetX = canv->offsetX+10; canvasMoved=true;}
        if (e->key()==Qt::Key_S||e->key()==1067){canv->offsetY = canv->offsetY-10; canvasMoved=true;}
        if (e->key()==Qt::Key_D||e->key()==1042){canv->offsetX = canv->offsetX-10; canvasMoved=true;}
        if(canvasMoved)canv->repaint();
    }
}

bool MainWindow::eventFilter(QObject *object, QEvent *event) // Двойное нажатие на слайдер
{
    if (canv!=nullptr){
        bool sliderReset=false;
        if (object == ui->SlidExp && event->type() == QEvent::MouseButtonDblClick){ui->SlidExp->setValue(100); sliderReset=true;}
        if (object == ui->SlidHl && event->type() == QEvent::MouseButtonDblClick){ui->SlidHl->setValue(0); sliderReset=true;}
        if (object == ui->SlidSh && event->type() == QEvent::MouseButtonDblClick){ui->SlidSh->setValue(0); sliderReset=true;}
        if (object == ui->SlidTp && event->type() == QEvent::MouseButtonDblClick){ui->SlidTp->setValue(0); sliderReset=true;}
        if (object == ui->SlidTi && event->type() == QEvent::MouseButtonDblClick){ui->SlidTi->setValue(100); sliderReset=true;}
        if (object == ui->SlidBl && event->type() == QEvent::MouseButtonDblClick){ui->SlidBl->setValue(100); sliderReset=true;}
        if(sliderReset)canv->repaint();
    }
    return false;
}

void MainWindow::on_pbSave_clicked() // Сохранить картинку
{
    canv->saveImage(copyImage);
}

void MainWindow::initializeSlider(QSlider *slider, int min, int max, int val) // Настроить начальное состояние слайдера
{
    slider->setMinimum(min);
    slider->setMaximum(max);
    slider->setValue(val);
    slider->installEventFilter(this);
}

void MainWindow::initializeSliders() // Задать начальное состояние для всех слайдеров
{
    initializeSlider(ui->SlidExp, 0, 500, 100);
    initializeSlider(ui->SlidHl, -30, 125, 0);
    initializeSlider(ui->SlidSh, -150, 150, 0);
    initializeSlider(ui->SlidTp, 70, 130, 100);
    initializeSlider(ui->SlidTi, 80, 120, 100);
    initializeSlider(ui->SlidBl, 0, 10, 0);
}

void MainWindow::createCanvas() // Создать холст
{
    canv = new canvas(&mainImage);
    canv->setGeometry(100,100,1000,600);
    canv->show();
    canv->repaint();
}

void MainWindow::flickButtons(bool isImageOpened) // Переключить кнопки для управления картинкой
{
    ui->pbOpen->setEnabled(!isImageOpened);
    ui->pbSave->setEnabled(isImageOpened);
    ui->pbZoomIn->setEnabled(isImageOpened);
    ui->pbZoomOut->setEnabled(isImageOpened);
}
