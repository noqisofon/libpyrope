#ifndef pyrope_w32_signal_h
#define pyrope_w32_signal_h

#include <pyrope/security_descriptor.h>
 

struct w32_signal_t {
    handle_t    handle;
};
/**
 * 
 */
typedef     struct w32_signal_t     Signal;    


/**
 * w32 のシグナルを作成して返します。
 *
 * \return シグナルインスタンス。
 */
Signal* PYROPE_API              w32_signal_new();
/**
 * w32 のシグナルを作成します。
 * \param signal_name  シグナルの名前。
 * \param manual_reset 手動でリセットするかどうか。
 * \param init_status  シグナルの初期状態。
 * \param attribute    セキュリティ記述子。
 *
 * \return シグナルインスタンス。
 */
Signal* PYROPE_API              w32_signal_new_all( const gchar*        signal_name,
                                                    gboolean            manual_reset,
                                                    gboolean            init_state,
                                                    security_attr_t*    attribute );


/**
 * 指定されたシグナルを ON にします。
 */
gboolean PYROPE_API             w32_signal_raise(Signal* self);


/**
 * 指定されたシグナルを OFF にします。
 */
gboolean PYROPE_API             w32_signal_hang(Signal* self);


/**
 * 指定されたシグナルがレイズ状態になるまで待機します。
 */
gint PYROPE_API                 w32_signal_pause(Signal* self);


/**
 * 指定されたシグナルがレイズ状態になるまで待機します。
 */
gint PYROPE_API                 w32_signal_pause_timeout(Signal* self, guint millisecond);


/**
 * シグナルを開放します。
 */
void PYROPE_API                 w32_signal_destroy(Signal* self);


#endif  /* pyrope_w32_signal_h */
