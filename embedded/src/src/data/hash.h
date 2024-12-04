#ifndef HASH_H
#define HASH_H

#include <Arduino.h>
#include "mbedtls/md.h"

String generateSHA256(const String &input);

#endif