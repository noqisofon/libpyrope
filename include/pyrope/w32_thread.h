#ifndef pyrope_w32_thread_h
#define pyrope_w32_thread_h


typedef     HANDLE       w32_thread_t;


/**
 * スレッドを作成します。
 */
gint PYROPE_API w32_thread_create( w32_thread_t*        thread_handle,
                        security_attr_t*     attribute,
                        unsigned             (__stdcall *start_routine)(void*),
                        void*                arglist
                        );


/**
 * スレッドを終了します。
 */
void PYROPE_API w32_thread_exit(guint retcode);


/**
 * 指定されたスレッドの実行を中断します。
 */
gint PYROPE_API w32_thread_suspend(w32_thread_t self);


/**
 * スレッドの中断カウントを 1 減らします。中断カウントが 0 になると、スレッドの実行が再開されます。
 */
gint PYROPE_API w32_thread_resume(w32_thread_t self);


/**
 * 指定したスレッドの相対優先順位を返します。
 */
gint PYROPE_API w32_get_thread_priority(w32_thread_t self);


/**
 * 指定したスレッドの相対優先順位を指定します。
 */
gboolean PYROPE_API w32_set_thread_priority(w32_thread_t self, int priority);


/**
 * 呼び出し側スレッドのハンドルを返します。
 */
w32_thread_t PYROPE_API w32_get_current_thread();


/**
 * 指定された既存のスレッドハンドルを返します。
 */
w32_thread_t PYROPE_API w32_thread_open( guint     desired_access,
                              gboolean  inherit_handle,
                              guint     thread_id
                              );


/**
 * 呼び出し側スレッドのスレッド識別子を返します。
 */
guint PYROPE_API w32_get_current_thread_id();


#endif  /* pyrope_w32_thread_h */
