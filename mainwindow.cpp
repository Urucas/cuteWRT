#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "flickcharm.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->webView->load(QUrl("qrc:/resources/html/index.html"));
    ui->webView->page()->settings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls,true);

    // FlickCharm *flickCharm = new FlickCharm( this );
    // flickCharm->activateOn( ui->webView);
}

void MainWindow::on_webView_loadFinished(){

    // get Webkit main frame
    frame = ui->webView->page()->mainFrame();

    // add js event
    connect(frame,SIGNAL(javaScriptWindowObjectCleared()),this, SLOT(addJS()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addJS()
{    
    cuteWRT = new CuteWRT();
    cuteWRT->setAppName("CuteWRT_Example");
    cuteWRT->setWebFrame(frame);    
    frame->addToJavaScriptWindowObject("_cuteWRT", cuteWRT);
}
