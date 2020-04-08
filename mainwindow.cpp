#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnWczytaj_clicked()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this, "Open File", "", "Images (*.bmp *.jpg *.png)");

    if (QString::compare(fileName, ""))
    {
        czysty.load(fileName);

        int imageWidth = ui->image->width();

        ui->image->setPixmap(QPixmap::fromImage((czysty.scaledToWidth(imageWidth))));

    }

}

void MainWindow::on_btnWczytaj2_clicked()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this, "Open File", "", "Images (*.bmp *.jpg *.png)");

    if (QString::compare(fileName, ""))
    {
        zaszumiony.load(fileName);

        int imageWidth = ui->image->width();


        ui->image2->setPixmap(QPixmap::fromImage((zaszumiony.scaledToWidth(imageWidth))));

    }
}

void MainWindow::on_btnWczytaj3_clicked()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this, "Open File", "", "Images (*.bmp *.jpg *.png)");

    if (QString::compare(fileName, ""))
    {
        odfiltrowany.load(fileName);

        int imageWidth = ui->image->width();


        ui->image3->setPixmap(QPixmap::fromImage((odfiltrowany.scaledToWidth(imageWidth))));

    }
}

void MainWindow::on_btnMapuj_clicked()
{
    mapaOrg=czysty; //kopia obrazka zamiast konstruktora nowego obiektu
    int width = czysty.width();
    int height = czysty.height();
    int imageWidth = ui->image4->width();

    //Wypelnienie czarnymi pikselami
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            mapaOrg.setPixel(col,row,qRgb(0,0,0));
        }
    }

    //Porownane oryginalu z zaszumionym i stworzenie mapy szumow
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            if(!(zaszumiony.pixelColor(col,row)==czysty.pixelColor(col,row)))
            {
                //qInfo() << "szum: " << col << row; //debugowanie, wypisuje wspolrzedne na ktorych wykrywa szum
                mapaOrg.setPixel(col,row,qRgb(255,255,255)); //ustawienie bialych pikseli w miejscu szumow
            }

        }
        ui->image4->setPixmap(QPixmap::fromImage((mapaOrg.scaledToWidth(imageWidth)))); // wyrzucenie obiektu qimage na ramke
    }
}

void MainWindow::on_btnZaszum_clicked()
{
    zaszumiony= czysty;
    int width = zaszumiony.width();
    int height = zaszumiony.height();
    int imageWidth = ui->image->width();

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            int chance = rand() % 100;

            if (chance < 50) {
                int red = rand() % 256;
                int green = rand() % 256;
                int blue = rand() % 256;

                zaszumiony.setPixel(col, row, qRgb(red, green, blue));
            }
        }
    }

    ui->image2->setPixmap(QPixmap::fromImage((zaszumiony.scaledToWidth(imageWidth))));
}

void MainWindow::on_btnEstymuj_clicked()
{
    mapaEst=czysty;
    int width = czysty.width();
    int height = czysty.height();
    int imageWidth = ui->image5->width();

    //Wypelnienie czarnymi pikselami
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            mapaEst.setPixel(col,row,qRgb(0,0,0));
        }
    }

    //Porownanie czystego i odfiltrwanego
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            //Sprawdzenie w miejscu zniszczonych pikseli
            if(mapaOrg.pixelColor(col,row)==qRgb(255,255,255))
            {
                if(!(odfiltrowany.pixelColor(col,row)==czysty.pixelColor(col,row)))
                {
                 mapaEst.setPixel(col,row,qRgb(255,255,255)); //ustawienie bialych pikseli w miejscu szumow
                }
            }

        }
        ui->image5->setPixmap(QPixmap::fromImage((mapaEst.scaledToWidth(imageWidth)))); // wyrzucenie obiektu qimage na ramke
    }
}
