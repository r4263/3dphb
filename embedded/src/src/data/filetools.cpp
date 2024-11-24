#include <src/data/filetools.h>

#define filesystem APPLICATION_STATE.filesystem

bool checkFilesystem(fs::LittleFSFS fs)
{
    bool state;
    SEMAPHORE_WRAPPER(fileSystemMutex, {
        state = fs.exists("/");
    });

    return state;
}

void initFS()
{
    bool fsState;

    if (!checkFilesystem(filesystem))
    {
        SEMAPHORE_WRAPPER(fileSystemMutex, {
            filesystem.begin();
        });
    }
}

void writeFile(const char *path, const char *content)
{
    SEMAPHORE_WRAPPER(fileSystemMutex, {
        File file = filesystem.open(path, FILE_WRITE);

        if (!file)
            return;

        file.print(content);

        file.close();
    });
}

String readFile(const char *path)
{
    String content;

    SEMAPHORE_WRAPPER(fileSystemMutex, {
        File file = filesystem.open(path);

        if (!file || file.isDirectory())
        {
            content = "";
        }

        while (file.available())
        {
            content += char(file.read());
        }

        file.close();
    });

    return content;
}