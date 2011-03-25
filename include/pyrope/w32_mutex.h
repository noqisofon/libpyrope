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
 * �~���[�e�b�N�X���쐬���ĕԂ��܂��B
 */
Mutex* PYROPE_API w32_mutex_new();
/**
 * ���O�t���� �~���[�e�b�N�X���쐬���ĕԂ��܂��B
 */
Mutex* PYROPE_API w32_mutex_new_from_name(const gchar* name);
/**
 * �~���[�e�b�N�X�̏������L���̗L����\���^�U�l�ƃ~���[�e�b�N�X�̖��O����~���[�e�b�N�X���쐬���ĕԂ��܂��B
 */
Mutex* PYROPE_API w32_mutex_new_owned(gboolean initially_owned, const gchar* name);
/**
 * �~���[�e�b�N�X�̏������L���̗L����\���^�U�l�ƃ~���[�e�b�N�X�̖��O����~���[�e�b�N�X���쐬���ĕԂ��܂��B
 */
Mutex* PYROPE_API w32_mutex_new_is_initially_create(gboolean initially_owned, const gchar* name, gboolean* create_new);


/**
 * �����̖��O�t���~���[�e�b�N�X���J���܂��B
 */
Mutex* PYROPE_API w32_mutex_open_existing(const gchar* name);


/**
 * �~���[�e�b�N�X���J�����܂��B
 */
gboolean PYROPE_API w32_mutex_release(Mutex* self);


/**
 * �~���[�e�b�N�X���M������M����܂Ō��݂̃X���b�h���u���b�N���܂��B
 */
gboolean PYROPE_API w32_mutex_wait(Mutex* self);
/**
 * �~���[�e�b�N�X���M������M����܂Ō��݂̃X���b�h���u���b�N���܂��B
 */
gboolean PYROPE_API w32_mutex_wait_timeout(Mutex* self, guint milliseconds);


/**
 * �~���[�e�b�N�X���J�����܂��B
 */
void PYROPE_API w32_mutex_destroy(Mutex* self);


#endif  /* pyrope_w32_mutex_h */
