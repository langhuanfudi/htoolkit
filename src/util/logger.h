//
// Created by hxh on 2022/5/15.
//

#ifndef HTOOLKIT_LOGGER_H
#define HTOOLKIT_LOGGER_H

#include <map>
#include <memory>
#include <mutex>
#include <fstream>

#include "util.h"
#include "hlist.h"
#include "thread/semaphore.h"

namespace htoolkit {
    class logContext;   // 日志上下文类
    class logChannel;   // 日志通道类
    class logWriter;    // 写日志器类
    class logger;       // 日志类，用于日志模块的配置管理
    using logContextPtr = std::shared_ptr<logContext>;

    /* 日志级别, 从低到高 */
    typedef enum {
        LTrace = 0, LDebug, LInfo, LWarn, LError
    } logLevel;

    /**
     * 日志上下文类
     * 用于存储日志信息, 包括日志级别、日志所在文件名、函数名、行号、用户待输出的日志信息
     */
    class logContext : public std::ostringstream {
    private:
        bool _got_content = false;
        std::string _content;
    public:
        logLevel _level;
        int _line;
        int _repeat = 0;
        std::string _file;
        std::string _function;
        std::string _thread_name;
        std::string _module_name;
        struct timeval _tv;
        const std::string &str();
    public:
        logContext() = default;
        logContext(logLevel level, const char *file, const char *function, int line, const char *module_name);
        ~logContext() = default;
    };

    /**
     * 日志通道类
     * 该类是一个抽象类, 且是所有特定类型通道的基类
     */
    class logChannel : public noncopyable {
    protected:
        std::string _name;
        logLevel _level;
    public:
        logChannel(const std::string &name, logLevel level = LTrace);
        virtual ~logChannel();

        virtual void write(const logger &logger, const logContextPtr &ctx) = 0;
        const std::string &name() const;
        void setLevel(logLevel level);
        static std::string printTime(const timeval &tv);
    protected:
        /**
         * 打印日志到输出流
         * @param logger
         * @param ost 输出流
         * @param ctx
         * @param enable_color 是否启用颜色
         * @param enable_detail 是否打印细节(函数名、源码文件名、源码行)
         */
        virtual void format(const logger &logger, std::ostream &ost, const logContext &ctx, bool enable_color = true,
                            bool enable_detail = true);
    };

    /* 输出日志到广播 */
    class eventChannel : public logChannel {
    public:
        static const std::string kBroadcastLogEvent; // 输出日志时的广播名


        eventChannel(const std::string &name = "eventChannel", logLevel level = LTrace);
        ~eventChannel() override = default;

        void write(const logger &logger, const logContextPtr &ctx) override;

    };

    /* 输出日志到终端 */
    class consoleChannel : public logChannel {

    };

    /* 输出日志到文件 */
    class fileChannelBase : public logChannel {

    };

    class fileChannel : public fileChannelBase {

    };


    /**
     * 日志类
     * 单例类, 用于日志模块的配置管理
     */
    class logger : public std::enable_shared_from_this<logger>, public noncopyable {
    private:
        logContextPtr _last_log;
        std::string _logger_name;
        std::shared_ptr<logWriter> _writer;
        std::map<std::string, std::shared_ptr<logChannel>> _channels;

    public:
        friend class asyncLogWriter;

        using Ptr = std::shared_ptr<logger>;

        /* 获取日志单例 */
        static logger &Instance();
        explicit logger(const std::string &loggerName);
        ~logger();

        /* 添加日志通道 */
        void add(const std::shared_ptr<logChannel> &channel);

        /* 删除日志通道 */
        void del(const std::string &name);

        /* 获取日志通道 */
        std::shared_ptr<logChannel> get(const std::string &name);

        /* 设置写log器 */
        void setWriter(const std::shared_ptr<logWriter> &writer);

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
     * 日志上下文捕获器类
     */
    class logContextCapturer {
    private:
        logContextPtr _ctx;
        logger &_logger;
    };

    /**
     * 写日志器类
     * 该类是一个抽象类，定义了一个write纯虚函数
     */
    class logWriter : public noncopyable {
        logWriter() = default;
        virtual ~logWriter() = default;
        virtual void write(const logContextPtr &ctx, logger &_logger) = 0;
    };

    class asyncLogWriter : public logWriter {
    public:
        asyncLogWriter();
        ~asyncLogWriter();
    private:
        void run();
        void flushAll();
        void write(const logContextPtr &ctx, logger &_logger) override;
    private:
        bool _exit_flag;
        semaphore _sem;
        std::mutex _mutex;
        std::shared_ptr<std::thread> _thread;

    };

    /**
     * 用法:
     * DebugL << 1 << "+" << 2 << '=' << 3;
     */
#define WriteL(level)::htoolkit::logContextCapture(::htoolkit::getLogger(), level, __FILE__, __FUNCTION__, __LINE__)
#define TraceL WriteL(::htoolkit::LTrace)
#define DebugL WriteL(::htoolkit::LDebug)
#define InfoL WriteL(::htoolkit::LInfo)
#define WarnL WriteL(::htoolkit::LWrite)
#define ErrorL WriteL(:htoolkit::LError)

} // namespace htoolkit

#endif // HTOOLKIT_LOGGER_H
