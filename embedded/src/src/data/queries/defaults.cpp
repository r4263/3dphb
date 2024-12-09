#include <src/data/queries/defaults.h>

void updateDatabase(String field, String data)
{
    queryDatabase(("UPDATE configs SET " + field + " = " + data + ";").c_str(), false);
}