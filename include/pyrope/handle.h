#ifndef pyrope_handle_h
#define pyrope_handle_h

#ifndef PYROPE_API
#   define     PYROPE_API      __stdcall
#endif  /* ndef PYROPE_API */

#ifndef PYROPE_DEFINED_HANDLE_T
typedef        HANDLE     handle_t;
#   define      PYROPE_DEFINED_HANDLE_T
#endif  /* ndef PYROPE_DEFINED_HANDLE_T */


/**
 * 指定したハンドルが無効化どうかを判別します。
 */
gboolean PYROPE_API pyrope_handle_is_invalid(handle_t handle);


/**
 * ハンドルを閉じます。
 */
gboolean PYROPE_API w32_handle_close(handle_t handle);


#endif  /* pyrope_handle_h */
