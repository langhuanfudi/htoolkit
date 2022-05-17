//
// Created by hxh on 2022/5/17.
//

#ifndef HTOOLKIT_SEMAPHORE_H
#define HTOOLKIT_SEMAPHORE_H

//#if defined(__linux__)
//#include <semaphore.h>
//#define HAVE_SEM
//#endif // defined(__linux__)

#include <mutex>
#include <condition_variable>

namespace htoolkit {
    class semaphore {
    private:
        size_t _count;
        std::recursive_mutex _mutex;
        std::condition_variable_any _condition;
    public:
        explicit semaphore(size_t initial = 0);
        ~semaphore() {}
        void post(size_t n = 1);
        void wait();
    }
};


} // namespace htoolkit

#endif //HTOOLKIT_SEMAPHORE_H
