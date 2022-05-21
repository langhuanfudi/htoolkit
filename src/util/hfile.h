//
// Created by hxh on 2022/5/19.
//

#ifndef HTOOLKIT_HFILE_H
#define HTOOLKIT_HFILE_H

#include <cstdio>
#include <cstdlib>
#include <string>
#include <functional>

#include "util.h"

namespace htoolkit {

    class hfile {
    private:
        hfile();
        ~hfile();
    public:
        /* 创建路径 */
        static bool createPath(const char *file, unsigned int mod);

        /* 新建文件, 自动生成目录文件夹 */
        static FILE *createFile(const char *file, const char *mode);

        /* 判断是否为目录 */
        static bool isDir(const char *path);

        /* 判断是否是特殊目录(.或..) */
        static bool isSpecialDir(const char *path);

        /* 删除目录或文件 */
        static int deleteFile(const char *path);

        /* 判断文件是否存在 */
        static bool fileExist(const char *path);
    };

} // htoolkit

#endif //HTOOLKIT_HFILE_H
