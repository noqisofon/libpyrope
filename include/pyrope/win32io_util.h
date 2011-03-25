#ifndef pyrope_win32io_util_h
#define pyrope_win32io_util_h

#include <pyrope/win32io.h>


/**
 * WIN32API �̃t�@�C���n���h���p�� fprintf �֐��ł��B
 */
gint PYROPE_API pyrope_fprintf(handle_t stream, const gchar* format, ...);


/**
 * 
 */
gint PYROPE_API pyrope_vfprintf(handle_t stream, const gchar* format, va_list args);


/**
 * �w�肳�ꂽ�p�X�����݂��邩�ǂ����𔻕ʂ��܂��B
 */
gboolean PYROPE_API pyrope_file_is_exist(const gchar* find_path);


/**
 * �w�肳�ꂽ�f�B���N�g�����ċA�I�ɍ폜���܂��B
 */
gboolean PYROPE_API pyrope_recursive_delete_directory(const gchar* original_path);


/**
 * 
 */
gchar* PYROPE_API pyrope_path_combine(const gchar* path1, const gchar* path2);
/**
 * 
 */
gchar* PYROPE_API pyrope_path_combine3(const gchar* path1, const gchar* path2, const gchar* path3);
/**
 * 
 */
gchar* PYROPE_API pyrope_path_combine4(const gchar* path1, const gchar* path2, const gchar* path3, const gchar* path4);


#endif  /* pyrope_win32io_util_h */
