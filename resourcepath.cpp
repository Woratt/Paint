#include "resourcepath.h"

resourcepath::resourcepath() = default;

auto resourcepath::getResourcePath() -> QString
{
    CFBundleRef mainBundle = CFBundleGetMainBundle();

    CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);

    char path[PATH_MAX];

    if (resourcesURL != nullptr)
    {
        if (CFURLGetFileSystemRepresentation(resourcesURL, TRUE, reinterpret_cast<UInt8 *>(path), PATH_MAX) != 0u)
        {
            CFRelease(resourcesURL);
            return QString(path) + "/";
        }
        CFRelease(resourcesURL);
    }
    return "";
}
