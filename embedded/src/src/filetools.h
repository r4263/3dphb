#ifndef FILETOOLS_H
#define FILETOOLS_H

#include <Arduino.h>
#include <LittleFS.h>
#include <src/definitions.h>
#include <src/constants.h>

bool initFS();
void writeFile(const char *path, const char *content);
String readFile(const char *path);

#endif