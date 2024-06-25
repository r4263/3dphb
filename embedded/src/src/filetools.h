#include <Arduino.h>
#include <LittleFS.h>
#include <src/data.h>

status FS_STAT;

bool initFS()
{
    LittleFS.end();

    FS_STAT.STATUS = LittleFS.begin();
    FS_STAT.ERR = !FS_STAT.STATUS ? "Could not initialize LittleFS Filesystem." : "OK";

    return FS_STAT.STATUS;
}

void writeFile(const char *path, const char *content)
{
    File file = LittleFS.open(path, FILE_WRITE);

    FS_STAT.STATUS = file;

    if (!FS_STAT.STATUS)
    {
        FS_STAT.STATUS = "Failed to open file for writing";
        return;
    }

    FS_STAT.STATUS = file.print(content);

    if (!FS_STAT.STATUS)
    {
        FS_STAT.ERR = "Could not write contents to file";
    }

    file.close();
}

String readFile(const char *path)
{

    FS_STAT.CLEAR();

    File file = LittleFS.open(path);
    if (!file || file.isDirectory())
    {
        FS_STAT.STATUS = false;
        FS_STAT.ERR = file.isDirectory() ? "The specified path is a folder and the content could not be written." : "Failed to open file for reading.";
        return String();
    }

    String content;
    while (file.available())
    {
        content += file.readStringUntil('\n');
    }

    file.close();
    return content;
}
