#include "resourcepath.h"

resourcepath::resourcepath() {}

extern std::string resourcePath;
auto resourcepath::getResourcePath() -> QString{
    CFBundleRef mainBundle = CFBundleGetMainBundle();

    CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);

    char path[PATH_MAX];

    if (resourcesURL) {
        if (CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8*)path, PATH_MAX)) {
            CFRelease(resourcesURL);
            return QString(path) + "/";
        }
        CFRelease(resourcesURL);
    }
    return "";
}
