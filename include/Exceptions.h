#pragma once

#include <stdexcept>

namespace Peep {

template <typename Tag>
class TaggedException : public std::runtime_error {
public:
    explicit TaggedException(const std::string &msg)
        : std::runtime_error(msg) {}
};

struct KeyErrTag{};
struct EventErrTag{};
struct LogicErrTag{};
struct DrawErrTag{};
struct FontErrTag{};

using KeyCallbackException = TaggedException<KeyErrTag>;
using EventCallbackException = TaggedException<EventErrTag>;
using LogicLoopException = TaggedException<LogicErrTag>;
using DrawLoopException = TaggedException<DrawErrTag>;
using FontCreationException = TaggedException<FontErrTag>;

}