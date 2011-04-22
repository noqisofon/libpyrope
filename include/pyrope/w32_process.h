#ifndef w32_process_h
#define w32_process_h

#ifndef PYROPE_API
#   define     PYROPE_API      __stdcall
#endif  /* ndef PYROPE_API */

#ifndef PYROPE_DEFINED_HANDLE_T
typedef        HANDLE     handle_t;
#   define      PYROPE_DEFINED_HANDLE_T
#endif  /* ndef PYROPE_DEFINED_HANDLE_T */


typedef     STARTUPINFO             startup_info_t;
typedef     PROCESS_INFORMATION     process_infomation_t;
typedef     SECURITY_ATTRIBUTES     security_attr_t;


struct pyrope_process_t {
    gchar*                  application_name;
    gchar*                  command_line;
    security_attr_t*        process_attr;
    security_attr_t*        thread_attr;
    gboolean                inherit_handles;
    guint                   creation_flags;
    VALUE                   environment;
    gchar*                  current_directory;
    startup_info_t*         startup_info;
    process_infomation_t*   process_info;
};


typedef     struct pyrope_process_t    Process;


/**
 * 空のプロセスインスタンスを作成して返します。
 */
Process* PYROPE_API w32_process_new();


/**
 * 現在アクティブなプロセスを返します。
 */
Process* PYROPE_API w32_get_current_process();


/**
 * 指定されたプロセスのプロセスハンドルを返します。
 */
handle_t PYROPE_API w32_process_get_process_handle(Process* self);


/**
 * 指定されたプロセスを開始します。
 */
gboolean PYROPE_API w32_process_start(Process* self);


/**
 * 指定されたプロセスとそのプロセスに所属する全てのスレッドを終了させます。
 */
gboolean PYROPE_API w32_process_exit(Process* self, guint exit_code);


/**
 * 関連付けられたプロセスを即時中断します。
 */
gboolean PYROPE_API w32_process_kill(const Process* self);


/**
 * 指定されたプロセスの終了ステータスを取得します。
 */
gboolean PYROPE_API w32_process_get_exitcode(Process* self, gint* exit_code);


/**
 *
 */
void PYROPE_API w32_process_wait(Process* self, guint milliseconds);


/**
 *
 */
void PYROPE_API w32_process_wait_for(Process* self);


/**
 * 
 */
void PYROPE_API w32_process_destroy(Process* self);


#endif  /* w32_process_h */
