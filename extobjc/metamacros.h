/**
 * Macros for metaprogramming
 * ExtendedC
 *
 * Copyright (C) 2012 Justin Spahr-Summers
 * Released under the MIT license
 */

#ifndef EXTC_METAMACROS_H
#define EXTC_METAMACROS_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

/**
 * Executes one or more expressions (which may have a void type, such as a call
 * to a function that returns no value) and always returns true.
 */
#define metamacro_exprify(...) \
    ((__VA_ARGS__), true)

/**
 * Returns a string representation of VALUE after full macro expansion.
 */
#define metamacro_stringify(VALUE) \
        metamacro_stringify_(VALUE)

/**
 * Returns A and B concatenated after full macro expansion.
 */
#define metamacro_concat(A, B) \
        metamacro_concat_(A, B)

/**
 * Returns the Nth variadic argument (starting from zero). At least
 * N + 1 variadic arguments must be given. N must be between zero and twenty,
 * inclusive.
 */
#define metamacro_at(N, ...) \
        metamacro_concat(metamacro_at, N)(__VA_ARGS__)

/**
 * Returns the number of arguments (up to twenty) provided to the macro. At
 * least one argument must be provided.
 *
 * Inspired by P99: http://p99.gforge.inria.fr
 */
#define metamacro_argcount(...) \
        metamacro_at(20, __VA_ARGS__, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)

/**
 * Identical to #metamacro_foreach_cxt, except that no CONTEXT argument is
 * given. Only the index and current argument will thus be passed to MACRO.
 */
#define metamacro_foreach(MACRO, SEP, ...) \
        metamacro_foreach_cxt(metamacro_foreach_iter, SEP, MACRO, __VA_ARGS__)

/**
 * Identical to #metamacro_foreach, except that a comma separator is used
 * (since a comma cannot be passed as an argument in a macro).
 */
#define metamacro_foreach_list(MACRO, ...) \
		metamacro_foreach_cxt_list(metamacro_foreach_iter, MACRO, __VA_ARGS__)

/**
 * For each consecutive variadic argument (up to fifty), MACRO is passed the
 * zero-based index of the current argument, CONTEXT, and then the argument
 * itself. The results of adjoining invocations of MACRO are then separated by
 * SEP.
 *
 * Inspired by P99: http://p99.gforge.inria.fr
 */
#define metamacro_foreach_cxt(MACRO, SEP, CONTEXT, ...) \
        metamacro_concat(metamacro_foreach_cxt, metamacro_argcount(__VA_ARGS__))(MACRO, SEP, CONTEXT, __VA_ARGS__)

/**
 * Identical to #metamacro_foreach_cxt, except that a comma separator is used
 * (since a comma cannot be passed as an argument in a macro).
 */
#define metamacro_foreach_cxt_list(MACRO, CONTEXT, ...) \
		metamacro_concat(metamacro_foreach_cxt_list, metamacro_argcount(__VA_ARGS__))(MACRO, CONTEXT, __VA_ARGS__)

/**
 * Identical to #metamacro_foreach_cxt. This can be used when the former would
 * fail due to recursive macro expansion.
 */
#define metamacro_foreach_cxt_recursive(MACRO, SEP, CONTEXT, ...) \
        metamacro_concat(metamacro_foreach_cxt_recursive, metamacro_argcount(__VA_ARGS__))(MACRO, SEP, CONTEXT, __VA_ARGS__)

/**
 * Identical to #metamacro_foreach_cxt_recursive, except that a comma separator is used
 * (since a comma cannot be passed as an argument in a macro).
 */
#define metamacro_foreach_cxt_recursive_list(MACRO, CONTEXT, ...) \
        metamacro_concat(metamacro_foreach_cxt_recursive_list, metamacro_argcount(__VA_ARGS__))(MACRO, CONTEXT, __VA_ARGS__)

/**
 * In consecutive order, appends each variadic argument (up to fifty) onto
 * BASE. The resulting concatenations are then separated by SEP.
 *
 * This is primarily useful to manipulate a list of macro invocations into instead
 * invoking a different, possibly related macro.
 */
#define metamacro_foreach_concat(BASE, SEP, ...) \
        metamacro_foreach_cxt(metamacro_foreach_concat_iter, SEP, BASE, __VA_ARGS__)

/**
 * Iterates COUNT times, each time invoking MACRO with the current index
 * (starting at zero) and CONTEXT. The results of adjoining invocations of MACRO
 * are then separated by SEP.
 *
 * COUNT must be an integer between zero and fifty, inclusive.
 */
#define metamacro_for_cxt(COUNT, MACRO, SEP, CONTEXT) \
        metamacro_concat(metamacro_for_cxt, COUNT)(MACRO, SEP, CONTEXT)

/**
 * Returns the first argument given. At least one argument must be provided.
 *
 * This is useful when implementing a variadic macro, where you may have only
 * one variadic argument, but no way to retrieve it (for example, because \c ...
 * always needs to match at least one argument).
 *
 * @code

#define varmacro(...) \
    metamacro_head(__VA_ARGS__)

 * @endcode
 */
#define metamacro_head(...) \
        metamacro_head_(__VA_ARGS__, 0)

/**
 * Returns every argument except the first. At least two arguments must be
 * provided.
 */
#define metamacro_tail(...) \
        metamacro_tail_(__VA_ARGS__)

/**
 * Returns the first N (up to twenty) variadic arguments as a new argument list.
 * At least N variadic arguments must be provided.
 */
#define metamacro_take(N, ...) \
        metamacro_concat(metamacro_take, N)(__VA_ARGS__)

/**
 * Removes the first N (up to twenty) variadic arguments from the given argument
 * list. At least N variadic arguments must be provided.
 */
#define metamacro_drop(N, ...) \
        metamacro_concat(metamacro_drop, N)(__VA_ARGS__)

/**
 * Decrements VAL, which must be a number between zero and twenty, inclusive.
 *
 * This is primarily useful when dealing with indexes and counts in
 * metaprogramming.
 */
#define metamacro_dec(VAL) \
        metamacro_at(VAL, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19)

/**
 * Increments VAL, which must be a number between zero and twenty, inclusive.
 *
 * This is primarily useful when dealing with indexes and counts in
 * metaprogramming.
 */
#define metamacro_inc(VAL) \
        metamacro_at(VAL, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21)

/**
 * If A is equal to B, the next argument list is expanded; otherwise, the
 * argument list after that is expanded. A and B must be numbers between zero
 * and twenty, inclusive. Additionally, B must be greater than or equal to A.
 *
 * @code

// expands to true
metamacro_if_eq(0, 0)(true)(false)

// expands to false
metamacro_if_eq(0, 1)(true)(false)

 * @endcode
 *
 * This is primarily useful when dealing with indexes and counts in
 * metaprogramming.
 */
#define metamacro_if_eq(A, B) \
        metamacro_concat(metamacro_if_eq, A)(B)

/**
 * Identical to #metamacro_if_eq. This can be used when the former would fail
 * due to recursive macro expansion.
 */
#define metamacro_if_eq_recursive(A, B) \
        metamacro_concat(metamacro_if_eq_recursive, A)(B)

/**
 * Returns 1 if N is an even number, or 0 otherwise. N must be between zero and
 * twenty, inclusive.
 *
 * For the purposes of this test, zero is considered even.
 */
#define metamacro_is_even(N) \
        metamacro_at(N, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1)

/**
 * Returns the logical NOT of B, which must be the number zero or one.
 */
#define metamacro_not(B) \
        metamacro_at(B, 1, 0)

// IMPLEMENTATION DETAILS FOLLOW!
// Do not write code that depends on anything below this line.
#define metamacro_stringify_(VALUE) # VALUE
#define metamacro_concat_(A, B) A ## B
#define metamacro_foreach_iter(INDEX, MACRO, ARG) MACRO(INDEX, ARG)
#define metamacro_head_(FIRST, ...) FIRST
#define metamacro_tail_(FIRST, ...) __VA_ARGS__
#define metamacro_consume_(...)
#define metamacro_expand_(...) __VA_ARGS__

// implemented from scratch so that metamacro_concat() doesn't end up nesting
#define metamacro_foreach_concat_iter(INDEX, BASE, ARG) metamacro_foreach_concat_iter_(BASE, ARG)
#define metamacro_foreach_concat_iter_(BASE, ARG) BASE ## ARG

// metamacro_at expansions
#define metamacro_at0(...) metamacro_head(__VA_ARGS__)
#define metamacro_at1(_0, ...) metamacro_head(__VA_ARGS__)
#define metamacro_at2(_0, _1, ...) metamacro_head(__VA_ARGS__)
#define metamacro_at3(_0, _1, _2, ...) metamacro_head(__VA_ARGS__)
#define metamacro_at4(_0, _1, _2, _3, ...) metamacro_head(__VA_ARGS__)
#define metamacro_at5(_0, _1, _2, _3, _4, ...) metamacro_head(__VA_ARGS__)
#define metamacro_at6(_0, _1, _2, _3, _4, _5, ...) metamacro_head(__VA_ARGS__)
#define metamacro_at7(_0, _1, _2, _3, _4, _5, _6, ...) metamacro_head(__VA_ARGS__)
#define metamacro_at8(_0, _1, _2, _3, _4, _5, _6, _7, ...) metamacro_head(__VA_ARGS__)
#define metamacro_at9(_0, _1, _2, _3, _4, _5, _6, _7, _8, ...) metamacro_head(__VA_ARGS__)
#define metamacro_at10(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, ...) metamacro_head(__VA_ARGS__)
#define metamacro_at11(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, ...) metamacro_head(__VA_ARGS__)
#define metamacro_at12(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, ...) metamacro_head(__VA_ARGS__)
#define metamacro_at13(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, ...) metamacro_head(__VA_ARGS__)
#define metamacro_at14(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, ...) metamacro_head(__VA_ARGS__)
#define metamacro_at15(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, ...) metamacro_head(__VA_ARGS__)
#define metamacro_at16(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, ...) metamacro_head(__VA_ARGS__)
#define metamacro_at17(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, ...) metamacro_head(__VA_ARGS__)
#define metamacro_at18(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, ...) metamacro_head(__VA_ARGS__)
#define metamacro_at19(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, ...) metamacro_head(__VA_ARGS__)
#define metamacro_at20(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, ...) metamacro_head(__VA_ARGS__)

// metamacro_foreach_cxt expansions
#define metamacro_foreach_cxt0(MACRO, SEP, CONTEXT)
#define metamacro_foreach_cxt1(MACRO, SEP, CONTEXT, _0) MACRO(0, CONTEXT, _0)

#define metamacro_foreach_cxt2(MACRO, SEP, CONTEXT, _0, _1) \
    metamacro_foreach_cxt1(MACRO, SEP, CONTEXT, _0) \
    SEP \
    MACRO(1, CONTEXT, _1)

#define metamacro_foreach_cxt3(MACRO, SEP, CONTEXT, _0, _1, _2) \
    metamacro_foreach_cxt2(MACRO, SEP, CONTEXT, _0, _1) \
    SEP \
    MACRO(2, CONTEXT, _2)

#define metamacro_foreach_cxt4(MACRO, SEP, CONTEXT, _0, _1, _2, _3) \
    metamacro_foreach_cxt3(MACRO, SEP, CONTEXT, _0, _1, _2) \
    SEP \
    MACRO(3, CONTEXT, _3)

#define metamacro_foreach_cxt5(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4) \
    metamacro_foreach_cxt4(MACRO, SEP, CONTEXT, _0, _1, _2, _3) \
    SEP \
    MACRO(4, CONTEXT, _4)

#define metamacro_foreach_cxt6(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5) \
    metamacro_foreach_cxt5(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4) \
    SEP \
    MACRO(5, CONTEXT, _5)

#define metamacro_foreach_cxt7(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6) \
    metamacro_foreach_cxt6(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5) \
    SEP \
    MACRO(6, CONTEXT, _6)

#define metamacro_foreach_cxt8(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7) \
    metamacro_foreach_cxt7(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6) \
    SEP \
    MACRO(7, CONTEXT, _7)

#define metamacro_foreach_cxt9(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8) \
    metamacro_foreach_cxt8(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7) \
    SEP \
    MACRO(8, CONTEXT, _8)

#define metamacro_foreach_cxt10(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9) \
    metamacro_foreach_cxt9(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8) \
    SEP \
    MACRO(9, CONTEXT, _9)

#define metamacro_foreach_cxt11(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) \
    metamacro_foreach_cxt10(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9) \
    SEP \
    MACRO(10, CONTEXT, _10)

#define metamacro_foreach_cxt12(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) \
    metamacro_foreach_cxt11(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) \
    SEP \
    MACRO(11, CONTEXT, _11)

#define metamacro_foreach_cxt13(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) \
    metamacro_foreach_cxt12(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) \
    SEP \
    MACRO(12, CONTEXT, _12)

#define metamacro_foreach_cxt14(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) \
    metamacro_foreach_cxt13(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) \
    SEP \
    MACRO(13, CONTEXT, _13)

#define metamacro_foreach_cxt15(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) \
    metamacro_foreach_cxt14(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) \
    SEP \
    MACRO(14, CONTEXT, _14)

#define metamacro_foreach_cxt16(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) \
    metamacro_foreach_cxt15(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) \
    SEP \
    MACRO(15, CONTEXT, _15)

#define metamacro_foreach_cxt17(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) \
    metamacro_foreach_cxt16(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) \
    SEP \
    MACRO(16, CONTEXT, _16)

#define metamacro_foreach_cxt18(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) \
    metamacro_foreach_cxt17(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) \
    SEP \
    MACRO(17, CONTEXT, _17)

#define metamacro_foreach_cxt19(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) \
    metamacro_foreach_cxt18(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) \
    SEP \
    MACRO(18, CONTEXT, _18)

#define metamacro_foreach_cxt20(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) \
    metamacro_foreach_cxt19(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) \
    SEP \
    MACRO(19, CONTEXT, _19)

#define metamacro_foreach_cxt21(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20) \
    metamacro_foreach_cxt20(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) \
    SEP \
    MACRO(20, CONTEXT, _20)

#define metamacro_foreach_cxt22(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21) \
    metamacro_foreach_cxt21(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20) \
    SEP \
    MACRO(21, CONTEXT, _21)

#define metamacro_foreach_cxt23(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22) \
    metamacro_foreach_cxt22(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21) \
    SEP \
    MACRO(22, CONTEXT, _22)

#define metamacro_foreach_cxt24(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23) \
    metamacro_foreach_cxt23(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22) \
    SEP \
    MACRO(23, CONTEXT, _23)

#define metamacro_foreach_cxt25(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24) \
    metamacro_foreach_cxt24(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23) \
    SEP \
    MACRO(24, CONTEXT, _24)

#define metamacro_foreach_cxt26(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25) \
    metamacro_foreach_cxt25(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24) \
    SEP \
    MACRO(25, CONTEXT, _25)

#define metamacro_foreach_cxt27(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26) \
    metamacro_foreach_cxt26(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25) \
    SEP \
    MACRO(26, CONTEXT, _26)

#define metamacro_foreach_cxt28(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27) \
    metamacro_foreach_cxt27(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26) \
    SEP \
    MACRO(27, CONTEXT, _27)

#define metamacro_foreach_cxt29(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28) \
    metamacro_foreach_cxt28(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27) \
    SEP \
    MACRO(28, CONTEXT, _28)

#define metamacro_foreach_cxt30(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29) \
    metamacro_foreach_cxt29(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28) \
    SEP \
    MACRO(29, CONTEXT, _29)

#define metamacro_foreach_cxt31(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30) \
    metamacro_foreach_cxt30(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29) \
    SEP \
    MACRO(30, CONTEXT, _30)

#define metamacro_foreach_cxt32(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31) \
    metamacro_foreach_cxt31(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30) \
    SEP \
    MACRO(31, CONTEXT, _31)

#define metamacro_foreach_cxt33(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32) \
    metamacro_foreach_cxt32(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31) \
    SEP \
    MACRO(32, CONTEXT, _32)

#define metamacro_foreach_cxt34(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33) \
    metamacro_foreach_cxt33(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32) \
    SEP \
    MACRO(33, CONTEXT, _33)

#define metamacro_foreach_cxt35(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34) \
    metamacro_foreach_cxt34(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33) \
    SEP \
    MACRO(34, CONTEXT, _34)

#define metamacro_foreach_cxt36(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35) \
    metamacro_foreach_cxt35(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34) \
    SEP \
    MACRO(35, CONTEXT, _35)

#define metamacro_foreach_cxt37(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36) \
    metamacro_foreach_cxt36(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35) \
    SEP \
    MACRO(36, CONTEXT, _36)

#define metamacro_foreach_cxt38(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37) \
    metamacro_foreach_cxt37(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36) \
    SEP \
    MACRO(37, CONTEXT, _37)

#define metamacro_foreach_cxt39(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38) \
    metamacro_foreach_cxt38(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37) \
    SEP \
    MACRO(38, CONTEXT, _38)

#define metamacro_foreach_cxt40(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39) \
    metamacro_foreach_cxt39(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38) \
    SEP \
    MACRO(39, CONTEXT, _39)

#define metamacro_foreach_cxt41(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40) \
    metamacro_foreach_cxt40(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39) \
    SEP \
    MACRO(40, CONTEXT, _40)

#define metamacro_foreach_cxt42(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41) \
    metamacro_foreach_cxt41(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40) \
    SEP \
    MACRO(41, CONTEXT, _41)

#define metamacro_foreach_cxt43(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42) \
    metamacro_foreach_cxt42(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41) \
    SEP \
    MACRO(42, CONTEXT, _42)

#define metamacro_foreach_cxt44(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43) \
    metamacro_foreach_cxt43(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42) \
    SEP \
    MACRO(43, CONTEXT, _43)

#define metamacro_foreach_cxt45(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44) \
    metamacro_foreach_cxt44(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43) \
    SEP \
    MACRO(44, CONTEXT, _44)

#define metamacro_foreach_cxt46(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45) \
    metamacro_foreach_cxt45(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44) \
    SEP \
    MACRO(45, CONTEXT, _45)

#define metamacro_foreach_cxt47(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46) \
    metamacro_foreach_cxt46(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45) \
    SEP \
    MACRO(46, CONTEXT, _46)

#define metamacro_foreach_cxt48(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47) \
    metamacro_foreach_cxt47(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46) \
    SEP \
    MACRO(47, CONTEXT, _47)

#define metamacro_foreach_cxt49(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48) \
    metamacro_foreach_cxt48(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47) \
    SEP \
    MACRO(48, CONTEXT, _48)

#define metamacro_foreach_cxt50(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49) \
    metamacro_foreach_cxt49(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48) \
    SEP \
    MACRO(49, CONTEXT, _49)

// metamacro_foreach_cxt_list expansions
#define metamacro_foreach_cxt_list0(MACRO, CONTEXT)
#define metamacro_foreach_cxt_list1(MACRO, CONTEXT, _0) MACRO(0, CONTEXT, _0)

#define metamacro_foreach_cxt_list2(MACRO, CONTEXT, _0, _1) \
    metamacro_foreach_cxt_list1(MACRO, CONTEXT, _0), \
    MACRO(1, CONTEXT, _1)

#define metamacro_foreach_cxt_list3(MACRO, CONTEXT, _0, _1, _2) \
    metamacro_foreach_cxt_list2(MACRO, CONTEXT, _0, _1), \
    MACRO(2, CONTEXT, _2)

#define metamacro_foreach_cxt_list4(MACRO, CONTEXT, _0, _1, _2, _3) \
    metamacro_foreach_cxt_list3(MACRO, CONTEXT, _0, _1, _2), \
    MACRO(3, CONTEXT, _3)

#define metamacro_foreach_cxt_list5(MACRO, CONTEXT, _0, _1, _2, _3, _4) \
    metamacro_foreach_cxt_list4(MACRO, CONTEXT, _0, _1, _2, _3), \
    MACRO(4, CONTEXT, _4)

#define metamacro_foreach_cxt_list6(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5) \
    metamacro_foreach_cxt_list5(MACRO, CONTEXT, _0, _1, _2, _3, _4), \
    MACRO(5, CONTEXT, _5)

#define metamacro_foreach_cxt_list7(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6) \
    metamacro_foreach_cxt_list6(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5), \
    MACRO(6, CONTEXT, _6)

#define metamacro_foreach_cxt_list8(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7) \
    metamacro_foreach_cxt_list7(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6), \
    MACRO(7, CONTEXT, _7)

#define metamacro_foreach_cxt_list9(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8) \
    metamacro_foreach_cxt_list8(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7), \
    MACRO(8, CONTEXT, _8)

#define metamacro_foreach_cxt_list10(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9) \
    metamacro_foreach_cxt_list9(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8), \
    MACRO(9, CONTEXT, _9)

#define metamacro_foreach_cxt_list11(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) \
    metamacro_foreach_cxt_list10(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9), \
    MACRO(10, CONTEXT, _10)

#define metamacro_foreach_cxt_list12(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) \
    metamacro_foreach_cxt_list11(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10), \
    MACRO(11, CONTEXT, _11)

#define metamacro_foreach_cxt_list13(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) \
    metamacro_foreach_cxt_list12(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11), \
    MACRO(12, CONTEXT, _12)

#define metamacro_foreach_cxt_list14(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) \
    metamacro_foreach_cxt_list13(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12), \
    MACRO(13, CONTEXT, _13)

#define metamacro_foreach_cxt_list15(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) \
    metamacro_foreach_cxt_list14(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13), \
    MACRO(14, CONTEXT, _14)

#define metamacro_foreach_cxt_list16(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) \
    metamacro_foreach_cxt_list15(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14), \
    MACRO(15, CONTEXT, _15)

#define metamacro_foreach_cxt_list17(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) \
    metamacro_foreach_cxt_list16(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15), \
    MACRO(16, CONTEXT, _16)

#define metamacro_foreach_cxt_list18(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) \
    metamacro_foreach_cxt_list17(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16), \
    MACRO(17, CONTEXT, _17)

#define metamacro_foreach_cxt_list19(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) \
    metamacro_foreach_cxt_list18(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17), \
    MACRO(18, CONTEXT, _18)

#define metamacro_foreach_cxt_list20(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) \
    metamacro_foreach_cxt_list19(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18), \
    MACRO(19, CONTEXT, _19)

#define metamacro_foreach_cxt_list21(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20) \
    metamacro_foreach_cxt_list20(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19), \
    MACRO(20, CONTEXT, _20)

#define metamacro_foreach_cxt_list22(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21) \
    metamacro_foreach_cxt_list21(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20), \
    MACRO(21, CONTEXT, _21)

#define metamacro_foreach_cxt_list23(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22) \
    metamacro_foreach_cxt_list22(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21), \
    MACRO(22, CONTEXT, _22)

#define metamacro_foreach_cxt_list24(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23) \
    metamacro_foreach_cxt_list23(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22), \
    MACRO(23, CONTEXT, _23)

#define metamacro_foreach_cxt_list25(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24) \
    metamacro_foreach_cxt_list24(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23), \
    MACRO(24, CONTEXT, _24)

#define metamacro_foreach_cxt_list26(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25) \
    metamacro_foreach_cxt_list25(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24), \
    MACRO(25, CONTEXT, _25)

#define metamacro_foreach_cxt_list27(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26) \
    metamacro_foreach_cxt_list26(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25), \
    MACRO(26, CONTEXT, _26)

#define metamacro_foreach_cxt_list28(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27) \
    metamacro_foreach_cxt_list27(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26), \
    MACRO(27, CONTEXT, _27)

#define metamacro_foreach_cxt_list29(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28) \
    metamacro_foreach_cxt_list28(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27), \
    MACRO(28, CONTEXT, _28)

#define metamacro_foreach_cxt_list30(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29) \
    metamacro_foreach_cxt_list29(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28), \
    MACRO(29, CONTEXT, _29)

#define metamacro_foreach_cxt_list31(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30) \
    metamacro_foreach_cxt_list30(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29), \
    MACRO(30, CONTEXT, _30)

#define metamacro_foreach_cxt_list32(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31) \
    metamacro_foreach_cxt_list31(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30), \
    MACRO(31, CONTEXT, _31)

#define metamacro_foreach_cxt_list33(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32) \
    metamacro_foreach_cxt_list32(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31), \
    MACRO(32, CONTEXT, _32)

#define metamacro_foreach_cxt_list34(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33) \
    metamacro_foreach_cxt_list33(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32), \
    MACRO(33, CONTEXT, _33)

#define metamacro_foreach_cxt_list35(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34) \
    metamacro_foreach_cxt_list34(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33), \
    MACRO(34, CONTEXT, _34)

#define metamacro_foreach_cxt_list36(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35) \
    metamacro_foreach_cxt_list35(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34), \
    MACRO(35, CONTEXT, _35)

#define metamacro_foreach_cxt_list37(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36) \
    metamacro_foreach_cxt_list36(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35), \
    MACRO(36, CONTEXT, _36)

#define metamacro_foreach_cxt_list38(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37) \
    metamacro_foreach_cxt_list37(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36), \
    MACRO(37, CONTEXT, _37)

#define metamacro_foreach_cxt_list39(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38) \
    metamacro_foreach_cxt_list38(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37), \
    MACRO(38, CONTEXT, _38)

#define metamacro_foreach_cxt_list40(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39) \
    metamacro_foreach_cxt_list39(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38), \
    MACRO(39, CONTEXT, _39)

#define metamacro_foreach_cxt_list41(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40) \
    metamacro_foreach_cxt_list40(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39), \
    MACRO(40, CONTEXT, _40)

#define metamacro_foreach_cxt_list42(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41) \
    metamacro_foreach_cxt_list41(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40), \
    MACRO(41, CONTEXT, _41)

#define metamacro_foreach_cxt_list43(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42) \
    metamacro_foreach_cxt_list42(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41), \
    MACRO(42, CONTEXT, _42)

#define metamacro_foreach_cxt_list44(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43) \
    metamacro_foreach_cxt_list43(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42), \
    MACRO(43, CONTEXT, _43)

#define metamacro_foreach_cxt_list45(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44) \
    metamacro_foreach_cxt_list44(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43), \
    MACRO(44, CONTEXT, _44)

#define metamacro_foreach_cxt_list46(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45) \
    metamacro_foreach_cxt_list45(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44), \
    MACRO(45, CONTEXT, _45)

#define metamacro_foreach_cxt_list47(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46) \
    metamacro_foreach_cxt_list46(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45), \
    MACRO(46, CONTEXT, _46)

#define metamacro_foreach_cxt_list48(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47) \
    metamacro_foreach_cxt_list47(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46), \
    MACRO(47, CONTEXT, _47)

#define metamacro_foreach_cxt_list49(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48) \
    metamacro_foreach_cxt_list48(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47), \
    MACRO(48, CONTEXT, _48)

#define metamacro_foreach_cxt_list50(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49) \
    metamacro_foreach_cxt_list49(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48), \
    MACRO(49, CONTEXT, _49)

// metamacro_foreach_cxt_recursive expansions
#define metamacro_foreach_cxt_recursive0(MACRO, SEP, CONTEXT)
#define metamacro_foreach_cxt_recursive1(MACRO, SEP, CONTEXT, _0) MACRO(0, CONTEXT, _0)

#define metamacro_foreach_cxt_recursive2(MACRO, SEP, CONTEXT, _0, _1) \
    metamacro_foreach_cxt_recursive1(MACRO, SEP, CONTEXT, _0) \
    SEP \
    MACRO(1, CONTEXT, _1)

#define metamacro_foreach_cxt_recursive3(MACRO, SEP, CONTEXT, _0, _1, _2) \
    metamacro_foreach_cxt_recursive2(MACRO, SEP, CONTEXT, _0, _1) \
    SEP \
    MACRO(2, CONTEXT, _2)

#define metamacro_foreach_cxt_recursive4(MACRO, SEP, CONTEXT, _0, _1, _2, _3) \
    metamacro_foreach_cxt_recursive3(MACRO, SEP, CONTEXT, _0, _1, _2) \
    SEP \
    MACRO(3, CONTEXT, _3)

#define metamacro_foreach_cxt_recursive5(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4) \
    metamacro_foreach_cxt_recursive4(MACRO, SEP, CONTEXT, _0, _1, _2, _3) \
    SEP \
    MACRO(4, CONTEXT, _4)

#define metamacro_foreach_cxt_recursive6(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5) \
    metamacro_foreach_cxt_recursive5(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4) \
    SEP \
    MACRO(5, CONTEXT, _5)

#define metamacro_foreach_cxt_recursive7(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6) \
    metamacro_foreach_cxt_recursive6(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5) \
    SEP \
    MACRO(6, CONTEXT, _6)

#define metamacro_foreach_cxt_recursive8(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7) \
    metamacro_foreach_cxt_recursive7(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6) \
    SEP \
    MACRO(7, CONTEXT, _7)

#define metamacro_foreach_cxt_recursive9(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8) \
    metamacro_foreach_cxt_recursive8(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7) \
    SEP \
    MACRO(8, CONTEXT, _8)

#define metamacro_foreach_cxt_recursive10(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9) \
    metamacro_foreach_cxt_recursive9(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8) \
    SEP \
    MACRO(9, CONTEXT, _9)

#define metamacro_foreach_cxt_recursive11(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) \
    metamacro_foreach_cxt_recursive10(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9) \
    SEP \
    MACRO(10, CONTEXT, _10)

#define metamacro_foreach_cxt_recursive12(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) \
    metamacro_foreach_cxt_recursive11(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) \
    SEP \
    MACRO(11, CONTEXT, _11)

#define metamacro_foreach_cxt_recursive13(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) \
    metamacro_foreach_cxt_recursive12(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) \
    SEP \
    MACRO(12, CONTEXT, _12)

#define metamacro_foreach_cxt_recursive14(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) \
    metamacro_foreach_cxt_recursive13(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) \
    SEP \
    MACRO(13, CONTEXT, _13)

#define metamacro_foreach_cxt_recursive15(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) \
    metamacro_foreach_cxt_recursive14(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) \
    SEP \
    MACRO(14, CONTEXT, _14)

#define metamacro_foreach_cxt_recursive16(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) \
    metamacro_foreach_cxt_recursive15(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) \
    SEP \
    MACRO(15, CONTEXT, _15)

#define metamacro_foreach_cxt_recursive17(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) \
    metamacro_foreach_cxt_recursive16(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) \
    SEP \
    MACRO(16, CONTEXT, _16)

#define metamacro_foreach_cxt_recursive18(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) \
    metamacro_foreach_cxt_recursive17(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) \
    SEP \
    MACRO(17, CONTEXT, _17)

#define metamacro_foreach_cxt_recursive19(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) \
    metamacro_foreach_cxt_recursive18(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) \
    SEP \
    MACRO(18, CONTEXT, _18)

#define metamacro_foreach_cxt_recursive20(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) \
    metamacro_foreach_cxt_recursive19(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) \
    SEP \
    MACRO(19, CONTEXT, _19)

#define metamacro_foreach_cxt_recursive21(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20) \
    metamacro_foreach_cxt_recursive20(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) \
    SEP \
    MACRO(20, CONTEXT, _20)

#define metamacro_foreach_cxt_recursive22(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21) \
    metamacro_foreach_cxt_recursive21(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20) \
    SEP \
    MACRO(21, CONTEXT, _21)

#define metamacro_foreach_cxt_recursive23(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22) \
    metamacro_foreach_cxt_recursive22(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21) \
    SEP \
    MACRO(22, CONTEXT, _22)

#define metamacro_foreach_cxt_recursive24(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23) \
    metamacro_foreach_cxt_recursive23(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22) \
    SEP \
    MACRO(23, CONTEXT, _23)

#define metamacro_foreach_cxt_recursive25(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24) \
    metamacro_foreach_cxt_recursive24(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23) \
    SEP \
    MACRO(24, CONTEXT, _24)

#define metamacro_foreach_cxt_recursive26(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25) \
    metamacro_foreach_cxt_recursive25(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24) \
    SEP \
    MACRO(25, CONTEXT, _25)

#define metamacro_foreach_cxt_recursive27(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26) \
    metamacro_foreach_cxt_recursive26(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25) \
    SEP \
    MACRO(26, CONTEXT, _26)

#define metamacro_foreach_cxt_recursive28(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27) \
    metamacro_foreach_cxt_recursive27(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26) \
    SEP \
    MACRO(27, CONTEXT, _27)

#define metamacro_foreach_cxt_recursive29(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28) \
    metamacro_foreach_cxt_recursive28(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27) \
    SEP \
    MACRO(28, CONTEXT, _28)

#define metamacro_foreach_cxt_recursive30(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29) \
    metamacro_foreach_cxt_recursive29(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28) \
    SEP \
    MACRO(29, CONTEXT, _29)

#define metamacro_foreach_cxt_recursive31(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30) \
    metamacro_foreach_cxt_recursive30(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29) \
    SEP \
    MACRO(30, CONTEXT, _30)

#define metamacro_foreach_cxt_recursive32(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31) \
    metamacro_foreach_cxt_recursive31(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30) \
    SEP \
    MACRO(31, CONTEXT, _31)

#define metamacro_foreach_cxt_recursive33(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32) \
    metamacro_foreach_cxt_recursive32(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31) \
    SEP \
    MACRO(32, CONTEXT, _32)

#define metamacro_foreach_cxt_recursive34(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33) \
    metamacro_foreach_cxt_recursive33(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32) \
    SEP \
    MACRO(33, CONTEXT, _33)

#define metamacro_foreach_cxt_recursive35(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34) \
    metamacro_foreach_cxt_recursive34(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33) \
    SEP \
    MACRO(34, CONTEXT, _34)

#define metamacro_foreach_cxt_recursive36(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35) \
    metamacro_foreach_cxt_recursive35(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34) \
    SEP \
    MACRO(35, CONTEXT, _35)

#define metamacro_foreach_cxt_recursive37(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36) \
    metamacro_foreach_cxt_recursive36(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35) \
    SEP \
    MACRO(36, CONTEXT, _36)

#define metamacro_foreach_cxt_recursive38(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37) \
    metamacro_foreach_cxt_recursive37(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36) \
    SEP \
    MACRO(37, CONTEXT, _37)

#define metamacro_foreach_cxt_recursive39(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38) \
    metamacro_foreach_cxt_recursive38(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37) \
    SEP \
    MACRO(38, CONTEXT, _38)

#define metamacro_foreach_cxt_recursive40(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39) \
    metamacro_foreach_cxt_recursive39(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38) \
    SEP \
    MACRO(39, CONTEXT, _39)

#define metamacro_foreach_cxt_recursive41(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40) \
    metamacro_foreach_cxt_recursive40(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39) \
    SEP \
    MACRO(40, CONTEXT, _40)

#define metamacro_foreach_cxt_recursive42(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41) \
    metamacro_foreach_cxt_recursive41(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40) \
    SEP \
    MACRO(41, CONTEXT, _41)

#define metamacro_foreach_cxt_recursive43(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42) \
    metamacro_foreach_cxt_recursive42(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41) \
    SEP \
    MACRO(42, CONTEXT, _42)

#define metamacro_foreach_cxt_recursive44(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43) \
    metamacro_foreach_cxt_recursive43(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42) \
    SEP \
    MACRO(43, CONTEXT, _43)

#define metamacro_foreach_cxt_recursive45(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44) \
    metamacro_foreach_cxt_recursive44(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43) \
    SEP \
    MACRO(44, CONTEXT, _44)

#define metamacro_foreach_cxt_recursive46(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45) \
    metamacro_foreach_cxt_recursive45(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44) \
    SEP \
    MACRO(45, CONTEXT, _45)

#define metamacro_foreach_cxt_recursive47(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46) \
    metamacro_foreach_cxt_recursive46(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45) \
    SEP \
    MACRO(46, CONTEXT, _46)

#define metamacro_foreach_cxt_recursive48(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47) \
    metamacro_foreach_cxt_recursive47(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46) \
    SEP \
    MACRO(47, CONTEXT, _47)

#define metamacro_foreach_cxt_recursive49(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48) \
    metamacro_foreach_cxt_recursive48(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47) \
    SEP \
    MACRO(48, CONTEXT, _48)

#define metamacro_foreach_cxt_recursive50(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49) \
    metamacro_foreach_cxt_recursive49(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48) \
    SEP \
    MACRO(49, CONTEXT, _49)
																														  
// metamacro_foreach_cxt_recursive_list expansions
#define metamacro_foreach_cxt_recursive_list0(MACRO, CONTEXT)
#define metamacro_foreach_cxt_recursive_list1(MACRO, CONTEXT, _0) MACRO(0, CONTEXT, _0)

#define metamacro_foreach_cxt_recursive_list2(MACRO, CONTEXT, _0, _1) \
    metamacro_foreach_cxt_recursive_list1(MACRO, CONTEXT, _0), \
    MACRO(1, CONTEXT, _1)

#define metamacro_foreach_cxt_recursive_list3(MACRO, CONTEXT, _0, _1, _2) \
    metamacro_foreach_cxt_recursive_list2(MACRO, CONTEXT, _0, _1), \
    MACRO(2, CONTEXT, _2)

#define metamacro_foreach_cxt_recursive_list4(MACRO, CONTEXT, _0, _1, _2, _3) \
    metamacro_foreach_cxt_recursive_list3(MACRO, CONTEXT, _0, _1, _2), \
    MACRO(3, CONTEXT, _3)

#define metamacro_foreach_cxt_recursive_list5(MACRO, CONTEXT, _0, _1, _2, _3, _4) \
    metamacro_foreach_cxt_recursive_list4(MACRO, CONTEXT, _0, _1, _2, _3), \
    MACRO(4, CONTEXT, _4)

#define metamacro_foreach_cxt_recursive_list6(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5) \
    metamacro_foreach_cxt_recursive_list5(MACRO, CONTEXT, _0, _1, _2, _3, _4), \
    MACRO(5, CONTEXT, _5)

#define metamacro_foreach_cxt_recursive_list7(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6) \
    metamacro_foreach_cxt_recursive_list6(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5), \
    MACRO(6, CONTEXT, _6)

#define metamacro_foreach_cxt_recursive_list8(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7) \
    metamacro_foreach_cxt_recursive_list7(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6), \
    MACRO(7, CONTEXT, _7)

#define metamacro_foreach_cxt_recursive_list9(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8) \
    metamacro_foreach_cxt_recursive_list8(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7), \
    MACRO(8, CONTEXT, _8)

#define metamacro_foreach_cxt_recursive_list10(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9) \
    metamacro_foreach_cxt_recursive_list9(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8), \
    MACRO(9, CONTEXT, _9)

#define metamacro_foreach_cxt_recursive_list11(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) \
    metamacro_foreach_cxt_recursive_list10(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9), \
    MACRO(10, CONTEXT, _10)

#define metamacro_foreach_cxt_recursive_list12(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) \
    metamacro_foreach_cxt_recursive_list11(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10), \
    MACRO(11, CONTEXT, _11)

#define metamacro_foreach_cxt_recursive_list13(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) \
    metamacro_foreach_cxt_recursive_list12(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11), \
    MACRO(12, CONTEXT, _12)

#define metamacro_foreach_cxt_recursive_list14(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) \
    metamacro_foreach_cxt_recursive_list13(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12), \
    MACRO(13, CONTEXT, _13)

#define metamacro_foreach_cxt_recursive_list15(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) \
    metamacro_foreach_cxt_recursive_list14(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13), \
    MACRO(14, CONTEXT, _14)

#define metamacro_foreach_cxt_recursive_list16(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) \
    metamacro_foreach_cxt_recursive_list15(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14), \
    MACRO(15, CONTEXT, _15)

#define metamacro_foreach_cxt_recursive_list17(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) \
    metamacro_foreach_cxt_recursive_list16(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15), \
    MACRO(16, CONTEXT, _16)

#define metamacro_foreach_cxt_recursive_list18(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) \
    metamacro_foreach_cxt_recursive_list17(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16), \
    MACRO(17, CONTEXT, _17)

#define metamacro_foreach_cxt_recursive_list19(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) \
    metamacro_foreach_cxt_recursive_list18(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17), \
    MACRO(18, CONTEXT, _18)

#define metamacro_foreach_cxt_recursive_list20(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) \
    metamacro_foreach_cxt_recursive_list19(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18), \
    MACRO(19, CONTEXT, _19)

#define metamacro_foreach_cxt_recursive_list21(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20) \
    metamacro_foreach_cxt_recursive_list20(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19), \
    MACRO(20, CONTEXT, _20)

#define metamacro_foreach_cxt_recursive_list22(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21) \
    metamacro_foreach_cxt_recursive_list21(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20), \
    MACRO(21, CONTEXT, _21)

#define metamacro_foreach_cxt_recursive_list23(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22) \
    metamacro_foreach_cxt_recursive_list22(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21), \
    MACRO(22, CONTEXT, _22)

#define metamacro_foreach_cxt_recursive_list24(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23) \
    metamacro_foreach_cxt_recursive_list23(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22), \
    MACRO(23, CONTEXT, _23)

#define metamacro_foreach_cxt_recursive_list25(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24) \
    metamacro_foreach_cxt_recursive_list24(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23), \
    MACRO(24, CONTEXT, _24)

#define metamacro_foreach_cxt_recursive_list26(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25) \
    metamacro_foreach_cxt_recursive_list25(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24), \
    MACRO(25, CONTEXT, _25)

#define metamacro_foreach_cxt_recursive_list27(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26) \
    metamacro_foreach_cxt_recursive_list26(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25), \
    MACRO(26, CONTEXT, _26)

#define metamacro_foreach_cxt_recursive_list28(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27) \
    metamacro_foreach_cxt_recursive_list27(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26), \
    MACRO(27, CONTEXT, _27)

#define metamacro_foreach_cxt_recursive_list29(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28) \
    metamacro_foreach_cxt_recursive_list28(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27), \
    MACRO(28, CONTEXT, _28)

#define metamacro_foreach_cxt_recursive_list30(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29) \
    metamacro_foreach_cxt_recursive_list29(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28), \
    MACRO(29, CONTEXT, _29)

#define metamacro_foreach_cxt_recursive_list31(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30) \
    metamacro_foreach_cxt_recursive_list30(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29), \
    MACRO(30, CONTEXT, _30)

#define metamacro_foreach_cxt_recursive_list32(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31) \
    metamacro_foreach_cxt_recursive_list31(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30), \
    MACRO(31, CONTEXT, _31)

#define metamacro_foreach_cxt_recursive_list33(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32) \
    metamacro_foreach_cxt_recursive_list32(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31), \
    MACRO(32, CONTEXT, _32)

#define metamacro_foreach_cxt_recursive_list34(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33) \
    metamacro_foreach_cxt_recursive_list33(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32), \
    MACRO(33, CONTEXT, _33)

#define metamacro_foreach_cxt_recursive_list35(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34) \
    metamacro_foreach_cxt_recursive_list34(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33), \
    MACRO(34, CONTEXT, _34)

#define metamacro_foreach_cxt_recursive_list36(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35) \
    metamacro_foreach_cxt_recursive_list35(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34), \
    MACRO(35, CONTEXT, _35)

#define metamacro_foreach_cxt_recursive_list37(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36) \
    metamacro_foreach_cxt_recursive_list36(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35), \
    MACRO(36, CONTEXT, _36)

#define metamacro_foreach_cxt_recursive_list38(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37) \
    metamacro_foreach_cxt_recursive_list37(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36), \
    MACRO(37, CONTEXT, _37)

#define metamacro_foreach_cxt_recursive_list39(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38) \
    metamacro_foreach_cxt_recursive_list38(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37), \
    MACRO(38, CONTEXT, _38)

#define metamacro_foreach_cxt_recursive_list40(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39) \
    metamacro_foreach_cxt_recursive_list39(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38), \
    MACRO(39, CONTEXT, _39)

#define metamacro_foreach_cxt_recursive_list41(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40) \
    metamacro_foreach_cxt_recursive_list40(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39), \
    MACRO(40, CONTEXT, _40)

#define metamacro_foreach_cxt_recursive_list42(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41) \
    metamacro_foreach_cxt_recursive_list41(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40), \
    MACRO(41, CONTEXT, _41)

#define metamacro_foreach_cxt_recursive_list43(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42) \
    metamacro_foreach_cxt_recursive_list42(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41), \
    MACRO(42, CONTEXT, _42)

#define metamacro_foreach_cxt_recursive_list44(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43) \
    metamacro_foreach_cxt_recursive_list43(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42), \
    MACRO(43, CONTEXT, _43)

#define metamacro_foreach_cxt_recursive_list45(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44) \
    metamacro_foreach_cxt_recursive_list44(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43), \
    MACRO(44, CONTEXT, _44)

#define metamacro_foreach_cxt_recursive_list46(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45) \
    metamacro_foreach_cxt_recursive_list45(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44), \
    MACRO(45, CONTEXT, _45)

#define metamacro_foreach_cxt_recursive_list47(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46) \
    metamacro_foreach_cxt_recursive_list46(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45), \
    MACRO(46, CONTEXT, _46)

#define metamacro_foreach_cxt_recursive_list48(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47) \
    metamacro_foreach_cxt_recursive_list47(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46), \
    MACRO(47, CONTEXT, _47)

#define metamacro_foreach_cxt_recursive_list49(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48) \
    metamacro_foreach_cxt_recursive_list48(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47), \
    MACRO(48, CONTEXT, _48)

#define metamacro_foreach_cxt_recursive_list50(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49) \
    metamacro_foreach_cxt_recursive_list49(MACRO, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48), \
    MACRO(49, CONTEXT, _49)

// metamacro_for_cxt expansions
#define metamacro_for_cxt0(MACRO, SEP, CONTEXT)
#define metamacro_for_cxt1(MACRO, SEP, CONTEXT) MACRO(0, CONTEXT)

#define metamacro_for_cxt2(MACRO, SEP, CONTEXT) \
    metamacro_for_cxt1(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(1, CONTEXT)

#define metamacro_for_cxt3(MACRO, SEP, CONTEXT) \
    metamacro_for_cxt2(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(2, CONTEXT)

#define metamacro_for_cxt4(MACRO, SEP, CONTEXT) \
    metamacro_for_cxt3(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(3, CONTEXT)

#define metamacro_for_cxt5(MACRO, SEP, CONTEXT) \
    metamacro_for_cxt4(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(4, CONTEXT)

#define metamacro_for_cxt6(MACRO, SEP, CONTEXT) \
    metamacro_for_cxt5(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(5, CONTEXT)

#define metamacro_for_cxt7(MACRO, SEP, CONTEXT) \
    metamacro_for_cxt6(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(6, CONTEXT)

#define metamacro_for_cxt8(MACRO, SEP, CONTEXT) \
    metamacro_for_cxt7(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(7, CONTEXT)

#define metamacro_for_cxt9(MACRO, SEP, CONTEXT) \
    metamacro_for_cxt8(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(8, CONTEXT)

#define metamacro_for_cxt10(MACRO, SEP, CONTEXT) \
    metamacro_for_cxt9(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(9, CONTEXT)

#define metamacro_for_cxt11(MACRO, SEP, CONTEXT) \
    metamacro_for_cxt10(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(10, CONTEXT)

#define metamacro_for_cxt12(MACRO, SEP, CONTEXT) \
    metamacro_for_cxt11(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(11, CONTEXT)

#define metamacro_for_cxt13(MACRO, SEP, CONTEXT) \
    metamacro_for_cxt12(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(12, CONTEXT)

#define metamacro_for_cxt14(MACRO, SEP, CONTEXT) \
    metamacro_for_cxt13(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(13, CONTEXT)

#define metamacro_for_cxt15(MACRO, SEP, CONTEXT) \
    metamacro_for_cxt14(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(14, CONTEXT)

#define metamacro_for_cxt16(MACRO, SEP, CONTEXT) \
    metamacro_for_cxt15(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(15, CONTEXT)

#define metamacro_for_cxt17(MACRO, SEP, CONTEXT) \
    metamacro_for_cxt16(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(16, CONTEXT)

#define metamacro_for_cxt18(MACRO, SEP, CONTEXT) \
    metamacro_for_cxt17(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(17, CONTEXT)

#define metamacro_for_cxt19(MACRO, SEP, CONTEXT) \
    metamacro_for_cxt18(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(18, CONTEXT)

#define metamacro_for_cxt20(MACRO, SEP, CONTEXT) \
    metamacro_for_cxt19(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(19, CONTEXT)

// metamacro_if_eq expansions
#define metamacro_if_eq0(VALUE) \
    metamacro_concat(metamacro_if_eq0_, VALUE)

#define metamacro_if_eq0_0(...) __VA_ARGS__ metamacro_consume_
#define metamacro_if_eq0_1(...) metamacro_expand_
#define metamacro_if_eq0_2(...) metamacro_expand_
#define metamacro_if_eq0_3(...) metamacro_expand_
#define metamacro_if_eq0_4(...) metamacro_expand_
#define metamacro_if_eq0_5(...) metamacro_expand_
#define metamacro_if_eq0_6(...) metamacro_expand_
#define metamacro_if_eq0_7(...) metamacro_expand_
#define metamacro_if_eq0_8(...) metamacro_expand_
#define metamacro_if_eq0_9(...) metamacro_expand_
#define metamacro_if_eq0_10(...) metamacro_expand_
#define metamacro_if_eq0_11(...) metamacro_expand_
#define metamacro_if_eq0_12(...) metamacro_expand_
#define metamacro_if_eq0_13(...) metamacro_expand_
#define metamacro_if_eq0_14(...) metamacro_expand_
#define metamacro_if_eq0_15(...) metamacro_expand_
#define metamacro_if_eq0_16(...) metamacro_expand_
#define metamacro_if_eq0_17(...) metamacro_expand_
#define metamacro_if_eq0_18(...) metamacro_expand_
#define metamacro_if_eq0_19(...) metamacro_expand_
#define metamacro_if_eq0_20(...) metamacro_expand_

#define metamacro_if_eq1(VALUE) metamacro_if_eq0(metamacro_dec(VALUE))
#define metamacro_if_eq2(VALUE) metamacro_if_eq1(metamacro_dec(VALUE))
#define metamacro_if_eq3(VALUE) metamacro_if_eq2(metamacro_dec(VALUE))
#define metamacro_if_eq4(VALUE) metamacro_if_eq3(metamacro_dec(VALUE))
#define metamacro_if_eq5(VALUE) metamacro_if_eq4(metamacro_dec(VALUE))
#define metamacro_if_eq6(VALUE) metamacro_if_eq5(metamacro_dec(VALUE))
#define metamacro_if_eq7(VALUE) metamacro_if_eq6(metamacro_dec(VALUE))
#define metamacro_if_eq8(VALUE) metamacro_if_eq7(metamacro_dec(VALUE))
#define metamacro_if_eq9(VALUE) metamacro_if_eq8(metamacro_dec(VALUE))
#define metamacro_if_eq10(VALUE) metamacro_if_eq9(metamacro_dec(VALUE))
#define metamacro_if_eq11(VALUE) metamacro_if_eq10(metamacro_dec(VALUE))
#define metamacro_if_eq12(VALUE) metamacro_if_eq11(metamacro_dec(VALUE))
#define metamacro_if_eq13(VALUE) metamacro_if_eq12(metamacro_dec(VALUE))
#define metamacro_if_eq14(VALUE) metamacro_if_eq13(metamacro_dec(VALUE))
#define metamacro_if_eq15(VALUE) metamacro_if_eq14(metamacro_dec(VALUE))
#define metamacro_if_eq16(VALUE) metamacro_if_eq15(metamacro_dec(VALUE))
#define metamacro_if_eq17(VALUE) metamacro_if_eq16(metamacro_dec(VALUE))
#define metamacro_if_eq18(VALUE) metamacro_if_eq17(metamacro_dec(VALUE))
#define metamacro_if_eq19(VALUE) metamacro_if_eq18(metamacro_dec(VALUE))
#define metamacro_if_eq20(VALUE) metamacro_if_eq19(metamacro_dec(VALUE))

// metamacro_if_eq_recursive expansions
#define metamacro_if_eq_recursive0(VALUE) \
    metamacro_concat(metamacro_if_eq_recursive0_, VALUE)

#define metamacro_if_eq_recursive0_0(...) __VA_ARGS__ metamacro_consume_
#define metamacro_if_eq_recursive0_1(...) metamacro_expand_
#define metamacro_if_eq_recursive0_2(...) metamacro_expand_
#define metamacro_if_eq_recursive0_3(...) metamacro_expand_
#define metamacro_if_eq_recursive0_4(...) metamacro_expand_
#define metamacro_if_eq_recursive0_5(...) metamacro_expand_
#define metamacro_if_eq_recursive0_6(...) metamacro_expand_
#define metamacro_if_eq_recursive0_7(...) metamacro_expand_
#define metamacro_if_eq_recursive0_8(...) metamacro_expand_
#define metamacro_if_eq_recursive0_9(...) metamacro_expand_
#define metamacro_if_eq_recursive0_10(...) metamacro_expand_
#define metamacro_if_eq_recursive0_11(...) metamacro_expand_
#define metamacro_if_eq_recursive0_12(...) metamacro_expand_
#define metamacro_if_eq_recursive0_13(...) metamacro_expand_
#define metamacro_if_eq_recursive0_14(...) metamacro_expand_
#define metamacro_if_eq_recursive0_15(...) metamacro_expand_
#define metamacro_if_eq_recursive0_16(...) metamacro_expand_
#define metamacro_if_eq_recursive0_17(...) metamacro_expand_
#define metamacro_if_eq_recursive0_18(...) metamacro_expand_
#define metamacro_if_eq_recursive0_19(...) metamacro_expand_
#define metamacro_if_eq_recursive0_20(...) metamacro_expand_

#define metamacro_if_eq_recursive1(VALUE) metamacro_if_eq_recursive0(metamacro_dec(VALUE))
#define metamacro_if_eq_recursive2(VALUE) metamacro_if_eq_recursive1(metamacro_dec(VALUE))
#define metamacro_if_eq_recursive3(VALUE) metamacro_if_eq_recursive2(metamacro_dec(VALUE))
#define metamacro_if_eq_recursive4(VALUE) metamacro_if_eq_recursive3(metamacro_dec(VALUE))
#define metamacro_if_eq_recursive5(VALUE) metamacro_if_eq_recursive4(metamacro_dec(VALUE))
#define metamacro_if_eq_recursive6(VALUE) metamacro_if_eq_recursive5(metamacro_dec(VALUE))
#define metamacro_if_eq_recursive7(VALUE) metamacro_if_eq_recursive6(metamacro_dec(VALUE))
#define metamacro_if_eq_recursive8(VALUE) metamacro_if_eq_recursive7(metamacro_dec(VALUE))
#define metamacro_if_eq_recursive9(VALUE) metamacro_if_eq_recursive8(metamacro_dec(VALUE))
#define metamacro_if_eq_recursive10(VALUE) metamacro_if_eq_recursive9(metamacro_dec(VALUE))
#define metamacro_if_eq_recursive11(VALUE) metamacro_if_eq_recursive10(metamacro_dec(VALUE))
#define metamacro_if_eq_recursive12(VALUE) metamacro_if_eq_recursive11(metamacro_dec(VALUE))
#define metamacro_if_eq_recursive13(VALUE) metamacro_if_eq_recursive12(metamacro_dec(VALUE))
#define metamacro_if_eq_recursive14(VALUE) metamacro_if_eq_recursive13(metamacro_dec(VALUE))
#define metamacro_if_eq_recursive15(VALUE) metamacro_if_eq_recursive14(metamacro_dec(VALUE))
#define metamacro_if_eq_recursive16(VALUE) metamacro_if_eq_recursive15(metamacro_dec(VALUE))
#define metamacro_if_eq_recursive17(VALUE) metamacro_if_eq_recursive16(metamacro_dec(VALUE))
#define metamacro_if_eq_recursive18(VALUE) metamacro_if_eq_recursive17(metamacro_dec(VALUE))
#define metamacro_if_eq_recursive19(VALUE) metamacro_if_eq_recursive18(metamacro_dec(VALUE))
#define metamacro_if_eq_recursive20(VALUE) metamacro_if_eq_recursive19(metamacro_dec(VALUE))

// metamacro_take expansions
#define metamacro_take0(...)
#define metamacro_take1(...) metamacro_head(__VA_ARGS__)
#define metamacro_take2(...) metamacro_head(__VA_ARGS__), metamacro_take1(metamacro_tail(__VA_ARGS__))
#define metamacro_take3(...) metamacro_head(__VA_ARGS__), metamacro_take2(metamacro_tail(__VA_ARGS__))
#define metamacro_take4(...) metamacro_head(__VA_ARGS__), metamacro_take3(metamacro_tail(__VA_ARGS__))
#define metamacro_take5(...) metamacro_head(__VA_ARGS__), metamacro_take4(metamacro_tail(__VA_ARGS__))
#define metamacro_take6(...) metamacro_head(__VA_ARGS__), metamacro_take5(metamacro_tail(__VA_ARGS__))
#define metamacro_take7(...) metamacro_head(__VA_ARGS__), metamacro_take6(metamacro_tail(__VA_ARGS__))
#define metamacro_take8(...) metamacro_head(__VA_ARGS__), metamacro_take7(metamacro_tail(__VA_ARGS__))
#define metamacro_take9(...) metamacro_head(__VA_ARGS__), metamacro_take8(metamacro_tail(__VA_ARGS__))
#define metamacro_take10(...) metamacro_head(__VA_ARGS__), metamacro_take9(metamacro_tail(__VA_ARGS__))
#define metamacro_take11(...) metamacro_head(__VA_ARGS__), metamacro_take10(metamacro_tail(__VA_ARGS__))
#define metamacro_take12(...) metamacro_head(__VA_ARGS__), metamacro_take11(metamacro_tail(__VA_ARGS__))
#define metamacro_take13(...) metamacro_head(__VA_ARGS__), metamacro_take12(metamacro_tail(__VA_ARGS__))
#define metamacro_take14(...) metamacro_head(__VA_ARGS__), metamacro_take13(metamacro_tail(__VA_ARGS__))
#define metamacro_take15(...) metamacro_head(__VA_ARGS__), metamacro_take14(metamacro_tail(__VA_ARGS__))
#define metamacro_take16(...) metamacro_head(__VA_ARGS__), metamacro_take15(metamacro_tail(__VA_ARGS__))
#define metamacro_take17(...) metamacro_head(__VA_ARGS__), metamacro_take16(metamacro_tail(__VA_ARGS__))
#define metamacro_take18(...) metamacro_head(__VA_ARGS__), metamacro_take17(metamacro_tail(__VA_ARGS__))
#define metamacro_take19(...) metamacro_head(__VA_ARGS__), metamacro_take18(metamacro_tail(__VA_ARGS__))
#define metamacro_take20(...) metamacro_head(__VA_ARGS__), metamacro_take19(metamacro_tail(__VA_ARGS__))

// metamacro_drop expansions
#define metamacro_drop0(...) __VA_ARGS__
#define metamacro_drop1(...) metamacro_tail(__VA_ARGS__)
#define metamacro_drop2(...) metamacro_drop1(metamacro_tail(__VA_ARGS__))
#define metamacro_drop3(...) metamacro_drop2(metamacro_tail(__VA_ARGS__))
#define metamacro_drop4(...) metamacro_drop3(metamacro_tail(__VA_ARGS__))
#define metamacro_drop5(...) metamacro_drop4(metamacro_tail(__VA_ARGS__))
#define metamacro_drop6(...) metamacro_drop5(metamacro_tail(__VA_ARGS__))
#define metamacro_drop7(...) metamacro_drop6(metamacro_tail(__VA_ARGS__))
#define metamacro_drop8(...) metamacro_drop7(metamacro_tail(__VA_ARGS__))
#define metamacro_drop9(...) metamacro_drop8(metamacro_tail(__VA_ARGS__))
#define metamacro_drop10(...) metamacro_drop9(metamacro_tail(__VA_ARGS__))
#define metamacro_drop11(...) metamacro_drop10(metamacro_tail(__VA_ARGS__))
#define metamacro_drop12(...) metamacro_drop11(metamacro_tail(__VA_ARGS__))
#define metamacro_drop13(...) metamacro_drop12(metamacro_tail(__VA_ARGS__))
#define metamacro_drop14(...) metamacro_drop13(metamacro_tail(__VA_ARGS__))
#define metamacro_drop15(...) metamacro_drop14(metamacro_tail(__VA_ARGS__))
#define metamacro_drop16(...) metamacro_drop15(metamacro_tail(__VA_ARGS__))
#define metamacro_drop17(...) metamacro_drop16(metamacro_tail(__VA_ARGS__))
#define metamacro_drop18(...) metamacro_drop17(metamacro_tail(__VA_ARGS__))
#define metamacro_drop19(...) metamacro_drop18(metamacro_tail(__VA_ARGS__))
#define metamacro_drop20(...) metamacro_drop19(metamacro_tail(__VA_ARGS__))

#endif
