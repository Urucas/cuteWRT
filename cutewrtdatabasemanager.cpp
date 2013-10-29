#include "cutewrtdatabasemanager.h"

CuteWRTDatabaseManager::CuteWRTDatabaseManager(QObject *parent) :
    QObject(parent)
{
    qDebug() << "new CuteWRTDatabaseManager instance";
}

int CuteWRTDatabaseManager::openDatabase(QString name)
{
    dbName = name + ".sqlite";
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);
    return db.open() ? 1 : 0;
}

QString CuteWRTDatabaseManager::showTables()
{
    QStringList tables = db.tables();
    QString json_response = "[";
    int len = tables.length();
    for(int i = 0; i < len; i++)
    {
        QString table = tables.at(i);
        json_response += "\"" + table + "\"";
        json_response += i == len - 1 ? "," : "";
    }
    json_response += "]";
    return json_response;
}

int CuteWRTDatabaseManager::tableExists(QString table)
{
    QStringList tables = db.tables();
    int len = tables.length();
    for(int i = 0; i < len; i++)
    {
        if(table == tables.at(i)) return 1;
    }
    return 0;
}

int CuteWRTDatabaseManager::createTable(QString table, QString fields)
{
    QString query;
    query = "CREATE TABLE IF NOT EXISTS " + table;
    query+= "(";

    QScriptValue sc;
    QScriptEngine engine;
    sc = engine.evaluate("(" + fields + ")");

    QVariant vFields = sc.toVariant();
    QVariantList list = vFields.toList();
    int len = list.length();
    if(len)
    {
        for(int i = 0; i < len; i++)
        {
            QVariant field = list.at(i);
            QMap<QString, QVariant> map = field.toMap();
            if(!map.contains("field") && map.value("field").toString() != "")
            {
                continue;
            }
            if(!map.contains("type") && map.value("type").toString() != "")
            {
                continue;
            }
            query += map.value("field").toString() + " ";
            query += map.value("type").toString();

            if(map.contains("primary_key") && map.value("primary_key").toBool())
            {
                query += " PRIMARY KEY";
                if(map.contains("auto_increment") && map.value("auto_increment").toBool())
                {
                    query += " AUTOINCREMENT";
                }
            }
            else if(map.contains("unique") && map.value("unique").toBool())
            {
                query += " UNIQUE";
            }

            if(map.contains("not_null") && map.value("not_null").toBool())
            {
                query += " NOT NULL";
            }

            if(map.contains("default") && map.value("default")!= "")
            {
                query += " DEFAULT ";
                query += map.value("type").toString() == "integer" ? map.value("default").toString() : "\"" + map.value("default").toString() + "\"";
            }
            query += i == len - 1 ? "" : ", ";
        }
    }
    query+= ");";
    QSqlQuery db_query(db);
    if(db_query.exec(query)) return 1;

    lastError = db_query.lastError().text();
    return 0;
}

QString CuteWRTDatabaseManager::select(QString table, QString params)
{
    QString json_response;
    json_response = "[";

    QScriptValue sc;
    QScriptEngine engine;
    sc = engine.evaluate("(" + params + ")");

    QVariant vParams = sc.toVariant();

    QString query;
    query = "SELECT ";

    QMap<QString, QVariant> param = vParams.toMap();
    if(param.contains("fields"))
    {
        QVariantList fields = param.value("fields").toList();
        int len = fields.length();
        if(len)
        {
            for(int i = 0; i < len; i++)
            {
                QString field = fields.at(i).toString();
                query+= field;
                query+= i == len - 1 ? " " : ", ";
            }
        }
        else
        {
            query+= "ALL ";
        }
    }
    else
    {
        query+= "ALL ";
    }
    query+= "FROM " + table;

    if(param.contains("where") && param.value("where").toString() != "")
    {
        query+= " WHERE " + param.value("where").toString();
    }
    if(param.contains("order") && param.value("order").toString() != "")
    {
    }
    qDebug() << query;

    json_response+= "]";
    return json_response;
}

QString CuteWRTDatabaseManager::getLastError()
{
    return lastError;
}

void CuteWRTDatabaseManager::setWebFrame(QWebFrame* frm)
{
    frame = frm;
}
