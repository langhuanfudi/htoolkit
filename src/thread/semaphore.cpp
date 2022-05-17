//
// Created by hxh on 2022/5/17.
//

#include "semaphore.h"

namespace htoolkit {
    semaphore::semaphore(size_t initial /* = 0 */) {
        _count = 0; // 现在有几个坑位
    }

    /* 拉完了, 多出来了n个坑位 */
    void semaphore::post(size_t n /* = 1 */) {
        std::unique_lock<std::recursive_mutex> lock(_mutex);
        _count += n;
        if (n == 1)
            _condition.notify_one();
        else
            _condition.notify_all();
    }

    /* 等一个坑位 */
    void semaphore::wait() {
        std::unique_lock<std::recursive_mutex> lock(_mutex);
        while (_count == 0) {
            _condition.wait(lock);
        }
        --_count;
    }

} // namespace htoolkit
