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
    VALUE  base_address;  //!< ���W���[�����ǂݍ��܂ꂽ�������A�h���X��\���܂��B
    VALUE  entrypoint_address;  //!< �V�X�e�������W���[����ǂݍ���Ŏ��s����Ƃ��ɌĂяo�����֐��̃������A�h���X��\���܂��B
    gchar* filename;  //!< ���W���[���̊��S�p�X��\���܂��B
    size_t memory_size;  //!< ���W���[���̓Ǎ��ɕK�v�ȃ������e�ʂ��擾���܂��B
    gchar* name;  //!< ���W���[������\���܂��B
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
