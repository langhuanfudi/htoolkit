#ifndef HTOOLKIT_UTIL_H
#define HTOOLKIT_UTIL_H

#include <string>
#include <sstream>

namespace htoolkit {
    /* 禁止复制基类 */
    class noncopyable {
    protected:
        noncopyable() {}
        ~noncopyable() {}
    private:
        noncopyable(const noncopyable &that) = delete;
        noncopyable(noncopyable &&that) = delete;
        noncopyable &operator=(const noncopyable &that) = delete;
        noncopyable &operator=(noncopyable &&that) = delete;
    };

    std::string exePath(bool isExe = true);
    std::string exeName(bool isExe = true);

} // htoolkit

#endif //HTOOLKIT_UTIL_H
