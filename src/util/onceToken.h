//
// Created by hxh on 2022/5/19.
//

#ifndef HTOOLKIT_ONCETOKEN_H
#define HTOOLKIT_ONCETOKEN_H

#include <functional>
#include <type_traits>

namespace htoolkit {

    class onceToken {
    public:
        using task = std::function<void(void)>;

        template<typename func>
        onceToken(const func &onConstructed, task onDestructed = nullptr);

        onceToken(std::nullptr_t, task onDestructed = nullptr);
        ~onceToken();
    private:
        onceToken() = delete;
        onceToken(const onceToken &) = delete;
        onceToken(onceToken &&) = delete;
        onceToken &operator=(const onceToken &) = delete;
        onceToken &operator=(onceToken &&) = delete;
    private:
        task _onDestructed;
    };

} // htoolkit

#endif //HTOOLKIT_ONCETOKEN_H
