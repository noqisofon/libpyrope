#ifndef pyrope_w32_signal_h
#define pyrope_w32_signal_h

#include <pyrope/security_descriptor.h>


typedef     HANDLE      w32_signal_t;


/**
 * w32 のシグナルを作成します。
 */
w32_signal_t        w32_w32_signal_new( const gchar*            signal_name,
                                           gboolean             manual_reset,
                                           gboolean             init_state,
                                           security_attr_t*     attribute
                                          );


/**
 * 指定されたシグナルを ON にします。
 */
gboolean            w32_signal_raise(w32_signal_t self);


/**
 * 指定されたシグナルを OFF にします。
 */
gboolean            w32_signal_sink(w32_signal_t self);


/**
 * 指定されたシグナルがレイズ状態になるまで待機します。
 */
int                 w32_signal_pause(w32_signal_t self);


/**
 * 指定されたシグナルがレイズ状態になるまで待機します。
 */
int                 w32_signal_pause_timeout(w32_signal_t self, uint32_t millisecond);


#endif  /* pyrope_w32_signal_h */
