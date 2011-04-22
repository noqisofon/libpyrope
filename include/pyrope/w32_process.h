#ifndef w32_process_h
#define w32_process_h

#ifndef PYROPE_API
#   define     PYROPE_API      __stdcall
#endif  /* ndef PYROPE_API */

#ifndef PYROPE_DEFINED_HANDLE_T
typedef        HANDLE     handle_t;
#   define      PYROPE_DEFINED_HANDLE_T
#endif  /* ndef PYROPE_DEFINED_HANDLE_T */


struct pyrope_process_t {
    guint    id;
    handle_t handle;
};


typedef    struct pyrope_process_t      Process;


/**
 * 関連付けられたプロセスを即時中断します。
 */
gboolean PYROPE_API w32_process_kill(const Process* self);


#endif  /* w32_process_h */
