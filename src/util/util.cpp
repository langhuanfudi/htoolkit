//
// Created by hxh on 2022/5/16.
//

#include "util.h"
#include <string>

#if defined(__APPLE__) || defined(__MACH__)

#include <limits.h>
#include <mach-o/dyld.h>    /* _NSGetExecutablePath */

int uv_exepath(char *buffer, int *size) {
    char abspath[PATH_MAX * 2 + 1]; // 绝对路径
    char exepath[PATH_MAX + 1];     // 相对路径
    uint32_t exepath_size;
    size_t abspath_size;

    /* Invalid argument */
    if (buffer == nullptr || size == nullptr || *size == 0)
        return -EINVAL;

    /* exepath不是绝对路径 -> Input/output error */
    exepath_size = sizeof(exepath);
    if (_NSGetExecutablePath(exepath, &exepath_size)) { // exepath是绝对路径返回0, 相对路径返回-1
        return -EIO;
    }

    /* exepath不是绝对路径 */
    if (realpath(exepath, abspath) != abspath) {
        return -errno;
    }

    /* abspath长度为0 -> Input/output error */
    abspath_size = strlen(abspath);
    if (abspath_size == 0) {
        return -EIO;
    }

    *size -= 1; // 去掉'\0'
    if ((size_t) *size > abspath_size) {
        *size = abspath_size;
    }
    memcpy(buffer, abspath, *size);
    buffer[*size] = '\0';
    return 0;
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
        if (uv_exepath(buffer, &n) != 0) { // 有错误
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
#endif // defined(_WIN32)
        return filePath;
    }

    std::string exeDir(bool isExe /* = True */) {
        auto path = exePath(isExe);
        return path.substr(path.rfind('/') + 1);
    }

    std::string exeName(bool isExe /* = True */) {
        auto path = exePath(isExe);
        return path.substr(0, path.rfind('/') + 1);
    }

} // htoolkit
