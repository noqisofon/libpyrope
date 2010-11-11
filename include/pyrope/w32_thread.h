#ifndef pyrope_w32_thread_h
#define pyrope_w32_thread_h

#include <pyrope/_pyrope.h>


typedef     HANDLE       w32_thread_t;


/**
 * �X���b�h���쐬���܂��B
 */
int w32_thread_create( w32_thread_t*        thread,
                       security_attr_t*     attr,
                       unsigned             (__stdcall *start_routine)(void*),
                       void*                arg
                       );


/**
 * �X���b�h���I�����܂��B
 */
void w32_thread_exit(unsigned retcode);


/**
 * �w�肳�ꂽ�X���b�h�̎��s�𒆒f���܂��B
 */
int w32_thread_suspend(w32_thread_t self);


/**
 * �X���b�h�̒��f�J�E���g�� 1 ���炵�܂��B���f�J�E���g�� 0 �ɂȂ�ƁA�X���b�h�̎��s���ĊJ����܂��B
 */
int w32_thread_resume(w32_thread_t self);


/**
 * �w�肵���X���b�h�̑��ΗD�揇�ʂ�Ԃ��܂��B
 */
int w32_get_thread_priority(w32_thread_t self);


/**
 * �w�肵���X���b�h�̑��ΗD�揇�ʂ��w�肵�܂��B
 */
gboolean w32_set_thread_priority(w32_thread_t self, int priority);


/**
 * �Ăяo�����X���b�h�̃n���h����Ԃ��܂��B
 */
w32_thread_t w32_get_current_thread();


/**
 * �w�肳�ꂽ�����̃X���b�h�n���h����Ԃ��܂��B
 */
w32_thread_t w32_thread_open( uint32_t   desired_access,
                              gboolean   inherit_handle,
                              uint32_t   thread_id
                              );


/**
 * �Ăяo�����X���b�h�̃X���b�h���ʎq��Ԃ��܂��B
 */
uint32_t w32_get_current_thread_id();


#endif  /* pyrope_w32_thread_h */
