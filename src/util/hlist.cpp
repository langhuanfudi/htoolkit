//
// Created by hxh on 2022/5/17.
//

#include "hlist.h"

namespace htoolkit {

    template<typename T>
    void hlist<T>::append(hlist<T> &other) {
        if (other.empty())
            return;
        this->insert(this->end(), other.begin(), other.end());
        other.clear();
    }

    template<typename T>
    template<typename Func>
    void hlist<T>::for_each(Func &&func) {
        for (auto &t: *this) {
            func(t);
        }
    }

    template<typename T>
    template<typename Func>
    void hlist<T>::for_each(Func &&func) const {
        for (auto &t: *this) {
            func(t);
        }
    }
} // namespace htoolkit
