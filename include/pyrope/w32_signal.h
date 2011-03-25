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
 * w32 �̃V�O�i�����쐬���ĕԂ��܂��B
 *
 * \return �V�O�i���C���X�^���X�B
 */
Signal* PYROPE_API              w32_signal_new();
/**
 * w32 �̃V�O�i�����쐬���܂��B
 * \param signal_name  �V�O�i���̖��O�B
 * \param manual_reset �蓮�Ń��Z�b�g���邩�ǂ����B
 * \param init_status  �V�O�i���̏�����ԁB
 * \param attribute    �Z�L�����e�B�L�q�q�B
 *
 * \return �V�O�i���C���X�^���X�B
 */
Signal* PYROPE_API              w32_signal_new_all( const gchar*        signal_name,
                                                    gboolean            manual_reset,
                                                    gboolean            init_state,
                                                    security_attr_t*    attribute );


/**
 * �w�肳�ꂽ�V�O�i���� ON �ɂ��܂��B
 */
gboolean PYROPE_API             w32_signal_raise(Signal* self);


/**
 * �w�肳�ꂽ�V�O�i���� OFF �ɂ��܂��B
 */
gboolean PYROPE_API             w32_signal_hang(Signal* self);


/**
 * �w�肳�ꂽ�V�O�i�������C�Y��ԂɂȂ�܂őҋ@���܂��B
 */
gint PYROPE_API                 w32_signal_pause(Signal* self);


/**
 * �w�肳�ꂽ�V�O�i�������C�Y��ԂɂȂ�܂őҋ@���܂��B
 */
gint PYROPE_API                 w32_signal_pause_timeout(Signal* self, guint millisecond);


/**
 * �V�O�i�����J�����܂��B
 */
void PYROPE_API                 w32_signal_destroy(Signal* self);


#endif  /* pyrope_w32_signal_h */
