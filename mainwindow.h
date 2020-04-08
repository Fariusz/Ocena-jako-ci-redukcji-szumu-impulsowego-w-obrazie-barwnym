#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QFileDialog>
#include <QImage>
#include <ctime>
#include <cstdlib>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnWczytaj_clicked();

    void on_btnWczytaj2_clicked();

    void on_btnWczytaj3_clicked();

    void on_btnMapuj_clicked();

    void on_btnZaszum_clicked();

    void on_btnEstymuj_clicked();

private:
    Ui::MainWindow *ui;
    QImage czysty, zaszumiony, odfiltrowany, mapaOrg, mapaEst;
};

#endif // MAINWINDOW_H
