#ifndef pyrope_w32_thread_h
#define pyrope_w32_thread_h


typedef     HANDLE       w32_thread_t;


/**
 * �X���b�h���쐬���܂��B
 */
gint PYROPE_API w32_thread_create( w32_thread_t*        thread_handle,
                        security_attr_t*     attribute,
                        unsigned             (__stdcall *start_routine)(void*),
                        void*                arglist
                        );


/**
 * �X���b�h���I�����܂��B
 */
void PYROPE_API w32_thread_exit(guint retcode);


/**
 * �w�肳�ꂽ�X���b�h�̎��s�𒆒f���܂��B
 */
gint PYROPE_API w32_thread_suspend(w32_thread_t self);


/**
 * �X���b�h�̒��f�J�E���g�� 1 ���炵�܂��B���f�J�E���g�� 0 �ɂȂ�ƁA�X���b�h�̎��s���ĊJ����܂��B
 */
gint PYROPE_API w32_thread_resume(w32_thread_t self);


/**
 * �w�肵���X���b�h�̑��ΗD�揇�ʂ�Ԃ��܂��B
 */
gint PYROPE_API w32_get_thread_priority(w32_thread_t self);


/**
 * �w�肵���X���b�h�̑��ΗD�揇�ʂ��w�肵�܂��B
 */
gboolean PYROPE_API w32_set_thread_priority(w32_thread_t self, int priority);


/**
 * �Ăяo�����X���b�h�̃n���h����Ԃ��܂��B
 */
w32_thread_t PYROPE_API w32_get_current_thread();


/**
 * �w�肳�ꂽ�����̃X���b�h�n���h����Ԃ��܂��B
 */
w32_thread_t PYROPE_API w32_thread_open( guint     desired_access,
                              gboolean  inherit_handle,
                              guint     thread_id
                              );


/**
 * �Ăяo�����X���b�h�̃X���b�h���ʎq��Ԃ��܂��B
 */
guint PYROPE_API w32_get_current_thread_id();


#endif  /* pyrope_w32_thread_h */
