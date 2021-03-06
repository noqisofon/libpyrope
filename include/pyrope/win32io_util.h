#ifndef pyrope_win32io_util_h
#define pyrope_win32io_util_h

#include <pyrope/win32io.h>


/**
 * WIN32API のファイルハンドル用の fprintf 関数です。
 */
int pyrope_fprintf(handle_t stream, const gchar* format, ...);


/**
 * 
 */
int pyrope_vfprintf(handle_t stream, const gchar* format, va_list args);


/**
 * 指定されたパスが存在するかどうかを判別します。
 */
gboolean pyrope_file_is_exist(const gchar* find_path);


/**
 * 指定されたディレクトリを再帰的に削除します。
 */
gboolean pyrope_recursive_delete_directory(const gchar* original_path);


/**
 * 
 */
gchar* pyrope_path_combine(const gchar* path1, const gchar* path2);
/**
 * 
 */
gchar* pyrope_path_combine3(const gchar* path1, const gchar* path2, const gchar* path3);
/**
 * 
 */
gchar* pyrope_path_combine4(const gchar* path1, const gchar* path2, const gchar* path3, const gchar* path4);


#endif  /* pyrope_win32io_util_h */
