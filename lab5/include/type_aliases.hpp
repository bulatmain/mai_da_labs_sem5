#ifndef TYPE_ALIASES_HPP
#define TYPE_ALIASES_HPP

#include <cinttypes>
#include <limits>
#include <memory>
#include <vector>
#include <string>

namespace lab {
    // Integer type aliases
    using u64 = uint64_t;
    using i64 = int64_t;
    using u32 = uint32_t;
    using i32 = int32_t;
    using u16 = uint16_t;
    using i16 = int16_t;
    using u8 = uint8_t;
    using i8 = int8_t;

    template <class T>
    using limit = std::numeric_limits<T>;

    // Alias for shared_ptr of basic types
    using CharPtr = std::shared_ptr<char>;
    using U64Ptr = std::shared_ptr<u64>;
    using I64Ptr = std::shared_ptr<i64>;
}

#endif // TYPE_ALIASES_HPP
