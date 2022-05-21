//
// Created by hxh on 2022/5/19.
//

#include "onceToken.h"

namespace htoolkit {
    template<typename func>
    onceToken::onceToken(const func &onConstructed, task onDestructed) {
        onConstructed();
        _onDestructed = std::move(onDestructed);
    }

    onceToken::onceToken(std::nullptr_t, task onDestructed) {
        _onDestructed = std::move(onDestructed);
    }

    onceToken::~onceToken() {
        if (_onDestructed) {
            _onDestructed();
        }
    }

} // htoolkit
