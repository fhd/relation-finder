#include <iostream>
#include "options.hpp"
#include "util.hpp"

boost::mutex message_mutex;
bool Util::verbose = false;

void Util::message(const std::string& s)
{
    if (verbose) {
        boost::mutex::scoped_lock lock(message_mutex);
        std::cout << s << std::endl;
    }
}

boost::filesystem::path Util::bin_dir()
{
    boost::filesystem::path path;

#if defined(_WIN32)
#include <windows.h>
    char buf[1024];
    DWORD ret = GetModuleFileName(NULL, buf, sizeof(buf));
    if (ret != 0 && ret != sizeof(buf))
        path = buf;
#elif defined(__APPLE__)  // Not tested
#include <mach-o/dyld.h>
    char buf[1024];
    uint32_t size = sizeof(buf);
    int ret = _NSGetExecutablePath(buf, &size);
    if (ret == 0)
        path = buf;
#elif defined(sun) || defined(__sun) // Not tested
#include <stdlib.h>
    path = getexecname();
#elif defined(__FreeBSD__)
#include <sys/sysctl.h>
    int mib[4];
    mib[0] = CTL_KERN;
    mib[1] = KERN_PROC;
    mib[2] = KERN_PROC_PATHNAME;
    mib[3] = -1;
    char buf[1024];
    size_t size = sizeof(buf);
    sysctl(mib, 4, buf, &size, NULL, 0);
    if (size != 0 && size != sizeof(buf))
        path = std::string(buf, size);
#elif defined(__linux__)
#include <unistd.h>
    char buf[1024];
    ssize_t ret = readlink("/proc/self/exe", buf, sizeof(buf));
    if (ret != 0 && ret != sizeof(buf))
        path = std::string(buf, ret);
#else
    message("Unsupported operating system; unable to determine the \
binary path. Trying with current working directory ...");
#endif

    return path.branch_path();
}
