#include <stdafx.h>

#include <pyrope/_pyrope.h>
#include <pyrope/win32io_util.h>


/**
 * pyrope_recursive_delete_directory 関数で呼び出されます。
 */
static gboolean _M_delete_directory_closure( const gchar*       parent_path,
                                             const gchar*       directory_name,
                                             WIN32_FIND_DATA*   find_data
                                             );


gint PYROPE_API pyrope_fprintf(handle_t stream, const gchar* format, ...)
{
    va_list     args;
    gint         result;

    if ( pyrope_handle_is_invalid( stream ) )

    va_start(format, args);
    result  = pyrope_vfprintf( stream, format, args );
    va_end(args);

    return result;
}


gint PYROPE_API pyrope_vfprintf(handle_t stream, const gchar* format, va_list args)
{
    gint        result;
    gchar       printing_buffer[PYROPE_PRINTING_BUFFER_LENGTH];
    ssize_t     bytes_written;

    if ( pyrope_handle_is_invalid( stream ) )
        return -1;

#ifdef _MSC_VER
    result  = _vstprintf_s( printing_buffer, PYROPE_PRINTING_BUFFER_LENGTH, format, args );
#else
    result  = _vstprintf( printing_buffer, format, args );
#endif  /* def _MSC_VER */

    if ( result == -1 )
        return -1;

    bytes_written   = w32_file_write( stream, printing_buffer, result );

    return result;
}


gboolean PYROPE_API pyrope_file_is_exist(const gchar* find_path)
{
    guint   ret;
    gint    last_separator_pos;
    gint    find_path_len;

    gchar*  parent_path;
    gchar*  filename;

    if ( !find_path )
        return false;

    last_separator_pos  = g_str_last_index_of( find_path, PYROPE_HL_DIRECTORY_SEPARATOR );
    /*
     * "\" が無かった場合、parent_path に空文字列が入り、存在しないファイルとし
     * て判定されてしまうので parent_path には "." をいれておきます。
     */
    if ( last_separator_pos == -1 )
        parent_path   = PYROPE_HL_CURRENT_DIRECTORY;
    else
        parent_path   = g_str_slice( find_path, 0, last_separator_pos );

    find_path_len = __STATIC_CAST(gint, g_strlen( find_path ));
    filename   = g_str_slice( find_path,
                              last_separator_pos + 1,
                              find_path_len - last_separator_pos
                              );

    ret = SearchPath( parent_path,
                      filename,
                      NULL,
                      0,
                      NULL,
                      NULL
                      );

    if ( last_separator_pos > 0 )
        g_delete( parent_path );
    g_delete( filename );

    return ret != 0;
}


gboolean PYROPE_API pyrope_recursive_delete_directory(const gchar* original_path)
{
    WIN32_FIND_DATA     data;

    gint        last_separator_pos;
    gchar*      filepath;
    gchar*      filepart;

    gchar*      current_path;
    gchar*      find_path;

    gchar*      tmp_fullpath;

    handle_t    finder;

    if ( !original_path )
        return false;

    last_separator_pos  = g_str_last_index_of( original_path, PYROPE_HL_DIRECTORY_SEPARATOR );
    if ( last_separator_pos == -1 )
        return false;

    filepath            = g_str_slice( original_path, 0, last_separator_pos );
    filepart            = g_str_slice_last( original_path, last_separator_pos + 1 );

    current_path        = w32_search_path( filepath, filepart );
    find_path           = pyrope_path_combine( current_path, PYROPE_HL_CURRENT_DIRECTORY );

    finder              = w32_find_begin( find_path, &data );
    if ( pyrope_handle_is_invalid( finder ) ) {
        g_delete( filepath );
        g_delete( filepart );
        g_delete( current_path );
        g_delete( find_path );

        return false;
    }

    do {
        if ( !g_str_equal( data.cFileName, PYROPE_HL_CURRENT_DIRECTORY )
             && g_str_equal( data.cFileName, PYROPE_HL_PARENT_DIRECTORY ) ) {
            tmp_fullpath    = pyrope_path_combine( current_path, data.cFileName );

            if ( g_bitset_is_include( data.dwFileAttributes, FILE_ATTRIBUTE_DIRECTORY ) ) {
                if ( !_M_delete_directory_closure( current_path, data.cFileName, &data ) ) {
                    g_delete( filepath );
                    g_delete( filepart );
                    g_delete( current_path );
                    g_delete( find_path );
                    g_delete( tmp_fullpath );

                    return false;
                }
                w32_delete_directory( tmp_fullpath );
            } else
                w32_delete_file( tmp_fullpath );

            g_delete( tmp_fullpath );
        }
    } while ( w32_find_next( finder, &data ) );
    w32_find_end( finder );

    g_delete( filepath );
    g_delete( filepart );
    g_delete( current_path );
    g_delete( find_path );
    g_delete( tmp_fullpath );

    return true;
}


gchar* PYROPE_API pyrope_path_combine(const gchar* path1, const gchar* path2)
{
    size_t  path1_len, path2_len;
    gchar*  ret_path;
    gchar*  p;

    if ( !path1 )
        return NULL;
    if ( !path2 )
        return g_strdup( path1 );

    path1_len   = g_strlen( path1 );
    path2_len   = g_strlen( path2 );
    ret_path    = g_new( gchar, path1_len + 1 + path2_len );

    p   = g_str_append( ret_path, path1 );
    p   = g_str_appendch( p, PYROPE_DIRECTORY_SEPARATOR );
    p   = g_str_append( p, path2 );

    return ret_path;
}
gchar* PYROPE_API pyrope_path_combine3(const gchar* path1, const gchar* path2, const gchar* path3)
{
    size_t  path1_len, path2_len, path3_len;
    gchar*  ret_path;
    gchar*  p;

    if ( !path1 || !path2 )
        return NULL;
    if ( !path3 )
        return pyrope_path_combine( path1, path2 );

    path1_len   = g_strlen( path1 );
    path2_len   = g_strlen( path2 );
    path3_len   = g_strlen( path3 );
    ret_path    = g_new( gchar, path1_len + 1 + path2_len + 1 + path3_len );

    p   = g_str_append( ret_path, path1 );
    p   = g_str_appendch( p, PYROPE_DIRECTORY_SEPARATOR );
    p   = g_str_append( p, path2 );
    p   = g_str_appendch( p, PYROPE_DIRECTORY_SEPARATOR );
    p   = g_str_append( p, path3 );

    return ret_path;
}
gchar* PYROPE_API pyrope_path_combine4(const gchar* path1, const gchar* path2, const gchar* path3, const gchar* path4)
{
    size_t  path1_len, path2_len, path3_len, path4_len;
    gchar*  ret_path;
    gchar*  p;

    if ( !path1 || !path2 || !path3 )
        return NULL;
    if ( !path3 )
        return pyrope_path_combine( path1, path2 );
    if ( !path4 )
        return pyrope_path_combine3( path1, path2, path3 );

    path1_len   = g_strlen( path1 );
    path2_len   = g_strlen( path2 );
    path3_len   = g_strlen( path3 );
    path4_len   = g_strlen( path4 );
    ret_path    = g_new( gchar, path1_len + 1 + path2_len + 1 + path3_len + 1 + path4_len );

    p   = g_str_append( ret_path, path1 );
    p   = g_str_appendch( p, PYROPE_DIRECTORY_SEPARATOR );
    p   = g_str_append( p, path2 );
    p   = g_str_appendch( p, PYROPE_DIRECTORY_SEPARATOR );
    p   = g_str_append( p, path3 );
    p   = g_str_appendch( p, PYROPE_DIRECTORY_SEPARATOR );
    p   = g_str_append( p, path4 );

    return ret_path;
}


static gboolean _M_delete_directory_closure( const gchar*       parent_path,
                                             const gchar*       directory_name,
                                             WIN32_FIND_DATA*   find_data
                                             )
{
    gchar*      current_path;
    gchar*      find_path;
    gchar*      tmp_path;

    handle_t    finder;

    if ( !parent_path || !directory_name || !find_data )
        return false;

    current_path    = w32_search_path( parent_path, directory_name );
    find_path       = pyrope_path_combine( current_path, PYROPE_HL_WILDCARD );

    finder          = w32_find_begin( find_path, find_data );
    if ( pyrope_handle_is_invalid( finder ) ) {
        g_delete( current_path );
        g_delete( find_path );

        return false;
    }

    do {
        if ( !g_str_equal( find_data->cFileName, PYROPE_HL_CURRENT_DIRECTORY )
             && !g_str_equal( find_data->cFileName, PYROPE_HL_PARENT_DIRECTORY ) ) {
            tmp_path    = pyrope_path_combine( current_path, find_data->cFileName );

            if ( g_bitset_is_include( find_data->dwFileAttributes, FILE_ATTRIBUTE_DIRECTORY ) ) {
                // 現在のファイルデータのファイル属性がディレクトリだったら、
                if ( !_M_delete_directory_closure( current_path, find_data->cFileName, find_data) ) {
                    // ディレクトリの中身の削除が失敗したら、
                    // 最後に動的に割り当てたバッファを開放します。
                    g_delete( current_path );
                    g_delete( find_path );
                    g_delete( tmp_path );

                    return false;
                }
                w32_delete_directory( tmp_path );
            } else
                w32_delete_file( tmp_path );

            g_delete( tmp_path );
        }
    } while ( w32_find_next( finder, find_data ) );
    w32_find_end( finder );

    g_delete( current_path );
    g_delete( find_path );
    g_delete( tmp_path );

    return true;
}
