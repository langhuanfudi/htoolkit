//
// Created by hxh on 2022/5/19.
//

#include <limits.h>
#include <dirent.h>
#include <sys/stat.h>

#include "hfile.h"
#include "util.h"
#include "logger.h"

#if !defined(_WIN32)
#define _access access
#define _mkdir mkdir
#endif // !defined(_WIN32)

namespace htoolkit {
    bool hfile::createPath(const char *file, unsigned int mod) {
        std::string path = file;
        std::string dir;
        size_t index = 1;
        while (true) {
            index = path.find('/', index) + 1;
            dir = path.substr(0, index);
            if (dir.length() == 0)
                break;
            /* 文件目录不存在 */
            if (_access(dir.c_str(), 0) == -1) {
                if (_mkdir(dir.c_str(), mod) == -1) {
                    WarnL <<
                }
            }

        }
    }

} // htoolkit
