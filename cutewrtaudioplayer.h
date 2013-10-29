#ifndef CUTEWRTAUDIOPLAYER_H
#define CUTEWRTAUDIOPLAYER_H

#include <QObject>
#include <Phonon>
#include <QUrl>
#include <QDebug>
#include <QWebFrame>

class CuteWRTAudioPlayer : public QObject
{
    Q_OBJECT
public:
    explicit CuteWRTAudioPlayer(QObject *parent = 0);

public:
    Phonon::AudioOutput *audioOutput;
    Phonon::MediaObject *mediaObject;
    QString source;
    QWebFrame* frame;

signals:

public slots:
    void setSource(QString source);
    void setWebFrame(QWebFrame* frame);
    void play();
    void stop();
    void pause();
    void mute();
    void volDown();
    void volUp();
    QString getSource();
    QString getState();
    void stateChange();

};

#endif // CUTEWRTAUDIOPLAYER_H
