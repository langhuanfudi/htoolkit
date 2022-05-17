//
// Created by hxh on 2022/5/17.
//

#ifndef HTOOLKIT_HLIST_H
#define HTOOLKIT_HLIST_H

#include <list>
#include <type_traits>

namespace htoolkit {
    template<typename T>
    class hlist : public std::list<T> {
    public:
        template<typename ... Args>
        hlist(Args &&...args):std::list<T>(std::forward<Args>(args)...) {};
        ~hlist() = default;

        void append(hlist<T> &other);

        template<typename Func>
        void for_each(Func &&func);

        template<typename Func>
        void for_each(Func &&func) const;
    };

} // namespace htoolkit

#endif //HTOOLKIT_HLIST_H
