#ifndef HTOOLKIT_UTIL_H
#define HTOOLKIT_UTIL_H

#include <string>
#include <sstream>

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

} // htoolkit

#endif //HTOOLKIT_UTIL_H
