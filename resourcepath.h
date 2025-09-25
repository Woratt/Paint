#ifndef RESOURCEPATH_H
#define RESOURCEPATH_H

#include <QString>

#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#endif

class resourcepath
{
  public:
    resourcepath();
    static auto getResourcePath() -> QString;
};

#endif // RESOURCEPATH_H
