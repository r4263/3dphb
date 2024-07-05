#include <src/filetools.h>

status FS_STAT;

bool initFS()
{
    LittleFS.end();

    FS_STAT.STATUS = LittleFS.begin();
    FS_STAT.ERR = !FS_STAT.STATUS ? FS_INIT_LFS_ERR : OK;

    return FS_STAT.STATUS;
}

void writeFile(const char *path, const char *content)
{
    File file = LittleFS.open(path, FILE_WRITE);

    FS_STAT.STATUS = file;

    if (!FS_STAT.STATUS)
    {
        FS_STAT.STATUS = FS_FILE_OPEN_ERR;
        return;
    }

    FS_STAT.STATUS = file.print(content);

    if (!FS_STAT.STATUS)
    {
        FS_STAT.ERR = FS_FILE_WRITE_ERR;
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
        FS_STAT.ERR = file.isDirectory() ? FS_FILE_IS_A_DIRECTORY_ERR : FS_FILE_WRITE_ERR;
        return String();
    }

    String content;
    while (file.available())
    {
        content += char(file.read());
    }

    file.close();
    return content;
}