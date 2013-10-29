#include "cutewrt.h"

CuteWRT::CuteWRT(QObject *parent) :
    QObject(parent)
{
}

void CuteWRT::setAppName(QString name)
{
    appName = name;
}

void CuteWRT::setWebFrame(QWebFrame* frm)
{
    frame = frm;
}

void CuteWRT::setPreferenceForKey(QString key, QString value)
{
    QSettings settings("cuteWRT", appName);
              settings.setValue(key, value);
}

void CuteWRT::setDisplayPortrait()
{
    #if defined(Q_WS_S60)
    CAknAppUi* appUi = dynamic_cast<CAknAppUi*>( CEikonEnv::Static()->AppUi() );
    if(appUi)
    {
        TRAP_IGNORE( appUi->SetOrientationL( CAknAppUi::EAppUiOrientationPortrait ) );
    }
    #endif
}

void CuteWRT::setDisplayLandscape()
{
    #if defined(Q_WS_S60)
    CAknAppUi* appUi = dynamic_cast<CAknAppUi*>( CEikonEnv::Static()->AppUi() );
    if(appUi)
    {
        TRAP_IGNORE( appUi->SetOrientationL( CAknAppUi::EAppUiOrientationLandscape ) );
    }
    #endif
}

void CuteWRT::openURL(QString url)
{
    QUrl webURL(url);
    QDesktopServices::openUrl(webURL);
}

void CuteWRT::close()
{
    QApplication::closeAllWindows();
}

QString CuteWRT::getPreferenceForKey(QString key)
{
    QSettings settings("cuteWRT", appName);
       return settings.value(key).toString();
}

void CuteWRT::debug(QString str)
{
    qDebug() << str;
}

void CuteWRT::createAudioPlayer()
{
    audioPlayer = new CuteWRTAudioPlayer();
    audioPlayer->setWebFrame(frame);
    frame->addToJavaScriptWindowObject("_cuteWRTAudioPlayer", audioPlayer);
}

void CuteWRT::destroyAudioPlayer()
{
    delete audioPlayer;
}

void CuteWRT::createDownloadManager()
{
    downloadManager = new CuteWRTDownloadManager();
    downloadManager->setWebFrame(frame);
    frame->addToJavaScriptWindowObject("_cuteWRTDownloadManager", downloadManager);
}

void CuteWRT::destroyDownloadManager()
{
    delete downloadManager;
}

void CuteWRT::createDatabaseManager()
{
    databaseManager = new CuteWRTDatabaseManager();
    databaseManager->setWebFrame(frame);
    databaseManager->openDatabase(appName);
    frame->addToJavaScriptWindowObject("_cuteWRTDatabaseManager", databaseManager);
}

void CuteWRT::destroyDatabaseManager()
{
    delete databaseManager;
}
