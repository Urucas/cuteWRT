#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebFrame>
#include <cutewrt.h>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    Ui::MainWindow *ui;
    QWebFrame* frame;
    CuteWRT* cuteWRT;

public slots:
    void on_webView_loadFinished();
    void addJS();
};

#endif // MAINWINDOW_H
