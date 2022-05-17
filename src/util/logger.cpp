//
// Created by hxh on 2022/5/15.
//

#include "logger.h"

using namespace std;

namespace htoolkit {
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
