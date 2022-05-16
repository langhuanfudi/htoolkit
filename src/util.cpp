//
// Created by hxh on 2022/5/16.
//

#include "util.h"
#include <string>

#if defined(__APPLE__) || defined(__MACH__)

#include <limits.h>

int uv_exepath(char *buffer, int *size) {
    char abspath[PATH_MAX * 2 + 1];
    char exepath[PATH_MAX + 1];
    uint32_t exepath_size;
    size_t abspath_size;

    if (buffer == nullptr || size == nullptr || *size == 0)
        return -EINVAL;

    exepath_size = sizeof(exepath);

    

}

#endif // defined(__APPLE__) || defined(__MACH__)

namespace htoolkit {

    std::string exePath(bool isExe) {
        char buffer[PATH_MAX * 2 + 1] = {0};
        int n = -1;
#if defined(_WIN32)
        n = 0;
#elif defined(__MACH__) || defined(__APPLE__)
        n = sizeof(buffer);
        if (uv_exepath(buffer, n) != 0) {
            n = -1;
        }
#elif defined(__linux__)
        n = 0;
#endif
        std::string filePath;
        if (n <= 0)
            filePath = "./";
        else
            filePath = buffer;

#if defined(_WIN32)
        for (auto &ch: filePath){
            if (ch == '\\')
                ch = '/';
        }
#endif

        return filePath;
    }

    std::string exeName(bool isExe) {
        auto path = exePath(isExe);

    }

} // htoolkit
