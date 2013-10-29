#ifndef CUTEWRTDATABASEMANAGER_H
#define CUTEWRTDATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QWebFrame>
#include <QDebug>
#include <QScriptEngine>
#include <QMap>
#include <QSqlQuery>
#include <QSqlError>

class CuteWRTDatabaseManager : public QObject
{
    Q_OBJECT
public:
    explicit CuteWRTDatabaseManager(QObject *parent = 0);

public:
    QWebFrame* frame;
    QSqlDatabase db;
    QString dbName;
    QString lastError;

public:
    void setWebFrame(QWebFrame * frm);
    int openDatabase(QString name);

signals:

public slots:
    QString showTables();
    QString getLastError();
    QString select(QString table, QString params);
    int tableExists(QString table);
    int createTable(QString table, QString fields);
};

#endif // CUTEWRTDATABASEMANAGER_H
