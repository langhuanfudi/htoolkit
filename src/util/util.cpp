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
        int n = sizeof(buffer);
        if (uv_exepath(buffer, &n) != 0) { // TODO: error
            n = -1;
        }
        std::string filePath;
        if (n <= 0)
            filePath = "./";
        else
            filePath = buffer;
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

    static std::string limitString(const char *name, size_t max_size) {
        std::string str = name;
        if (str.size() + 1 > max_size) {
            auto erased = str.size() + 1 - max_size + 3;
            str.replace(5, erased, "...");
        }
        return str;
    }

    void setThreadName(const char *name) {
        assert(name);
        pthread_setname_np(limitString(name, 32).data());
    }

    std::string getThreadName() {
        std::string ret;
        ret.resize(32);
        auto tid = pthread_self();
        pthread_getname_np(tid, (char *) ret.data(), ret.size());
        if (ret[0]) {
            ret.resize(strlen(ret.data()));
            return ret;
        }
        return std::to_string((uint64_t) tid);
    }

} // htoolkit
