#ifndef HTOOLKIT_UTIL_H
#define HTOOLKIT_UTIL_H

#include <ctime>
#include <cstdio>
#include <cstring>
#include <memory>
#include <string>
#include <sstream>
#include <vector>
#include <atomic>
#include <unordered_map>

#if defined(_WIN32)
#else
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <cstddef>
#endif // defined(_WIN32)

#define INSTANCE_IMP(class_name, ...) \
class_name &class_name::Instance() { \
    static std::shared_ptr<class_name> s_instance(new class_name(__VA_ARGS__)); \
    static class_name &s_instance_ref = *s_instance; \
    return s_instance_ref; \
}

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
    std::string exeDir(bool isExe = true);
    std::string exeName(bool isExe = true);

    /* 设置线程名 */
    void setThreadName(const char *name);

    /* 获取线程名 */
    std::string getThreadName();

} // htoolkit

#endif //HTOOLKIT_UTIL_H
