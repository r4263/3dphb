#include <src/data/database.h>

char *zErrMsg = 0;
const char *data = "Callback function called";

sqlite3 *db1;
int rc;

JsonDocument doc;

static int callback(void *data, int argc, char **argv, char **azColName)
{
    JsonObject row = doc.createNestedObject();

    for (int i = 0; i < argc; i++)
    {
        if (argv[i] != NULL)
        {
            row[azColName[i]] = argv[i];
        }
        else
        {
            row[azColName[i]] = "NULL";
        }
    }

    return 0;
}

int db_open(const char *filename, sqlite3 **db)
{
    int rc = sqlite3_open(filename, db);
    if (rc)
    {
        Serial.printf("Can't open database: %s\n", sqlite3_errmsg(*db));
        return rc;
    }
    return rc;
}

int db_exec(sqlite3 *db, const char *sql)
{
    int rc = sqlite3_exec(db, sql, callback, (void *)data, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        Serial.printf("SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    return rc;
}

void initDatabase()
{
    sqlite3_initialize();

    if (!filesystem.exists(DATABASE_RELATIVE_PATH))
    {
        sqlite3 *tempDb;
        if (sqlite3_open(DATABASE_ABSOLUTE_PATH, &tempDb) != SQLITE_OK)
        {
            Serial.printf("Failed to create database: %s\n", sqlite3_errmsg(tempDb));
            sqlite3_close(tempDb);
            return;
        }

        rc = db_exec(tempDb, createConfigTableQuery);
        if (rc != SQLITE_OK)
        {
            sqlite3_close(tempDb);
            return;
        }

        rc = db_exec(tempDb, insertDefaultData);
        if (rc != SQLITE_OK)
        {
            sqlite3_close(tempDb);
            return;
        }

        sqlite3_close(tempDb);
    }

    if (db_open(DATABASE_ABSOLUTE_PATH, &db1))
    {
        return;
    }
}

void stopDatabase()
{
    sqlite3_close(db1);
}

String queryDatabase(const char *sql, bool expectResult)
{
    doc.clear();
    rc = db_exec(db1, sql);

    if (rc == SQLITE_OK)
    {
        if (expectResult)
        {
            String output;
            serializeJsonPretty(doc, output);

            return output;
        }
        else
        {
            Serial.printf("Query executed successfully, %d rows affected.\n", sqlite3_changes(db1));
        }
        return "success";
    }
    else
    {
        Serial.printf("Error executing query: %s\n", sqlite3_errmsg(db1));
        return sqlite3_errmsg(db1);
    }
}