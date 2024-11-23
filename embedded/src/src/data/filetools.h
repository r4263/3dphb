#ifndef FILETOOLS_H
#define FILETOOLS_H

#include <Arduino.h>
#include <LittleFS.h>
#include <src/data/macros.h>
#include <src/data/identifiers.h>
#include <src/data/data.h>

extern void initFS();
extern void writeFile(const char *path, const char *content);
extern String readFile(const char *path);

#endif