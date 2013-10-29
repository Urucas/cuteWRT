#include "cutewrtdownloadmanager.h"

CuteWRTDownloadManager::CuteWRTDownloadManager(QObject *parent) :
    QObject(parent)
{
    if(!QDir("files").exists()) { QDir().mkdir("files"); }

    networkAccessManager = new QNetworkAccessManager(this);
    connect(networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(downloadFinished(QNetworkReply*)));
}

void CuteWRTDownloadManager::download(QString src, QString name)
{
    source = src;
    localName = name;
    networkReply = networkAccessManager->get(QNetworkRequest(QUrl(source)));
    connect(networkReply, SIGNAL(downloadProgress(qint64,qint64)), SLOT(downloadProgress(qint64,qint64)));

    frame->evaluateJavaScript("cuteWRT.downloadManager.onStateChangeStarted()");
}

QString CuteWRTDownloadManager::listDownloadedFiles()
{
    QDir dir("files");
    QStringList dirs = dir.entryList();

    QString json_response = "[";
    int len = dirs.length();
    for(int i = 0; i < len; i++) {
        QString file = dirs.at(i);
        if( file == "." || file == "..") continue;
        json_response += "\"" + file + "\"";
        json_response += i == len - 1 ? "" : ",";
    }
    json_response += "]";
    return json_response;
}

QString CuteWRTDownloadManager::getBasepath(QString file)
{
    QString basepath = QDir("files").absolutePath();
    QString path     = basepath + "/" + file;
    return path;
}

int CuteWRTDownloadManager::fileExists(QString file)
{
    return QFile::exists(getBasepath(file)) ? 1 : 0;
}

void CuteWRTDownloadManager::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    QString percent = QString::number(bytesReceived * 100 / bytesTotal);
    frame->evaluateJavaScript("cuteWRT.downloadManager.onStateChangeProgress(" + percent + ")");
}

void CuteWRTDownloadManager::downloadFinished(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        QFile file(getBasepath(localName));
        if (!file.open(QIODevice::WriteOnly)) {
            QString error = file.errorString();
            frame->evaluateJavaScript("cuteWRT.downloadManager.onStateChangeError('" + error + "')");
            return;
        }
        file.write(reply->readAll());
        file.close();
        frame->evaluateJavaScript("cuteWRT.downloadManager.onStateChangeFinished()");
    }
    else
    {
        QString error = reply->errorString();
        frame->evaluateJavaScript("cuteWRT.downloadManager.onStateChangeError('" + error + "')");
    }
}

void CuteWRTDownloadManager::setWebFrame(QWebFrame* frm)
{
    frame = frm;
}
