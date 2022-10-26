#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_pbRHGenerate_clicked();

    void on_pbProcessMoves_clicked();

    void on_pbNW_clicked();

    void on_pbW_clicked();

    void on_pbSW_clicked();

    void on_pbNE_clicked();

    void on_pbE_clicked();

    void on_pbSE_clicked();

    void on_pbLastLocateGenerate_clicked();

    void on_pbRHGenerate_2_clicked();

    void on_pbtHGenerate_clicked();

    void on_pbRecenter_clicked();

    void on_lcdTravelTime_overflow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
