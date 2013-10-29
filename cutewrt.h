#ifndef CUTEWRT_H
#define CUTEWRT_H

#include <QObject>
#include <QDebug>
#include <QSettings>
#include <QWebFrame>
#include <QDesktopServices>
#include <QApplication>

#include <cutewrtaudioplayer.h>
#include <cutewrtdownloadmanager.h>
#include <cutewrtdatabasemanager.h>

class CuteWRT : public QObject
{
    Q_OBJECT
public:
    explicit CuteWRT(QObject *parent = 0);
    void setAppName(QString appName);
    void setWebFrame(QWebFrame *frame);

private:
    QString appName;
    QWidget* ui;
    QWebFrame* frame;   

private:
    CuteWRTAudioPlayer* audioPlayer;
    CuteWRTDownloadManager* downloadManager;
    CuteWRTDatabaseManager* databaseManager;

signals:

public slots:
    void setPreferenceForKey(QString key, QString value);
    QString getPreferenceForKey(QString key);

    void debug(QString str);

    void createAudioPlayer();
    void destroyAudioPlayer();

    void createDownloadManager();
    void destroyDownloadManager();

    void createDatabaseManager();
    void destroyDatabaseManager();

    void setDisplayPortrait();
    void setDisplayLandscape();

    void openURL(QString url);
    void close();
};

#endif // CUTEWRT_H
