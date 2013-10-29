#ifndef CUTEWRTDOWNLOADMANAGER_H
#define CUTEWRTDOWNLOADMANAGER_H

#include <QObject>
#include <QWebFrame>
#include <QDebug>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include <QDir>

class CuteWRTDownloadManager : public QObject
{
    Q_OBJECT
public:
    explicit CuteWRTDownloadManager(QObject *parent = 0);

signals:

private:
    QString source;
    QString localName;

public:
    QWebFrame* frame;
    QNetworkAccessManager* networkAccessManager;
    QNetworkReply* networkReply;

public slots:
    void download(QString src, QString name);
    void setWebFrame(QWebFrame* frame);
    void downloadFinished(QNetworkReply* reply);
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    int fileExists(QString file);    
    QString getBasepath(QString file);
    QString listDownloadedFiles();
};

#endif // CUTEWRTDOWNLOADMANAGER_H
