#ifndef pyrope_win32io_h
#define pyrope_win32io_h

#include <pyrope/handle.h>


#define     PYROPE_PRINTING_BUFFER_LENGTH       4096

#define     PYROPE_DIRECTORY_SEPARATOR          _T('\\')
#define     PYROPE_VOLUME_SEPARATOR             _T(':')
#define     PYROPE_WILDCARD                     _T('*')

#define     PYROPE_HL_CURRENT_DIRECTORY         _T(".")
#define     PYROPE_HL_PARENT_DIRECTORY          _T("..")
#define     PYROPE_HL_DIRECTORY_SEPARATOR       _T("\\")
#define     PYROPE_HL_VOLUME_SEPARATOR          _T(":")
#define     PYROPE_HL_WILDCARD                  _T("*")


/**
 * �w�肳�ꂽ�t�@�C�����J���܂��B
 */
handle_t PYROPE_API w32_file_open(const gchar* filename, int filemode);


/**
 * 
 */
ssize_t PYROPE_API w32_file_write(handle_t stream, const void* buf, size_t count);


/**
 * 
 */
ssize_t PYROPE_API w32_file_read(handle_t stream, void* buf, size_t count);


/**
 * 
 */
int PYROPE_API w32_file_flush(handle_t stream);


/**
 * 
 */
offset_t PYROPE_API w32_file_seek(handle_t stream, offset_t offset, int origin);


/**
 * ���݂̃J�����g�f�B���N�g���̃t���p�X��Ԃ��܂��B
 */
gchar* PYROPE_API w32_get_current_directory();


/**
 * �w�肳�ꂽ�t�@�C�����폜���܂��B
 */
gboolean PYROPE_API w32_delete_file(const gchar* filepath);


/**
 * �w�肳�ꂽ�f�B���N�g�����폜���܂��B
 */
gboolean PYROPE_API w32_delete_directory(const gchar* dirpath);


/**
 * 
 */
handle_t PYROPE_API w32_find_begin(const gchar* path, WIN32_FIND_DATA* find_data);


/**
 * 
 */
gboolean PYROPE_API w32_find_next(handle_t find_handle, WIN32_FIND_DATA* find_data);


/**
 * 
 */
gboolean PYROPE_API w32_find_end(handle_t find_handle);


/**
 * �w�肳�ꂽ�p�X����t�@�C�������������܂��B
 */
gchar* PYROPE_API  w32_search_path(const gchar* find_path, const gchar* filename);


#endif  /* pyrope_win32io_h */
