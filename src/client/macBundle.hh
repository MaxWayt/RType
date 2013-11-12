#ifndef _MACBUNDLE_H_
# define _MACBUNDLE_H_

# include <iostream>
# ifdef __APPLE__
#  include <CoreFoundation/CFBundle.h>
# endif

class macBundlePath {
    
public:
    macBundlePath() {
# ifdef __APPLE__
        CFBundleRef mainBundle = CFBundleGetMainBundle();
        CFURLRef resourcesURL = CFBundleCopyBundleURL(mainBundle);
        CFStringRef str = CFURLCopyFileSystemPath(resourcesURL, kCFURLPOSIXPathStyle);
        CFRelease(resourcesURL);
        char path[PATH_MAX];

        CFStringGetCString(str, path, FILENAME_MAX, kCFStringEncodingASCII);
        CFRelease(str);
        _path = (std::string(path) + "/Contents/");
# else
        _path = "";
# endif
    }
    
    ~macBundlePath() = default;
    
    std::string getPath() { return _path; }
    
private:
    std::string _path;
    
    
};
#endif /* _MACBUNDLE_H_ */
