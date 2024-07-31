#ifndef CONSTANTS_H
#define CONSTANTS_H

#define CONFIGPATH "/config.json"

#define FS_INIT_OK "Filesystem init sequence OK."
#define FS_INIT_LFS_ERR "LittleFS filesystem could not be initialized."
#define FS_FILE_OPEN_ERR "Failed to open the file."
#define FS_FILE_WRITE_ERR "Could not write contents to file."
#define FS_FILE_IS_A_DIRECTORY_ERR "The specified path is a folder and the content could not be written."
#define OK "OK."

#define HTTP_STATUS_OK 200
#define HTTP_STATUS_BAD_REQUEST 400
#define HTTP_STATUS_UNAUTHORIZED 401 // unauthenticated
#define HTTP_STATUS_FORBIDDEN 403    // known by the server, recuse to fullfill the request
#define HTTP_STATUS_NOT_FOUND 404
#define HTTP_STATUS_METHOD_NOT_ALLOWED 405
#define HTTP_STATUS_NOT_ACCEPTABLE 406
#define HTTP_STATUS_TIMEOUT 408
#define HTTP_STATUS_INTERNAL_SERVER_ERROR 500
#define HTTP_STATUS_NOT_IMPLEMENTED 501
#define HTTP_STATUS_SERVICE_UNAVAILABLE 503

#endif