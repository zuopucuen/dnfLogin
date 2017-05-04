#ifndef UTIL_H
#define UTIL_H
#include "windows.h"
#include <QString>

bool processExistsByName(LPCTSTR findProcessName);
QString getMacAddr();
bool changeHostFile();

#endif // UTIL_H
