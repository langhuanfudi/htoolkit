//
// Created by hxh on 2022/5/15.
//

#include <sys/stat.h>
#include <cstdarg>
#include <iostream>

#include "logger.h"
#include "onceToken.h"
#include "hfile.h"

#if defined(__MACH__) || ((defined(__linux) || defined(__linux__)) && !defined(ANDROID))

#include <sys/syslog.h>

#endif // defined(__MACH__) || ((defined(__linux) || defined(__linux__)) && !defined(ANDROID))

using namespace std;

namespace htoolkit {
    /**
     * logContext
     */
    static inline const char *getFileName(const char *file) {
        auto pos = std::strrchr(file, '/');
        return pos ? pos + 1 : file;
    }

    static inline const char *getFunctionName(const char *function) {
        auto pos = std::strrchr(function, ':');
        return pos ? pos + 1 : function;
    }

    logContext::logContext(logLevel level, const char *file, const char *function, int line, const char *module_name)
            : _level(level), _line(line), _file(getFileName(file)), _function(getFunctionName(function)),
              _module_name(module_name) {
        gettimeofday(&_tv, nullptr);
        _thread_name = getThreadName();
    }


    /**
     * logger
     */
    logger *g_defaultLogger = nullptr;

    logger &getlogger() {
        if (g_defaultLogger == nullptr) {
            g_defaultLogger = &logger::Instance();
        }
        return *g_defaultLogger;
    }

    logger &logger::Instance() {
        static std::shared_ptr<logger> s_instance(new logger(exeName()));
        static logger &s_instance_ref = *s_instance;
        return s_instance_ref;
    }

    logger::logger(const std::string &loggerName) {
        _logger_name = loggerName;
        _last_log = std::shared_ptr<logContext>();
    }

    logger::~logger() {

    }

    void logger::add(const std::shared_ptr<logChannel> &channel) {
        _channels[channel->name()] = channel;
    }

    void logger::del(const std::string &name) {
        _channels.erase(name);
    }

    const std::string &logger::getName() const {
        return _logger_name;
    }

    void logger::write(const logContextPtr &ctx) {

    }

} // namespace htoolkit
