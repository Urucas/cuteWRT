#include <QApplication>
#include <QBoxLayout>
#include <QWidget>
#include <QUrl>
#include <QtGui/QtGui>
#include <QWidget>
//#include <QAbstractKineticScroller>



#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("RadioComm");
    MainWindow w;

    #if defined(Q_WS_S60)
        //w.showMaximized();
        w.showFullScreen();

        // jajaja set portrait orientation
        /*CAknAppUi* appUi = dynamic_cast<CAknAppUi*>( CEikonEnv::Static()->AppUi() );
        if(appUi)
        {
            TRAP_IGNORE( appUi->SetOrientationL( CAknAppUi::EAppUiOrientationPortrait ) );
        }
        */

    #else
        w.show();
    #endif

    return a.exec();

}
