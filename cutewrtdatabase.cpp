#include "cutewrtdatabase.h"

CuteWRTDatabase::CuteWRTDatabase(QObject *parent) :
    QObject(parent)
{    
}

void CuteWRTDatabase::connectDatabase(QString dbName)
{
}

void CuteWRTDatabase::setWebFrame(QWebFrame* frm)
{
    frame = frm;
}
