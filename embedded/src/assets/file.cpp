// #include <LITTLEFS.h>

// void writeFile(const char *path, const char *content)
// {
//     File file = LittleFS.open(path, FILE_WRITE);
//     if (!file)
//     {
//         Serial.println("Failed to open file for writing");
//         return;
//     }

//     if (file.print(content))
//     {
//         Serial.println("File written successfully");
//     }
//     else
//     {
//         Serial.println("Write failed");
//     }

//     file.close();
// }

// String readFile(const char *path)
// {
//     File file = LittleFS.open(path);
//     if (!file || file.isDirectory())
//     {
//         Serial.println("Failed to open file for reading");
//         return String();
//     }

//     String content;
//     while (file.available())
//     {
//         content += file.readStringUntil('\n');
//     }

//     file.close();
//     return content;
// }