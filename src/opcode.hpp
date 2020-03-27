#ifndef WINTER_OPCODE_HPP
#define WINTER_OPCODE_HPP

#include <cstdint>

namespace winter {

enum class OpcodeValue : uint16_t {
    I32Const,
    Return
};

}

#endif
