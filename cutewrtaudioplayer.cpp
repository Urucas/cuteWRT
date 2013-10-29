#include "cutewrtaudioplayer.h"

CuteWRTAudioPlayer::CuteWRTAudioPlayer(QObject *parent) :
    QObject(parent)
{
    audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
    mediaObject = new Phonon::MediaObject(this);
    Phonon::createPath(mediaObject, audioOutput);
    connect(mediaObject, SIGNAL(stateChanged(Phonon::State,Phonon::State)), this, SLOT(stateChange()));
}

void CuteWRTAudioPlayer::stateChange()
{
    switch(mediaObject->state())
    {
        case Phonon::LoadingState:
            frame->evaluateJavaScript("cuteWRT.audioPlayer.onStateChangeLoading();");
            break;
        case Phonon::StoppedState:
            frame->evaluateJavaScript("cuteWRT.audioPlayer.onStateChangeStopped();");
            break;
        case Phonon::PlayingState:
            frame->evaluateJavaScript("cuteWRT.audioPlayer.onStateChangePlaying();");
            break;
        case Phonon::BufferingState:
            frame->evaluateJavaScript("cuteWRT.audioPlayer.onStateChangeBuffering();");
            break;
        case Phonon::PausedState:
            frame->evaluateJavaScript("cuteWRT.audioPlayer.onStateChangePaused();");
            break;
        case Phonon::ErrorState:
            QString error = mediaObject->errorString();
            qDebug() << error;
            frame->evaluateJavaScript("cuteWRT.audioPlayer.onStateChangeError('" + error + "');");
            break;
    }
}

void CuteWRTAudioPlayer::setWebFrame(QWebFrame* frm)
{
    frame = frm;
}

void CuteWRTAudioPlayer::setSource(QString src)
{
    source = src;
    mediaObject->setCurrentSource(QUrl(source));
    mediaObject->play();
}

QString CuteWRTAudioPlayer::getSource()
{
    return source;
}

QString CuteWRTAudioPlayer::getState()
{    
}

void CuteWRTAudioPlayer::play()
{
    mediaObject->play();
}

void CuteWRTAudioPlayer::stop()
{
    mediaObject->stop();
}

void CuteWRTAudioPlayer::pause()
{
    mediaObject->pause();
}

void CuteWRTAudioPlayer::mute()
{
}

void CuteWRTAudioPlayer::volDown()
{
}

void CuteWRTAudioPlayer::volUp()
{
}
