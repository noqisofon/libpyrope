#ifndef pyrope_w32_mutex_h
#define pyrope_w32_mutex_h

#ifndef PYROPE_API
#   define     PYROPE_API      __stdcall
#endif  /* ndef PYROPE_API */

//#ifndef GARNET_DEFINE_GINT
//#   define      GARNET_DEFINE_GINT
//typedef     int                 gint;
//#endif  /* ndef GARNET_DEFINE_GINT */
//
//#ifndef GARNET_DEFINED_
//#   define      GARNET_DEFINED_
//typedef     unsigned int        guint;
//#endif  /* ndef GARNET_DEFINED_ */
//
//#ifndef GARNET_DEFINE_GCHAR
//#   define      GARNET_DEFINE_GCHAR
//#   if defined(_UNICODE) || defined(UNICODE)
//typedef    wchar_t        gchar;
//#   else
//typedef    char           gchar;
//#   endif  /* defined(_UNICODE) || defined(UNICODE) */
//#endif  /* ndef GARNET_DEFINE_GCHAR */
//
//#ifndef GARNET_DEFINE_GBOOLEAN
//#   define      GARNET_DEFINE_GBOOLEAN
//#   if defined(__cplusplus)
//typedef    bool    gboolean;
//#   else
//typedef enum boolean_t {
//    false = 0,
//    true = 1
//} gboolean;
//#   endif  /* defined(__cplusplus) */
//#endif  /* ndef GARNET_DEFINE_GBOOLEAN */


struct w32_mutex_t {
    HANDLE      handle;
    gboolean    released;
};
typedef     struct w32_mutex_t     Mutex;


/**
 * ミューテックスを作成して返します。
 */
Mutex* PYROPE_API w32_mutex_new();
/**
 * 名前付きの ミューテックスを作成して返します。
 */
Mutex* PYROPE_API w32_mutex_new_from_name(const gchar* name);
/**
 * ミューテックスの初期所有権の有無を表す真偽値とミューテックスの名前からミューテックスを作成して返します。
 */
Mutex* PYROPE_API w32_mutex_new_owned(gboolean initially_owned, const gchar* name);
/**
 * ミューテックスの初期所有権の有無を表す真偽値とミューテックスの名前からミューテックスを作成して返します。
 */
Mutex* PYROPE_API w32_mutex_new_is_initially_create(gboolean initially_owned, const gchar* name, gboolean* create_new);


/**
 * 既存の名前付きミューテックスを開きます。
 */
Mutex* PYROPE_API w32_mutex_open_existing(const gchar* name);


/**
 * ミューテックスを開放します。
 */
gboolean PYROPE_API w32_mutex_release(Mutex* self);


/**
 * ミューテックスが信号を受信するまで現在のスレッドをブロックします。
 */
gboolean PYROPE_API w32_mutex_wait(Mutex* self);
/**
 * ミューテックスが信号を受信するまで現在のスレッドをブロックします。
 */
gboolean PYROPE_API w32_mutex_wait_timeout(Mutex* self, guint milliseconds);


/**
 * ミューテックスを開放します。
 */
void PYROPE_API w32_mutex_destroy(Mutex* self);


#endif  /* pyrope_w32_mutex_h */
