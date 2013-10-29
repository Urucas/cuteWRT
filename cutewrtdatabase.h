#ifndef CUTEWRTDATABASE_H
#define CUTEWRTDATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QWebFrame>

class CuteWRTDatabase : public QObject
{
    Q_OBJECT
public:
    explicit CuteWRTDatabase(QObject *parent = 0);

signals:

public:
    QSqlDatabase *db;
    QWebFrame *frame;

public slots:
    void connectDatabase(QString dbName);
    void setWebFrame(QWebFrame* frm);

};

#endif // CUTEWRTDATABASE_H
