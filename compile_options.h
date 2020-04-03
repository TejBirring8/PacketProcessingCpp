//
// Created by tbirring on 05/10/2019.
//

#ifndef COMPILE_OPTIONS_H
#define COMPILE_OPTIONS_H

inline const constexpr bool COMPILE_FOR_DEBUG = false;

// instead of deducing endianness at run-time (i.e. HOST_IS_BIG_ENDIAN = (htons(56) == 56),
// or compile-time (reliant on macros from system header files),
// we simply pass this into the compiler as a build option.
inline const constexpr bool HOST_IS_BIG_ENDIAN = false;

#endif //COMPILE_OPTIONS_H
