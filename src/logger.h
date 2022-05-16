//
// Created by hxh on 2022/5/15.
//

#ifndef HTOOLKIT_LOGGER_H
#define HTOOLKIT_LOGGER_H

#include <map>
#include <memory>

#include "util.h"

namespace htoolkit {
    class logContext;   // 日志上下文，用于存储日志信息，包括日志级别、日志所在文件名、函数名、行号、用户待输出的日志信息
    class logChannel;   // 日志通道类，该类是一个抽象类，且是所有特定类型通道的基类
    class logWriter;    // 写日志器类，该类是一个抽象类，定义了一个write纯虚函数
    class logger;       // 单例类，用于日志模块的配置管理
    using logContextPtr = std::shared_ptr<logContext>;

    /* 日志级别, 从低到高 */
    typedef enum {
        LTrace = 0, LDebug, LInfo, LWarn, LError
    } logLevel;

    /**
     * 日志类
     */
    class logger : public std::enable_shared_from_this<logger>, public noncopyable {
    private:
        logContextPtr _last_log;
        std::string _logger_name;
        std::shared_ptr <logWriter> _writer;
        std::map <std::string, std::shared_ptr<logChannel>> _channels;

    public:
        friend class asyncLogWriter;

        using Ptr = std::shared_ptr<logger>;

        /* 获取日志单例 */
        static logger &Instance();
        explicit logger(const std::string &loggerName);
        ~logger();

        /* 添加日志通道 */
        void add(const std::shared_ptr <logChannel> &channel);

        /* 删除日志通道 */
        void del(const std::string &name);

        /* 获取日志通道 */
        std::shared_ptr <logChannel> get(const std::string &name);

        /* 设置写log器 */
        void setWriter(const std::shared_ptr <logWriter> &writer);

        /* 设置所有日志通道的log等级 */
        void setLevel(logLevel level);

        /* 获取logger名 */
        const std::string &getName() const;

        /* 写日志 */
        void write(const logContextPtr &ctx);

    private:
        /* 写日志到各channel, 仅供AsyncLogWriter调用 */
        void writeChannels(const logContextPtr &ctx);
        void writeChannels_l(const logContextPtr &ctx);
    };

    /**
     * 日志上下文类
     */
    class logContext : public std::ostringstream {
    private:
        bool _got_content = false;
        std::string _content;
    };

    /**
     * 日志上下文捕获器类
     */
    class logContextCapturer {
    private:
        logContextPtr _ctx;
        logger &_logger;
    };

    /**
     * 写日志器类
     */
    class logWriter : public noncopyable {
    };

} // namespace htoolkit

#endif // HTOOLKIT_LOGGER_H
