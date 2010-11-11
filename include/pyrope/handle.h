#ifndef pyrope_handle_h
#define pyrope_handle_h

#include <pyrope/_pyrope.h>


#ifndef pyrope_DEFINED_HANDLE_T
typedef     handle_t        HANDLE;
#   define      w32_DEFINED_HANDLE_T
#endif  /* ndef w32_DEFINED_HANDLE_T */


/**
 * �w�肵���n���h�����������ǂ����𔻕ʂ��܂��B
 */
gboolean pyrope_handle_is_invalid(handle_t handle);


/**
 * �n���h������܂��B
 */
gboolean w32_handle_close(handle_t handle);


#endif  /* pyrope_handle_h */
