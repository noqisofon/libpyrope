#ifndef pyrope_handle_h
#define pyrope_handle_h

#include <pyrope/_pyrope.h>


#ifndef pyrope_DEFINED_HANDLE_T
typedef     handle_t        HANDLE;
#   define      w32_DEFINED_HANDLE_T
#endif  /* ndef w32_DEFINED_HANDLE_T */


/**
 * 指定したハンドルが無効化どうかを判別します。
 */
gboolean pyrope_handle_is_invalid(handle_t handle);


/**
 * ハンドルを閉じます。
 */
gboolean w32_handle_close(handle_t handle);


#endif  /* pyrope_handle_h */
