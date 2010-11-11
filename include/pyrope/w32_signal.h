#ifndef pyrope_w32_signal_h
#define pyrope_w32_signal_h

#include <pyrope/security_descriptor.h>


typedef     HANDLE      w32_signal_t;


/**
 * w32 �̃V�O�i�����쐬���܂��B
 */
w32_signal_t        w32_w32_signal_new( const gchar*            signal_name,
                                           gboolean             manual_reset,
                                           gboolean             init_state,
                                           security_attr_t*     attribute
                                          );


/**
 * �w�肳�ꂽ�V�O�i���� ON �ɂ��܂��B
 */
gboolean            w32_signal_raise(w32_signal_t self);


/**
 * �w�肳�ꂽ�V�O�i���� OFF �ɂ��܂��B
 */
gboolean            w32_signal_sink(w32_signal_t self);


/**
 * �w�肳�ꂽ�V�O�i�������C�Y��ԂɂȂ�܂őҋ@���܂��B
 */
int                 w32_signal_pause(w32_signal_t self);


/**
 * �w�肳�ꂽ�V�O�i�������C�Y��ԂɂȂ�܂őҋ@���܂��B
 */
int                 w32_signal_pause_timeout(w32_signal_t self, uint32_t millisecond);


#endif  /* pyrope_w32_signal_h */
