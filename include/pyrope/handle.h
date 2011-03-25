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
 * �w�肵���n���h�����������ǂ����𔻕ʂ��܂��B
 */
gboolean PYROPE_API pyrope_handle_is_invalid(handle_t handle);


/**
 * �n���h������܂��B
 */
gboolean PYROPE_API w32_handle_close(handle_t handle);


#endif  /* pyrope_handle_h */
