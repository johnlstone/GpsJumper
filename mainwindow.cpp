#include "mainwindow.h"
#include "./ui_mainwindow.h"
# include <QTime>
# include <QTimer>
# include <QProcess>
#include <QClipboard>
# include <QThread>
#include <QGeoCoordinate>


QTimer* objTimer;

QTime*  objTime;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

QString getCommandline(QGeoCoordinate loc,QString dur,QString eph)
{
    QString path =("./gps-sdr-sim -l "+
                                   QString::number( loc.latitude())+","+
                                    QString::number( loc.longitude())+
                                   ",100 "+
                                   "-b 8 -d "+
                                   (dur)+
                                   " -e "+
                                    eph+
                                   "");

    QClipboard* clipboard = QApplication::clipboard();

    clipboard->setText(path, QClipboard::Clipboard);

    if (clipboard->supportsSelection()) {
        clipboard->setText(path, QClipboard::Selection);
    }

    QThread::msleep(1); //workaround for copied text not being available...

    return path;
}
void MainWindow::on_pbRHGenerate_clicked()
{
    QGeoCoordinate rh = QGeoCoordinate( ui->tbRHLatitude->text().toDouble(),
                                      ui->tbRHLongitude->text().toDouble());
   QString du =  ui->tbDefualtDuration->text();
   QString ep =  ui->tbEphemeris->text();
   getCommandline(rh,du,ep);
   ui->tbLastLatitude->setText(QString::number(rh.latitude()));
   ui->tbLastLongitude->setText(QString::number(rh.longitude()));
   ui->tbTHLatitude->setText(QString::number(rh.latitude()));
   ui->tbTHLongitude->setText(QString::number(rh.longitude()));
}

void MainWindow::on_pbProcessMoves_clicked() {
  int p;
  int azi;
  QListWidgetItem *mMove;
  QGeoCoordinate newCoordinate =
      QGeoCoordinate(ui->tbTHLatitude->text().toDouble(),
                     ui->tbTHLongitude->text().toDouble(), 100.0);

  for (int i = 0; i < ui->lstMoves->count(); ++i) {
      azi = 0;
    mMove = ui->lstMoves->item(i);
    QString dir = mMove->text();
    ui->tbDisplay->insertPlainText(mMove->text() + "-> ");

    if (newCoordinate.isValid()){
      //
      newCoordinate.setLongitude(newCoordinate.longitude());
    newCoordinate.setLatitude(newCoordinate.latitude());
    newCoordinate.setAltitude(100.0);
    }

    if (dir=="NE"){ azi = 30;};
    if (dir=="E"){ azi = 90;};
    if (dir=="SE"){ azi = 150;};
    if (dir=="SW"){ azi = 210;};
    if (dir=="W"){ azi = 270;};
    if (dir=="NW"){ azi = 330;};



    QGeoCoordinate newCoor = newCoordinate.atDistanceAndAzimuth(50, azi);

    ui->tbDisplay->insertPlainText(
        QString::number( azi )+ "deg " +
        QString::number(newCoor.latitude()) + " " +
        QString::number(newCoor.longitude()) + "\n"
       );
    ui->tbLastLatitude->setText(QString::number(newCoor.latitude()));
    ui->tbLastLongitude->setText(QString::number(newCoor.longitude()));
    newCoordinate = newCoor;
  }
  QGeoCoordinate lo = newCoordinate;
  QString dur = ui->tbDefualtDuration->text();
  QString ep = ui->tbEphemeris->text();
  QString jk = getCommandline(lo,dur,ep);

  QGeoCoordinate TH= QGeoCoordinate(ui->tbTHLatitude->text().toDouble(),ui->tbTHLongitude->text().toDouble());
  int dist = newCoordinate.distanceTo(TH);
  int sec = (dist /25) ;//sec at 25mps 55mph

  ui->tbDistTempHome->setText(QString::number( dist));
  ui->lcdTravelTime->display(sec);


}

void MainWindow::on_pbNW_clicked()
{
    ui->lstMoves->addItem("NW");

}


void MainWindow::on_pbW_clicked()
{
     ui->lstMoves->addItem("W");
}


void MainWindow::on_pbSW_clicked()
{
     ui->lstMoves->addItem("SW");
}


void MainWindow::on_pbNE_clicked()
{
     ui->lstMoves->addItem("NE");
}


void MainWindow::on_pbE_clicked()
{
     ui->lstMoves->addItem("E");
}


void MainWindow::on_pbSE_clicked()
{
     ui->lstMoves->addItem("SE");
}


void MainWindow::on_pbLastLocateGenerate_clicked()
{
    QGeoCoordinate rh = QGeoCoordinate( ui->tbLastLatitude->text().toDouble(),
                                      ui->tbLastLongitude->text().toDouble());
   QString du =  ui->tbDefualtDuration->text();
   QString ep =  ui->tbEphemeris->text();
   getCommandline(rh,du,ep);


}


void MainWindow::on_pbtHGenerate_clicked()
{
    QGeoCoordinate rh = QGeoCoordinate( ui->tbTHLatitude->text().toDouble(),
                                      ui->tbTHLongitude->text().toDouble());
   QString du =  ui->tbDefualtDuration->text();
   QString ep =  ui->tbEphemeris->text();
   getCommandline(rh,du,ep);
}


void MainWindow::on_pbRecenter_clicked()
{
     ui->tbTHLatitude->setText(  ui->tbLastLatitude->text());
     ui->tbTHLongitude->setText(  ui->tbLastLongitude->text());
}


void MainWindow::on_pbRHGenerate_2_clicked()
{

}


void MainWindow::on_lcdTravelTime_overflow()
{
    ui->lcdTravelTime->display(4567);
}

