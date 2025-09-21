#ifndef RESOURCEPATH_H
#define RESOURCEPATH_H

#include <QString>

#include <CoreFoundation/CoreFoundation.h>

class resourcepath
{
  public:
    resourcepath();
    auto static getResourcePath() -> QString;
};

#endif // RESOURCEPATH_H
