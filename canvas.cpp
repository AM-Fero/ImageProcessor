#include "canvas.h"
canvas::canvas(QImage* temp) // Конструктор
{
    image=temp;
    buffer = image->copy();
    setWindowTitle("canvas");
    setFocusPolicy(Qt::StrongFocus);
}

void canvas::paintEvent(QPaintEvent *) // Отрисовка
{
    QPainter painter(this);
    QColor color(40,40,40,255);
    QBrush brush;
    brush.setColor(color);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    painter.drawRect(0,0,this->width(),this->height());
    painter.drawImage(offsetX,offsetY,buffer);
}

void canvas::saveImage(QImage &im) // Сохранить изображение
{
    calculateImage(im);
    QString ret = QFileDialog::getSaveFileName(this,"Save image","","*.png");
    if (ret=="")return;
    im.save(ret,"PNG");
}

void canvas::drawCanv() // Подготовка к отрисовке
{
    buffer = image->copy();
    calculateImage(buffer);
    repaint();
}

void canvas::calculateImage(QImage & inputImage) // Расчет значений пикселей изображения
{
    // типа нормализация значений но вообще не она
    double val = EXcoef/100.;
    double val2 = HLcoef/100.*pow(HLcoef/200.,2);
    double val3 = SHcoef/100.;
    double val4 = pow(CBcoef/100.,2);
    double val5 = pow(TIcoef/100.,2);

    // Ниже банальная реализация алгоритма свертки для эффекта blur, стоит заменить на иной алгоритм
    if (COcoef!=0) // при условии что нужен блюр
    {
        QImage temp = inputImage.copy();
        for(int i = 0; i < inputImage.height(); i++)
        {
            QRgb *line = reinterpret_cast<QRgb*>(inputImage.scanLine(i));
            for(int j = 0;  j< inputImage.width(); j++)
            {
                QRgb &rgb = line[j];
                QColor color(rgb);
                float redavg = 0;
                float greenavg = 0;
                float blueavg = 0;
                for (int k = -COcoef; k<COcoef; k++)
                {
                    if ((i+k)<0 || (i+k) > temp.height()-1)continue;

                    for (int m = -COcoef; m<COcoef; m++)
                    {
                        if ((j+m)<0 || (j+m) > temp.width()-1)continue;
                        redavg = redavg+temp.pixelColor(j+m,i+k).redF();
                        greenavg = greenavg+temp.pixelColor(j+m,i+k).greenF();
                        blueavg = blueavg+temp.pixelColor(j+m,i+k).blueF();
                    }
                }
                redavg = redavg/COcoef/COcoef/4;
                greenavg = greenavg/COcoef/COcoef/4;
                blueavg = blueavg/COcoef/COcoef/4;
                color.setRgbF(redavg,greenavg,blueavg);
                rgb = color.rgb();
            }
        }
    }

    float sum;
    float hlcoef;
    float Shcoef;
    // Ниже применение значений слайдеров к изображению
    for (int y = 0; y < inputImage.height(); y++)
    {
        QRgb *line = reinterpret_cast<QRgb*>(inputImage.scanLine(y));
        for (int x = 0; x < inputImage.width(); x++)
        {
            QRgb &rgb = line[x];
            QColor color(rgb);

            // Подбор функций преобразования был сделан "на глаз"
            color.setRedF(color.redF()*val4*val5);
            color.setGreenF(color.greenF()*val4*(1/val5));
            color.setBlueF(color.blueF()*(1/(val4)*(1/(val4)))*val5);

            color.setRgbF(color.redF()*val, color.greenF()*val, color.blueF()*val);

            sum = color.redF()+color.greenF()+color.blueF();
            hlcoef = ((pow((1.5*sum-1),3.)+1)*val2) + 1;
            color.setRgbF(color.redF()*hlcoef, color.greenF()*hlcoef, color.blueF()*hlcoef);

            sum = color.redF()+color.greenF()+color.blueF();
            Shcoef = ((1/(5*sum))*val3)+1;
            color.setRgbF(color.redF()*Shcoef, color.greenF()*Shcoef, color.blueF()*Shcoef);

            rgb = color.rgb();
        }
    }
}

void canvas::EXChange(int input) // Изменение экспозиции
{
    EXcoef=input;
    drawCanv();
}

void canvas::HLChange(int input) // Изменение светлых областей
{
    HLcoef = input;
    drawCanv();
}

void canvas::SHChange(int input) // Изменение теней
{
    SHcoef=input;
    drawCanv();
}

void canvas::COChange(int input) // Изменение блюра
{
    COcoef = input;
    drawCanv();
}

void canvas::CBChange(int input) // Изменение температуры
{
    CBcoef = input;
    drawCanv();
}

void canvas::TIChange(int input) // Изменение оттенка
{
    TIcoef = input;
    drawCanv();
}

void canvas::keyPressEvent(QKeyEvent *e) // Навигация по холсту через WASD
{
    if (e->key()==Qt::Key_W)offsetY = offsetY+10;
    if (e->key()==Qt::Key_A)offsetX = offsetX+10;
    if (e->key()==Qt::Key_S)offsetY = offsetY-10;
    if (e->key()==Qt::Key_D)offsetX = offsetX-10;
    repaint();
}
