/***************************************************************************************************
 ***************************************************************************************************
 *
 *	Copyright (c) 2018 - 2024, Networked Embedded Systems Lab, TU Dresden
 *	All rights reserved.
 *
 *	Redistribution and use in source and binary forms, with or without
 *	modification, are permitted provided that the following conditions are met:
 *		* Redistributions of source code must retain the above copyright
 *		  notice, this list of conditions and the following disclaimer.
 *		* Redistributions in binary form must reproduce the above copyright
 *		  notice, this list of conditions and the following disclaimer in the
 *		  documentation and/or other materials provided with the distribution.
 *		* Neither the name of the NES Lab or TU Dresden nor the
 *		  names of its contributors may be used to endorse or promote products
 *		  derived from this software without specific prior written permission.
 *
 *	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 *	ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *	DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
 *	DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *	ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ***********************************************************************************************//**
 *
 *	@file					gpi/tools.h
 *
 *	@brief					Common macros, types, etc. generally useful to improve code quality
 *							(portability, robustness, readability).
 *
 * @internal
 *	@version				\$Id: f270ad28dc4a104522bad6b4d27b744126d45896 $
 *	@noop @date				git log -1 <filename>
 *
 *	@author					Carsten Herrmann
 * @endinternal
 *
 ***************************************************************************************************

 	@details

	This file contains basic macros and datatypes that are useful in C language programs
	of all kind (not limited to low-level programming) to encapsulate frequently used code
	patterns and avoid fragile constructs, increase robustness, support error handling, make
	code more readable and improve code quality in general.

	Such macros are common in many projects, actually often under the same or similar names.
	For this reason, tools.h is implemented as an almost self-contained file with only negligible
	dependencies to other GPI files (such that it could be separated easily and used stand-alone).
	To underline this, the names used in tools.h do not start with `GPI_...` and, when reasonable,
	adopt the names of equivalent macros from other projects or libraries.

	@par Name Conflicts

	The use of tools.h (incl. GPI) together with other libraries that provide the mentioned kind
	of general purpose macros in the same source modul can lead to name collisions. To avoid such
	conflicts, the following strategies could be implemented.

	All macro definitions in tools.h are enclosed in `#ifndef GPI_DONT_PROVIDE_...`, making it
	possible to disable the redefinition of an existing macro. Of course, this requires to check
	carefully that the non-GPI macro implements the same functionality. Further, the header file
	containing the definition of the other macro must be included in tools.h to provide the
	functionality. This could be implemented by an additional `GPI_TOOLS_EXTRA_INCLUDE` macro.
	Beyond that, the tools.h implementation could be provided as `GPI_...` with a non-`GPI_...`
	alias, and `GPI_DONT_PROVIDE_...` could than be limited to the alias.

	The other way around, tools.h could `#undef` existing macros before redefinition, together
	with an optional warning or error message. Again, this requires to check that the non-GPI
	macro implements the same functionality. `GPI_TOOLS_EXTRA_INCLUDE` would also be necessary.

	Both strategies could also be mixed, i.e. individually select don't provide or overwrite for
	each involved macro.

	@note None of these strategies is implemented yet, see TODO.

	@todo Provide functionality to resolve conflicts with similar macros from other libraries.

 **************************************************************************************************/

#ifndef __GPI_TOOLS_H__
#define __GPI_TOOLS_H__

//**************************************************************************************************
//***** Includes ***********************************************************************************

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

//**************************************************************************************************
//***** Global Defines and Consts ******************************************************************

//**************************************************************************************************
/// @name Macro Expansion Helper Macros
///
/// The following macros can be used to control intermediate expansion whenever macros
/// or their names are to be combined or stringified.
/// @{

/// @brief Stringify args with intermediate macro expansion.
/// @details Expands all macros in the argument list and converts the result to a string.
//  internal: two-step approach is necessary (do not remove it!)
#define STRINGIFY(...)    STRINGIFY2(__VA_ARGS__)
#define STRINGIFY2(...)   #__VA_ARGS__

/// @brief Concatenate args with intermediate macro expansion.
/// @details
/// Expands all macros in the argument list and concatenates the result,
/// which in turn gets expanded in case it yields a macro name
/// (i.e. expansion of each argument -> concatenation -> final expansion).
/// At least two arguments are required, up to 10 are possible
/// (can be extended if necessary, see implementation).
///
/// For an example, see @ref TEST_EXPANSION().
/// @sa CONCAT_NOEXP(), TEST_EXPANSION()
#define CONCAT(a, b, ...) CONCAT_NOEXP(a, b, __VA_ARGS__)

/// @brief Concatenate args without intermediate macro expansion.
/// @details
/// Concatenates all arguments without macro expansion,
/// then expands the result in case it yields a macro name
/// (i.e. concatenation of each argument *as is* -> final expansion).
/// Concatenates up to 10 arguments (can be extended if necessary, see implementation).
///
/// For an example, see @ref TEST_EXPANSION().
/// @sa CONCAT(), TEST_EXPANSION()
//
//  internal: two-step approach is essential (do not remove it!)
#define CONCAT_NOEXP(...) CONCAT_NOEXP2(dummy, ##__VA_ARGS__, , , , , , , , , )
#define CONCAT_NOEXP2(dummy, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, ...)                         \
    _1##_2##_3##_4##_5##_6##_7##_8##_9##_10

/// @brief Test expansion of a macro.
/// @details
/// This macro is provided as a diagnostic tool for temporary use during development.
/// It generates an error message that shows the expansion of macro \a x
/// at the place where TEST_EXPANSION() is called.
///
/// Example:
/// @code
///		#define		A	1
///		#define		B	2
///		#define		C	3
///		#define		AB	4
///		#define		ABC	5
///
///		TEST_EXPANSION(AB);								// -> 4
///		TEST_EXPANSION(CONCAT(A, B, C));				// -> 123
///		TEST_EXPANSION(CONCAT_NOEXP(A, B, C));			// -> 5
///		TEST_EXPANSION(CONCAT(CONCAT_NOEXP(A, B), C));	// -> 43
/// @endcode
#define TEST_EXPANSION(x)                                             _Pragma(STRINGIFY(GCC error STRINGIFY(x)))

/// @}
//**************************************************************************************************
/// @name Macro Variadic Arguments Handling
///
/// The following macros support the handling of variadic macro arguments (i.e. arguments mapped
/// to ... and \__VA_ARGS__) in function-like preprocessor macros.
/// @{

/// @brief Get number of variadic args (\__VA_ARGS__) in a function-like preprocessor macro.
/// @details
/// The current implementation handles 0...10 arguments (which can be extended
/// straightforwardly if required).
///
/// We provide two macros for this purpose, VA_NUM() and VA_NARG(), which have slightly different
/// pros and cons. VA_NUM() gets (finally) resolved at compile time, while VA_NARG() is completely
/// resolved by the preprocessor. In consequence,
/// * VA_NUM() catches the case of being called with too many arguments (it triggers an assertion
///   in this case), while VA_NARG() will yield a wrong result in this situation.
/// * On the other hand, VA_NARG() can be evaluated in preprocessor expressions (e.g. in
///   `#error ...`), which is not possible with VA_NUM().
/// .
/// Hence, VA_NARG() is a bit more generic, while VA_NUM() is a bit more reliable regarding
/// unknown callers.
///
/// @sa VA_NUM(), VA_NARG(), VA_NARG_NOEXP()
#define VA_NUM(a...)                                                  VA_NUM1(a)

/// @copydoc VA_NUM()
#define VA_NARG(...)                                                  VA_NARG1(0, ##__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#define VA_NARG1(...)                                                 VA_NARG2(__VA_ARGS__)
#define VA_NARG2(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, n, ...) n

/// @copydoc VA_NUM()
///
/// VA_NARG_NOEXP() is a special version of VA_NARG() that does not expand macros in the arguments.
/// This can lead to different results in case macros contain commas, as in the following example.
/// @code
/// #define TEST	aa,bb
///
/// int x = VA_NARG(TEST);          // x = 2
/// int x = VA_NARG_NOEXP(TEST);    // x = 1
/// @endcode
#define VA_NARG_NOEXP(...)                                            VA_NARG2(0, ##__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

/// @brief Get size of variadic args (\__VA_ARGS__) in a function-like preprocessor macro.
/// @details
/// VA_SIZE() can be used to determine the size of a variable parameter list, more precisely the
/// size of the stack frame that is used to call a variadic function like `printf()` with the
/// given parameter list.
///
/// The current implementation handles 0...10 arguments (can be extended straightforwardly
/// if required).
/// @impdetails VA_SIZE() depends on the platform-specific VA_SIZE_GRANULARITY, which must be
/// configured carefully to be consistent with the generated machine code.
#define VA_SIZE(a...)                                                 VA_SIZE1(a)

/// @brief Expand and return i-th argument (i.e. i-th element of a comma-separated list).
/// @details
/// Index \a i is 0-based.
/// The current implementation handles \a i = 0, ..., 9 (can be extended straightforwardly
/// if required).
//
//  internal: two-step approach is necessary (do not remove it!)
#define VA_ARG_i(i, ...)                                              VA_ARG##i(__VA_ARGS__)

/// @}
//**************************************************************************************************
/// @name Assertions (in particular compile-time assertions)
///
/// The concept of [assertions](https://en.wikipedia.org/wiki/Assertion_(software_development))
/// can help a lot when developing and debugging programs (we strongly recommend to make use of it).
/// There are two kinds of assertions:
/// 1. Runtime assertions, which are checked at runtime.
///    They are very flexible, but cost some processing power, as they generate extra machine code.
/// 2. Static assertions, which are checked at compile-time.
///    They are less flexible because the condition must resolve to a constant expression (to
///    allow for compile-time evaluation), but come at no cost regarding the generated program
///    (they get completely removed, e.g. by dead-code elimination optimization steps), and ---
///    maybe even more important --- trigger inevitably if not fulfilled (emitting compilation
///    errors, in contrast to runtime assertions which trigger not before program execution
///    reaches the corresponding statements).
/// .
/// Hence, use static assertions where possible. At other places, runtime assertions are better
/// than no assertions.
///
/// The C programming language provides runtime assertions in
/// [<assert.h>](https://en.wikipedia.org/wiki/Assert.h) for a long time.
/// Static assertions have been officially introduced with C11 (`static_assert` keyword).
/// The following macros implement all kinds of assertions with and without C11 support.
/// @{

// internal core construct to implement compile-time assertions
// note: make sure that bitfield does not contain unused bits to avoid -Wpadded warnings (if enabled)
#define ASSERT_CT_CORE(condition, ...)                                                             \
    sizeof(struct __attribute__((packed)) {                                                        \
        int8_t assertion_failed__##__VA_ARGS__ : 8 - 9 * !(condition);                             \
    })

/// @brief compile-time assertion inside a function body.
/// @details The assertion is evaluated at compile-time and leads to a compilation error if the
/// check fails. It does not generate machine code.
/// @param condition	condition that is asserted to be true
/// @param ...			(optional) identifier that makes the potential error message more meaningful
/// @sa ASSERT_CT_STATIC(), ASSERT_CT_EVAL()
/// @impdetails TODO: accommodate to static_assert() (ISO C11) after that has become common
#define ASSERT_CT(condition, ...)      ((void) ASSERT_CT_CORE(condition, ##__VA_ARGS__))

/// @brief compile-time assertion inside an expression.
/// @details ASSERT_CT_EVAL() is a function-like variant of ASSERT_CT(). It basically works
/// like ASSERT_CT(), but provides a return value
/// (0 if the assertion is true, irrelevant otherwise due to the generated compilation error).
/// This makes it possible to check the assertion inside of another expression.
/// @par Example
/// @code
///		#define DOUBLE(x)	( (2 * (x)) + ASSERT_CT_EVAL((x) < 128, value_range_exceeded) )
///
///		int a = DOUBLE(100);	// -> a = 200
///		int b = DOUBLE(200);	// -> assertion failed ... value_range_exceeded ...
/// @endcode
/// @sa ASSERT_CT()
#define ASSERT_CT_EVAL(condition, ...) (!ASSERT_CT_CORE(condition, ##__VA_ARGS__))

/// @brief compile-time assertion at file scope.
/// @details ASSERT_CT_STATIC() is a variant of ASSERT_CT() that can be used at file scope
/// (i.e., outside of functions).
/// @sa ASSERT_CT(), ASSERT_CT_EVAL()
//#define ASSERT_CT_STATIC(condition, ...)	ASSERT_CT_STATIC2(__COUNTER__, condition, __VA_ARGS__)
#define ASSERT_CT_STATIC(condition, ...)                                                           \
    static inline void CONCAT(assert_dummy_, __COUNTER__)(void)                                    \
    {                                                                                              \
        ASSERT_CT(condition, ##__VA_ARGS__);                                                       \
    }

/// @brief compile-time assertion warning inside a function body.
/// @details ASSERT_CT_WARN() is equivalent to ASSERT_CT(), but generates a warning instead of an error.
/// @sa ASSERT_CT(), ASSERT_CT_WARN_STATIC()
//
// Workaround for MSPGCC version <= 4.6.3, GCC diagnostic push/pop commands are ignored
#if ((__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__) <= 40603)
  #define ASSERT_CT_WARN(condition, ...)                                                           \
      do {                                                                                         \
          _Pragma("GCC diagnostic warning \"-Wpadded\"");                                          \
          struct T_                                                                                \
          {                                                                                        \
              uint8_t  a[1 + !!(condition)];                                                       \
              uint16_t assertion_warning__##__VA_ARGS__;                                           \
          };                                                                                       \
          _Pragma("GCC diagnostic ignored \"-Wpadded\"");                                          \
      }                                                                                            \
      while (0)
#else
  #define ASSERT_CT_WARN(condition, ...)                                                           \
      do {                                                                                         \
          _Pragma("GCC diagnostic push");                                                          \
          _Pragma("GCC diagnostic warning \"-Wpadded\"");                                          \
          struct T_                                                                                \
          {                                                                                        \
              uint8_t  a[1 + !!(condition)];                                                       \
              uint16_t assertion_warning__##__VA_ARGS__;                                           \
          };                                                                                       \
          _Pragma("GCC diagnostic pop");                                                           \
      }                                                                                            \
      while (0)
#endif

/// @brief compile-time assertion warning at file scope.
/// @details ASSERT_CT_WARN_STATIC() is equivalent to ASSERT_CT_STATIC(),
/// but generates a warning instead of an error.
/// @sa ASSERT_CT_WARN(), ASSERT_CT_STATIC()
#define ASSERT_CT_WARN_STATIC(condition, ...)                                                      \
    static inline void CONCAT(assert_dummy_, __COUNTER__)(void)                                    \
    {                                                                                              \
        ASSERT_CT_WARN(condition, ##__VA_ARGS__);                                                  \
    }

/// @brief determine if x is a constant expression.
/// @details A common use case for IS_CONST_EXPRESSION() is to ensure that some macro `M()` can be
/// used only with constants (to prohibit accidental and maybe expensive unfolding). To this end,
/// `M` can be defined as follows:
/// @code #define M(x) (... + ASSERT_CT_EVAL(IS_CONST_EXPRESSION(x))) @endcode
#define IS_CONST_EXPRESSION(x) __builtin_constant_p(x)

/// @brief compile-time or runtime assertion.
/// @details
/// ASSERT() can be used as a "flexible kind" assertion. If possible, the assertion is implemented
/// as a compile-time assertion, otherwise it redirects to the standard assert() macro.
///
/// Defining the special macro ASSERT_WARN_CT before including <tools.h> enables the generation of
/// a warning message whenever ASSERT() cannot be resolved into a compile-time assertion.
/// This can be used as a hint to either rework the condition or explicitly switch to assert().
#define ASSERT(condition, ...)                                                                     \
    do {                                                                                           \
        if (__builtin_constant_p(condition))                                                       \
        {                                                                                          \
            /* here we use variable-length arrays, a feature introduced with C99 */                \
            const int trigger_ = __builtin_constant_p(condition) * !(condition);                   \
            int       assertion_failed_##__VA_ARGS__[1 - 2 * trigger_] __attribute__((unused));    \
        }                                                                                          \
        else                                                                                       \
        {                                                                                          \
            _Pragma("GCC diagnostic push");                                                        \
            _Pragma(ASSERT_DIAG_MODE);                                                             \
            struct T_                                                                              \
            {                                                                                      \
                uint8_t  a[1 + !!__builtin_constant_p(condition)];                                 \
                uint16_t unable_to_evaluate_ASSERT_at_compile_time;                                \
            };                                                                                     \
            _Pragma("GCC diagnostic pop");                                                         \
            assert(condition);                                                                     \
        }                                                                                          \
    }                                                                                              \
    while (0)

#if (!defined(ASSERT_WARN_CT) && defined(NDEBUG))
  #define ASSERT_WARN_CT 1
#endif
#if ASSERT_WARN_CT
  #define ASSERT_DIAG_MODE "GCC diagnostic warning \"-Wpadded\""
#else
  #define ASSERT_DIAG_MODE "GCC diagnostic ignored \"-Wpadded\""
#endif

/// @brief runtime assertion with user-defined message.
/// @details
/// assert_msg() can be used instead of the standard `assert()` command to add a user-defined part
/// to the generated assertion message (standard `assert()` implementations typically generate a
/// message including the condition, file name, and line number).
/// Besides that, assert_msg() is equivalent to `assert()`, including its dependency to `NDEBUG`.
///
/// The additional parameters with user-defined message parts are optional, so assert_msg() can
/// also be called like `assert()` (with only the condition). This can be used to globally
/// redirect `assert()` calls via something like
/// @code
///		#undef  assert
///		#define assert(c)	assert_msg(c)
/// @endcode
/// which can be helpful to catch `assert()` statements that have been written for some (old)
/// proprietary `assert()` implementation with additional parameters.
/// However, we strongly recommend to not globally remap `assert()` except for such special cases,
/// as calling `assert()` with additional arguments is not ISO-C compliant.
#ifdef NDEBUG
  #define assert_msg(condition, ...) ((void) 0)
#else
  #define assert_msg(condition, ...)                                                               \
      if (!(condition)) do                                                                         \
          {                                                                                        \
              static const void *msg_[] = {#condition, ##__VA_ARGS__};                             \
              __assert(msg_[NUM_ELEMENTS(msg_) - 1], __FILE__, __LINE__);                          \
          }                                                                                        \
      while (0)
#endif

/// @}
//**************************************************************************************************
/// @name Array and Struct Field Handling
///
/// The following macros simplify the handling of generic arrays and structs.
/// They should be used whenever possible to make code robust and avoid error-prone constructs.
/// @{

/// @brief Get length of an array (number of elements, not `sizeof()`).
/// @details The name ARRAY_SIZE() stems from the Linux kernel. NUM_ELEMENTS() is a bit more
/// specific and may avoid confusion with `sizeof(a)`.
/// @sa NUM_ELEMENTS()
//  internal: http://zubplot.blogspot.com/2015/01/gcc-is-wonderful-better-arraysize-macro.html
//  helps to understand the type issues
#define ARRAY_SIZE(a)                                                                              \
    ((sizeof(a) /                                                                                  \
      sizeof((a)[0])) + /* check if a is really the array (itself), not a pointer to the array;		\
		 * otherwise the result would be wrong */ \
     ASSERT_CT_EVAL(!__builtin_types_compatible_p(typeof(a), typeof(&(a)[0])),                     \
                    invalid_ARRAY_SIZE_usage))

/// @copybrief ARRAY_SIZE().
/// @details This is just another name for ARRAY_SIZE(), it avoids confusion with `sizeof(a)`.
/// @sa ARRAY_SIZE()
#define NUM_ELEMENTS(a)       ARRAY_SIZE(a)

/// @brief Get size of a struct field or class member.
/// @details The name FIELD_SIZEOF stems from the Linux kernel.
/// @par Example
/// @code
///		typedef struct T {
///			int16_t a;
///		} T;
///
///		n = FIELD_SIZEOF(T, a);		// -> 2
/// @endcode
/// @sa sizeof_field(), sizeof_member()
#define FIELD_SIZEOF(T, m)    sizeof(((const T *) 0)->m)

/// @copybrief FIELD_SIZEOF().
/// @details This is just another name for FIELD_SIZEOF() in the style of `sizeof()` and `offsetof()`.
/// @sa FIELD_SIZEOF()
#define sizeof_field(T, m)    FIELD_SIZEOF(T, m)
#define sizeof_member(T, m)   FIELD_SIZEOF(T, m) ///< @copydoc sizeof_field()

/// @brief Get offset of a struct field or class member relative to the struct or class.
/// @details
/// This is just another name for [`offsetof()`](https://en.wikipedia.org/wiki/Offsetof) from
/// [stddef.h](https://en.wikipedia.org/wiki/Stddef.h) in the style of sizeof_field().
/// The use is deprecated in favor of `offsetof()` since the latter is ISO standard.
#define offsetof_field(T, m)  offsetof(T, m)
#define offsetof_member(T, m) offsetof(T, m) ///< @copydoc offsetof_field()

// redefine offsetof() to the clean builtin form
// NOTE: Some stddef.h define offsetof(T, m) as ((size_t)&(((T*)0)->m)), which is somewhat dirty
// (see for instance https://en.wikipedia.org/wiki/Offsetof for details) and can cause annoying
// warnings in some use cases (e.g. warning: variably modified ... at file scope). Therefore we
// redefine offsetof() to the clean form using a builtin function.
// ATTENTION: Redefining standard macros is crude in general because in consequence different
// definitions may become effective in different places of the program. However, this is not
// critical here because the result of the evaluation is consistent (we just avoid potential
// warnings)
#undef offsetof
#define offsetof(T, m)    __builtin_offsetof(T, m)

/// @brief Convert a pointer to an array element to the index of that element.
/// @details
/// @par Example
/// @code
///		int	a[10];
///		int	*p = &a[3];
///
///		n = ARRAY_INDEX(p, a);	// -> 3
/// @endcode
#define ARRAY_INDEX(p, a) (((uintptr_t) (p) - (uintptr_t) &(a)[0]) / sizeof((a)[0]))

/// @}
//**************************************************************************************************
/// @name Bit Twiddling
///
/// The following macros provide bit-related computations for constant expressions. They are
/// evaluated at compile-time, so they come at no cost regarding the compiled program and can,
/// amongst others, be used in compile-time assertions.
/// @{

/// @brief Generate bit mask with single bit at position \a pos set.
/// @details
/// BV() ("BitValue") is often used in low-level programming when working with control register
/// fields. Its main purpose is to improve the compactness and readability of source code (that is
/// why it has this short name).
#define BV(pos)           (1u << (pos))

/// @brief Test if constant value is a power of 2.
/// @details
/// A typical use case for this macro is in compile-time assertions before writing some optimized
/// code that relies on a power-of-2 assumption (e.g. when replacing mul or div by shift operations).
#define IS_POWER_OF_2(a)  ((a) && (((uintmax_t) (a) & -(uintmax_t) (a)) == (uintmax_t) (a)))

/// @brief Extract most significant bit (MSB) of a constant value.
/// @details
/// Returns the 0-based index of the highest bit set or -1 if \a a equals 0.
///
/// The current implementation supports 8...32 bit wide arguments (can be extended
/// straightforwardly if required). Calling MSB() with wider arguments triggers an assertion.
/// @sa LSB()
//  internal: if sizeof(a) assertion triggers, then extend the MSBxx macros (it is straightforward)
#define MSB(a)                                                                                     \
    (MSB32(a) + ASSERT_CT_EVAL(IS_CONST_EXPRESSION(a), non_const_expression) +                     \
     ASSERT_CT_EVAL(sizeof(a) < 8, overflow))

/// @brief Extract least significant bit (LSB) of a constant value.
/// @details
/// Returns the 0-based index of the lowest bit set or -1 if \a a equals 0.
///
/// The current implementation supports 8...32 bit wide arguments (can be extended
/// straightforwardly if required). Calling LSB() with wider arguments triggers an assertion.
/// @sa MSB()
#define LSB(a)            MSB((a) & -(a))

/// @}
//**************************************************************************************************
/// @name Low-level Programming and Instruction Flow Control
///
/// The following macros and functions are primarily useful in the context of low-level programming,
/// some of them are also relevant for multi-threaded programming (incl. interrupt and exception
/// handling). They use special mechanisms to implement barriers that ensure that the
/// compiler-generated machine code works as expected. Such barriers can be necessary to avoid
/// optimization steps that would otherwise lead to malfunctioning code (because the compiler is
/// not aware of hardware-specific details and, in general, does not semantically understand what
/// the program does).
/// @{

/// @brief Make function always inline.
/// @details
/// In contrast to the keyword `inline`, declaring a function as @ref ALWAYS_INLINE means that
/// it gets inlined *always*, i.e. also with optimization disabled and even in DEBUG builds.
///
/// @ref ALWAYS_INLINE is primarily useful for very small and time-critical functions like
/// gpi_int_lock(), gpi_int_unlock(), gpi_atomic_set(), gpi_atomic_clear(), etc..
#define ALWAYS_INLINE     inline __attribute__((always_inline))

/// @brief General re-order barrier.
/// @details
/// A REORDER_BARRIER() can be used to ensure that the instructions written above the barrier get
/// executed before the instructions written below the barrier.
///
/// What sounds as a matter of course at first glance is not necessarily guaranteed in general
/// because the compiler can rearrange things internally for optimization purposes (e.g. store
/// intermediate variable values in CPU registers instead of RAM, reorder write-back operations,
/// etc.). REORDER_BARRIER() can be used to enforce critical ordering.
///
/// @par Example
/// @code
///		// prepare data
///		// configure DMA controller for data transfer
///
///		REORDER_BARRIER();	// ensures that data is written to memory before continuing
///
///		// start DMA transfer
/// @endcode
///
/// @impdetails REORDER_BARRIER() makes the compiler believe that an external "blackbox" accesses
/// the memory at this place. Hence, the CPU must write changed data back to memory before
/// reaching the barrier, and it must reload data afterwards since it cannot know if the blackbox
/// changed something.
//
//  internal: For the moment, the intermediate macro is only used to produce more straightforward
//  Doxygen output. However, maybe for some reason it gets beneficial to have a (more flexible)
//  macro in between (usage is the same).
#define REORDER_BARRIER() gpi_reorder_barrier()
static ALWAYS_INLINE void gpi_reorder_barrier(void) { __asm__ volatile("" : : : "memory"); }

/// @brief Selective re-order barrier for specific variable \a p.
/// @details
/// COMPUTE_BARRIER() is a more selective barrier than REORDER_BARRIER() with focus on a single
/// variable. It is rarely used in "normal" programs, but it can (for instance) be beneficial
/// in functions that mix C and inline assembly code to exploit some hardware functionality
/// (e.g. a math co-processor) most efficiently.
/// As a side effect, COMPUTE_BARRIER(p) ensures that \a p resides in a register.
/// @sa REORDER_BARRIER()
#define COMPUTE_BARRIER(p) __asm__ volatile("" : : "r"(p))

/// @}
//**************************************************************************************************
/// @name Miscellaneous
/// @{

#ifndef ABS
  /// @brief Get magnitude of \a a.
  #define ABS(a)                                                                                   \
      ({                                                                                           \
        typeof(a) a_ = (a);                                                                        \
        (a_ < 0) ? -a_ : a_;                                                                       \
      })
#endif

#ifndef MIN
  /// @brief Get minimum of \a a and \a b.
  #define MIN(a, b)                                                                                \
      ({                                                                                           \
        typeof(a) a_ = (a);                                                                        \
        typeof(b) b_ = (b);                                                                        \
        (a_ < b_) ? a_ : b_;                                                                       \
      })
  /// @brief Get maximum of \a a and \a b.
  #define MAX(a, b)                                                                                \
      ({                                                                                           \
        typeof(a) a_ = (a);                                                                        \
        typeof(b) b_ = (b);                                                                        \
        (a_ > b_) ? a_ : b_;                                                                       \
      })
#endif

/// @brief Alignment of current platform or compiler settings.
#define ALIGNMENT                                                                                  \
    offsetof(                                                                                      \
            struct {                                                                               \
                int8_t   a;                                                                        \
                intmax_t b;                                                                        \
            },                                                                                     \
            b)

/// @}
//**************************************************************************************************
//***** Local (Private) Defines and Consts *********************************************************

// the following macros are for internal use only

// detect if argument (or arg list) is present by evaluating the size of its stringification
// internal: accommodate to __VA_OPT__() (ISO C++2a) after that has become common
//#define VA_IS(a...) 		(sizeof(STRINGIFY(#a)) > 3)	// "\"a\"" = {\", a, \", \0}
#define VA_IS(a...)                                          (sizeof(#a) > 1)

// successively count the arguments
// note: we cannot do things like #define VA_NUM(a,b...) (VA_IS(a) + VA_NUM(b)) because
// preprocessor avoids "self-expansion". Therefore the macros have to be unrolled.
#define VA_NUM1(a...)                                        (VA_IS(a) ? 1 + VA_NUM2(a) : 0)
#define VA_NUM2(a, b...)                                     (VA_IS(b) ? 1 + VA_NUM3(b) : 0)
#define VA_NUM3(b, c...)                                     (VA_IS(c) ? 1 + VA_NUM4(c) : 0)
#define VA_NUM4(c, d...)                                     (VA_IS(d) ? 1 + VA_NUM5(d) : 0)
#define VA_NUM5(d, e...)                                     (VA_IS(e) ? 1 + VA_NUM6(e) : 0)
#define VA_NUM6(e, f...)                                     (VA_IS(f) ? 1 + VA_NUM7(f) : 0)
#define VA_NUM7(f, g...)                                     (VA_IS(g) ? 1 + VA_NUM8(g) : 0)
#define VA_NUM8(g, h...)                                     (VA_IS(h) ? 1 + VA_NUM9(h) : 0)
#define VA_NUM9(h, i...)                                     (VA_IS(i) ? 1 + VA_NUM10(i) : 0)
#define VA_NUM10(i, j...)                                    (VA_IS(j) ? 1 + VA_NUM11(j) : 0)
#define VA_NUM11(j, k...)                                    ASSERT_CT_EVAL(!VA_IS(k), VA_NUM_overflow)
//#define VA_NUM11(j,k...)	(VA_IS(k) ? -10 - __LINE__ : 0)

// get size of argument, 0 if there is no argument
#define VA_SIZEOF(a...)                                      (sizeof((void) (uint8_t) 1, ##a) - 1 + VA_IS(a))

// pad size to var_args granularity (typically machine word size)
#define VA_SIZEOF_PAD(a...)                                  ((VA_SIZEOF(a) + VA_SIZE_GRANULARITY - 1) & ~(VA_SIZE_GRANULARITY - 1))

// successively count the size of the arguments
// note: preprocessor avoids "self-expansion", therefore the macros have to be unrolled
#define VA_SIZE1(a...)                                       (VA_IS(a) ? VA_SIZE2(a) : 0)
#define VA_SIZE2(a, b...)                                    (VA_SIZEOF_PAD(a) + (VA_IS(b) ? VA_SIZE3(b) : 0))
#define VA_SIZE3(b, c...)                                    (VA_SIZEOF_PAD(b) + (VA_IS(c) ? VA_SIZE4(c) : 0))
#define VA_SIZE4(c, d...)                                    (VA_SIZEOF_PAD(c) + (VA_IS(d) ? VA_SIZE5(d) : 0))
#define VA_SIZE5(d, e...)                                    (VA_SIZEOF_PAD(d) + (VA_IS(e) ? VA_SIZE6(e) : 0))
#define VA_SIZE6(e, f...)                                    (VA_SIZEOF_PAD(e) + (VA_IS(f) ? VA_SIZE7(f) : 0))
#define VA_SIZE7(f, g...)                                    (VA_SIZEOF_PAD(f) + (VA_IS(g) ? VA_SIZE8(g) : 0))
#define VA_SIZE8(g, h...)                                    (VA_SIZEOF_PAD(g) + (VA_IS(h) ? VA_SIZE9(h) : 0))
#define VA_SIZE9(h, i...)                                    (VA_SIZEOF_PAD(h) + (VA_IS(i) ? VA_SIZE10(i) : 0))
#define VA_SIZE10(i, j...)                                   (VA_SIZEOF_PAD(i) + (VA_IS(j) ? VA_SIZE11(j) : 0))
#define VA_SIZE11(j, k...)                                   (VA_SIZEOF_PAD(j) + ASSERT_CT_EVAL(!VA_IS(k), VA_SIZE_overflow))
//#define VA_SIZE11(j,k...)	(VA_SIZEOF_PAD(j) + (VA_IS(k) ? -80 - __LINE__ : 0))

// return i-th argument (i.e. i-th element of a comma-separated list).
// for detail see VA_ARG_i().
// note: index i is 0-based
#define VA_ARG0(_0, ...)                                     _0
#define VA_ARG1(_0, _1, ...)                                 _1
#define VA_ARG2(_0, _1, _2, ...)                             _2
#define VA_ARG3(_0, _1, _2, _3, ...)                         _3
#define VA_ARG4(_0, _1, _2, _3, _4, ...)                     _4
#define VA_ARG5(_0, _1, _2, _3, _4, _5, ...)                 _5
#define VA_ARG6(_0, _1, _2, _3, _4, _5, _6, ...)             _6
#define VA_ARG7(_0, _1, _2, _3, _4, _5, _6, _7, ...)         _7
#define VA_ARG8(_0, _1, _2, _3, _4, _5, _6, _7, _8, ...)     _8
#define VA_ARG9(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, ...) _9

// return MSB of a
#define MSB2(a)                                              ((a) & 2 ? 1 : ((a) & 1 ? 0 : -1))
#define MSB4(a)                                              ((uint32_t) (a) >= 0x4 ? 2 + MSB2((uint32_t) (a) >> 2) : MSB2(a))
#define MSB8(a)                                              ((uint32_t) (a) >= 0x10 ? 4 + MSB4((uint32_t) (a) >> 4) : MSB4(a))
#define MSB16(a)                                             ((uint32_t) (a) >= 0x100 ? 8 + MSB8((uint32_t) (a) >> 8) : MSB8(a))
#define MSB32(a)                                             ((uint32_t) (a) >= 0x10000 ? 16 + MSB16((uint32_t) (a) >> 16) : MSB16(a))
//#define MSB64(a)			( (uint64_t)(a) >= UINT64_C(0x100000000) ? 32 + MSB32((uint64_t)(a) >> 32) : MSB32(a) )

//**************************************************************************************************
//***** Forward Class and Struct Declarations ******************************************************


//**************************************************************************************************
//***** Global Typedefs and Class Declarations *****************************************************

// NOTE: use @defgroup (= topic) instead of @name (= member group) because the latter does not
// work for some reason (members are there, but surrounding group is not shown, Doxygen 1.10.0)
//
/// @defgroup GenericXX Generic 16/32/64 bit Containers
///
/// The Generic16/32/64 datatypes can be used to store or overlay 16/32/64 bit of arbitrary data
/// and access pieces of that data without fragile casting and pointer arithmetic.
/// Note that beyond comfort, avoiding pointer arithmetic also facilitates performance (simplifies
/// optimization) because the data can be stored in CPU registers (which have no address).
///
/// The internal type definitions respect the machine's native byte order, e.g. it always holds
/// `Generic16.u8_h == Generic16.u16 >> 8`. (In other words, with little endian byte order
/// `u8_l` refers to the first byte and `u8_h` refers to the second byte, while the opposite
/// is true for big endian byte order.)
/// @{

/// @brief Generic 16 bit container.
typedef union Generic16_tag
{
    uint16_t u16; ///< underlying data interpreted as 16 bit unsigned value.
    int16_t  s16; ///< underlying data interpreted as 16 bit signed value.

// flatten structs for Doxygen because the latter has trouble with unnamed structs / unions
// [see <https://github.com/doxygen/doxygen/issues/6652#issuecomment-991863827>,
// <https://github.com/doxygen/doxygen/issues/9180>]
// ATTENTION: resulting struct layout is wrong, so do not use this for anything else
#if (__DOXYGEN__)

    uint8_t u8_l; ///< lowest 8 bit of the underlying data interpreted as unsigned value.
    uint8_t u8_h; ///< highest 8 bit of the underlying data interpreted as unsigned value.

    int8_t  s8_l; ///< lowest 8 bit of the underlying data interpreted as signed value.
    int8_t  s8_h; ///< highest 8 bit of the underlying data interpreted as signed value.

#elif (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)

    struct
    {
        uint8_t u8_l;
        uint8_t u8_h;
    };

    struct
    {
        int8_t s8_l;
        int8_t s8_h;
    };

#elif (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)

    struct
    {
        uint8_t u8_h;
        uint8_t u8_l;
    };

    struct
    {
        int8_t s8_h;
        int8_t s8_l;
    };

#else
  #error byte order is unknown
#endif

} Generic16;

//**************************************************************************************************

/// @brief Generic 32 bit container.
typedef union Generic32_tag
{
    uint32_t u32; ///< underlying data interpreted as 32 bit unsigned value.
    int32_t  s32; ///< underlying data interpreted as 32 bit signed value.

// flatten structs for Doxygen because the latter has trouble with unnamed structs / unions
// [see <https://github.com/doxygen/doxygen/issues/6652#issuecomment-991863827>,
// <https://github.com/doxygen/doxygen/issues/9180>]
// ATTENTION: resulting struct layout is wrong, so do not use this for anything else
#if (__DOXYGEN__)

    uint16_t u16_l; ///< lowest 16 bit of the underlying data interpreted as unsigned value.
    uint16_t u16_h; ///< highest 16 bit of the underlying data interpreted as unsigned value.

    int16_t  s16_l; ///< lowest 16 bit of the underlying data interpreted as signed value.
    int16_t  s16_h; ///< highest 16 bit of the underlying data interpreted as signed value.

    uint8_t  u8_ll; ///< lowest 8 bit of the underlying data interpreted as unsigned value.
    uint8_t  u8_lh; ///< second-lowest 8 bit of the underlying data interpreted as unsigned value.
    uint8_t  u8_hl; ///< second-highest 8 bit of the underlying data interpreted as unsigned value.
    uint8_t  u8_hh; ///< highest 8 bit of the underlying data interpreted as unsigned value.

    int8_t   s8_ll; ///< lowest 8 bit of the underlying data interpreted as signed value.
    int8_t   s8_lh; ///< second-lowest 8 bit of the underlying data interpreted as signed value.
    int8_t   s8_hl; ///< second-highest 8 bit of the underlying data interpreted as signed value.
    int8_t   s8_hh; ///< highest 8 bit of the underlying data interpreted as signed value.

#elif (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)

    struct
    {
        uint16_t u16_l;
        uint16_t u16_h;
    };

    struct
    {
        int16_t s16_l;
        int16_t s16_h;
    };

    struct
    {
        uint8_t u8_ll;
        uint8_t u8_lh;
        uint8_t u8_hl;
        uint8_t u8_hh;
    };

    struct
    {
        int8_t s8_ll;
        int8_t s8_lh;
        int8_t s8_hl;
        int8_t s8_hh;
    };

#elif (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)

    struct
    {
        uint16_t u16_h;
        uint16_t u16_l;
    };

    struct
    {
        int16_t s16_h;
        int16_t s16_l;
    };

    struct
    {
        uint8_t u8_hh;
        uint8_t u8_hl;
        uint8_t u8_lh;
        uint8_t u8_ll;
    };

    struct
    {
        int8_t s8_hh;
        int8_t s8_hl;
        int8_t s8_lh;
        int8_t s8_ll;
    };

#else
  #error byte order is unknown
#endif

} Generic32;

//**************************************************************************************************

/// @brief Generic 64 bit container.
typedef union Generic64_tag
{
    uint64_t u64; ///< underlying data interpreted as 64 bit unsigned value.
    int64_t  s64; ///< underlying data interpreted as 64 bit signed value.

// flatten structs for Doxygen because the latter has trouble with unnamed structs / unions
// [see <https://github.com/doxygen/doxygen/issues/6652#issuecomment-991863827>,
// <https://github.com/doxygen/doxygen/issues/9180>]
// ATTENTION: resulting struct layout is wrong, so do not use this for anything else
#if (__DOXYGEN__)

    uint32_t u32_l; ///< lowest 32 bit of the underlying data interpreted as unsigned value.
    uint32_t u32_h; ///< highest 32 bit of the underlying data interpreted as unsigned value.

    int32_t  s32_l; ///< lowest 32 bit of the underlying data interpreted as signed value.
    int32_t  s32_h; ///< highest 32 bit of the underlying data interpreted as signed value.

    uint16_t u16_ll; ///< lowest 16 bit of the underlying data interpreted as unsigned value.
    uint16_t u16_lh; ///< second-lowest 16 bit of the underlying data interpreted as unsigned value.
    uint16_t
            u16_hl; ///< second-highest 16 bit of the underlying data interpreted as unsigned value.
    uint16_t u16_hh; ///< highest 16 bit of the underlying data interpreted as unsigned value.

    int16_t  s16_ll; ///< lowest 16 bit of the underlying data interpreted as signed value.
    int16_t  s16_lh; ///< second-lowest 16 bit of the underlying data interpreted as signed value.
    int16_t  s16_hl; ///< second-highest 16 bit of the underlying data interpreted as signed value.
    int16_t  s16_hh; ///< highest 16 bit of the underlying data interpreted as signed value.

    uint8_t  u8_lll; ///< lowest 8 bit of the underlying data interpreted as unsigned value.
    uint8_t  u8_llh; ///< second-lowest 8 bit of the underlying data interpreted as unsigned value.
    uint8_t  u8_lhl; ///< third-lowest 8 bit of the underlying data interpreted as unsigned value.
    uint8_t  u8_lhh; ///< fourth-lowest 8 bit of the underlying data interpreted as unsigned value.
    uint8_t  u8_hll; ///< fourth-highest 8 bit of the underlying data interpreted as unsigned value.
    uint8_t  u8_hlh; ///< third-highest 8 bit of the underlying data interpreted as unsigned value.
    uint8_t  u8_hhl; ///< second-highest 8 bit of the underlying data interpreted as unsigned value.
    uint8_t  u8_hhh; ///< highest 8 bit of the underlying data interpreted as unsigned value.

    int8_t   s8_lll; ///< lowest 8 bit of the underlying data interpreted as signed value.
    int8_t   s8_llh; ///< second-lowest 8 bit of the underlying data interpreted as signed value.
    int8_t   s8_lhl; ///< third-lowest 8 bit of the underlying data interpreted as signed value.
    int8_t   s8_lhh; ///< fourth-lowest 8 bit of the underlying data interpreted as signed value.
    int8_t   s8_hll; ///< fourth-highest 8 bit of the underlying data interpreted as signed value.
    int8_t   s8_hlh; ///< third-highest 8 bit of the underlying data interpreted as signed value.
    int8_t   s8_hhl; ///< second-highest 8 bit of the underlying data interpreted as signed value.
    int8_t   s8_hhh; ///< highest 8 bit of the underlying data interpreted as signed value.

#elif (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)

    struct
    {
        uint32_t u32_l;
        uint32_t u32_h;
    };

    struct
    {
        int32_t s32_l;
        int32_t s32_h;
    };

    struct
    {
        uint16_t u16_ll;
        uint16_t u16_lh;
        uint16_t u16_hl;
        uint16_t u16_hh;
    };

    struct
    {
        int16_t s16_ll;
        int16_t s16_lh;
        int16_t s16_hl;
        int16_t s16_hh;
    };

    struct
    {
        uint8_t u8_lll;
        uint8_t u8_llh;
        uint8_t u8_lhl;
        uint8_t u8_lhh;
        uint8_t u8_hll;
        uint8_t u8_hlh;
        uint8_t u8_hhl;
        uint8_t u8_hhh;
    };

    struct
    {
        int8_t s8_lll;
        int8_t s8_llh;
        int8_t s8_lhl;
        int8_t s8_lhh;
        int8_t s8_hll;
        int8_t s8_hlh;
        int8_t s8_hhl;
        int8_t s8_hhh;
    };

#elif (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)

    struct
    {
        uint32_t u32_h;
        uint32_t u32_l;
    };

    struct
    {
        int32_t s32_h;
        int32_t s32_l;
    };

    struct
    {
        uint16_t u16_hh;
        uint16_t u16_hl;
        uint16_t u16_lh;
        uint16_t u16_ll;
    };

    struct
    {
        int16_t s16_hh;
        int16_t s16_hl;
        int16_t s16_lh;
        int16_t s16_ll;
    };

    struct
    {
        uint8_t u8_hhh;
        uint8_t u8_hhl;
        uint8_t u8_hlh;
        uint8_t u8_hll;
        uint8_t u8_lhh;
        uint8_t u8_lhl;
        uint8_t u8_llh;
        uint8_t u8_lll;
    };

    struct
    {
        int8_t s8_hhh;
        int8_t s8_hhl;
        int8_t s8_hlh;
        int8_t s8_hll;
        int8_t s8_lhh;
        int8_t s8_lhl;
        int8_t s8_llh;
        int8_t s8_lll;
    };

#else
  #error byte order is unknown
#endif

} Generic64;

/// @}

//**************************************************************************************************
//***** Global Variables ***************************************************************************


//**************************************************************************************************
//***** Prototypes of Global Functions *************************************************************

#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
}
#endif

//**************************************************************************************************
//***** Post Includes ******************************************************************************

// include files that (may) depend on current file "in order"

#include "gpi/platform_spec.h" // VA_SIZE_GRANULARITY

//**************************************************************************************************
//**************************************************************************************************

#endif // __GPI_TOOLS_H__
