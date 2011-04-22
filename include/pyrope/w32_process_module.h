#ifndef w32_process_module_h
#define w32_process_module_h

#ifndef PYROPE_API
#   define     PYROPE_API      __stdcall
#endif  /* ndef PYROPE_API */

#ifndef PYROPE_DEFINED_HANDLE_T
typedef        HANDLE     handle_t;
#   define      PYROPE_DEFINED_HANDLE_T
#endif  /* ndef PYROPE_DEFINED_HANDLE_T */


struct pyrope_process_module_t {
    VALUE  base_address;  //!< モジュールが読み込まれたメモリアドレスを表します。
    VALUE  entrypoint_address;  //!< システムがモジュールを読み込んで実行するときに呼び出される関数のメモリアドレスを表します。
    gchar* filename;  //!< モジュールの完全パスを表します。
    size_t memory_size;  //!< モジュールの読込に必要なメモリ容量を取得します。
    gchar* name;  //!< モジュール名を表します。
};


typedef   struct pyrope_process_module_t     ProcessModule;


/**
 * 
 */
ProcessModule* pyrope_process_module_new(handle_t process, handle_t module);


/**
 * 
 */
void pyrope_process_module_destroy(ProcessModule* self);


#endif  /* w32_process_module_h */
