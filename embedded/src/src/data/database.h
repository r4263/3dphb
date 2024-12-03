#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <ArduinoJson.h>
#include <src/data/data.h>
#include <src/data/queries/config.h>

#define filesystem APPLICATION_STATE.filesystem

#define DATABASE_ABSOLUTE_PATH "/littlefs/dev-config.db"
#define DATABASE_RELATIVE_PATH "/dev-config.db"
#define JOURNAL_RELATIVE_PATH "/dev-config.db-journal"

extern void initDatabase(void);
extern void stopDatabase(void);

extern String queryDatabase(const char *sql, bool expectResult);

#endif