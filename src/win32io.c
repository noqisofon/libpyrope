#include <stdafx.h>

#include <math.h>

#include <pyrope/handle.h>
#include <pyrope/win32io.h>
#include <pyrope/win32io_util.h>


/**
 * w32_get_long_filename ŠÖ”“à‚ÅŒÄ‚Ño‚³‚ê‚Ü‚·B
 */
static gchar* _M_get_long_filename_closure( const gchar*        filename,
                                            const gchar*        directory_name,
                                            WIN32_FIND_DATA*    find_data
                                            );


handle_t w32_file_open(const gchar* filename, int filemode)
{
    handle_t    stream;

    if ( !g_bitset_is_include( filemode, GENERIC_READ )
         && !g_bitset_is_include( filemode, GENERIC_WRITE )
         )
        return NULL;

    stream  = CreateFile( filename,
                          filemode,
                          FILE_SHARE_READ,
                          NULL,
                          OPEN_ALWAYS,
                          0,
                          NULL
                        );

    if ( pyrope_handle_is_invalid( stream ) )
        return stream;

    return stream;
}


ssize_t w32_file_write(handle_t stream, const VALUE buf, size_t count)
{
    unsigned int   amount_of_bytes_written;

    if ( pyrope_handle_is_invalid( stream ) )
        return -1;

    if ( !WriteFile( stream,
                     buf,
                     __STATIC_CAST(DWORD, count),
                     __REINTERPRET_CAST(DWORD *, &amount_of_bytes_written),
                     NULL
                     )
         )
        return -1;

    return __STATIC_CAST(ssize_t, amount_of_bytes_written);
}


ssize_t w32_file_read(handle_t stream, VALUE buf, size_t count)
{
    DWORD   amount_of_bytes_read;

    if ( pyrope_handle_is_invalid( stream ) )
        return -1;

    if ( !ReadFile( stream,
                    buf,
                    __STATIC_CAST(DWORD, count),
                    &amount_of_bytes_read,
                    NULL
                    )
         )
        return -1;

    return __STATIC_CAST(ssize_t, amount_of_bytes_read);
}


int w32_file_flush(handle_t stream)
{
    if ( pyrope_handle_is_invalid( stream ) )
        return -1;

    return FlushFileBuffers( stream ) != 0;
}


offset_t w32_file_seek(handle_t stream, offset_t offset, int origin)
{
    LARGE_INTEGER   large_offset;
    LARGE_INTEGER   current;

    if ( pyrope_handle_is_invalid( stream ) )
        return 0;

    large_offset.QuadPart   = offset;

    SetFilePointerEx( stream, large_offset, &current, origin );

    return current.QuadPart;
}


gchar* w32_get_current_directory()
{
    gchar*     fullpath_buffer         = NULL;
    size_t      fullpath_buffer_size    = 0;

    uint32_t    ret;

    ret = GetCurrentDirectory( __STATIC_CAST(DWORD, fullpath_buffer_size),
                               fullpath_buffer
                               );
    if ( ret > 0 ) {
        fullpath_buffer_size    = ret;
        fullpath_buffer         = g_new(gchar, fullpath_buffer_size);

        ret = GetCurrentDirectory( __STATIC_CAST(DWORD, fullpath_buffer_size),
                                   fullpath_buffer
                                   );
    }
    return fullpath_buffer;
}


gboolean w32_delete_file(const gchar* filepath)
{
    int ret;

    if ( !filepath )
        return false;
    if ( g_strlen( filepath ) == 0 )
        return false;

    ret = DeleteFile( filepath );

    return ret != 0;
}


gboolean w32_delete_directory(const gchar* dirpath)
{
    int ret;

    if ( !dirpath )
        return false;
    if ( g_strlen( dirpath ) == 0 )
        return false;

    ret = RemoveDirectory( dirpath );

    return ret != 0;
}


handle_t w32_find_begin(const gchar* path, WIN32_FIND_DATA* find_data)
{
    handle_t    ret;

    if ( !path || !find_data )
        return NULL;

    ret = FindFirstFile( path, find_data );

    return ret;
}


gboolean w32_find_next(handle_t find_handle, WIN32_FIND_DATA* find_data)
{
    if ( pyrope_handle_is_invalid( find_handle ) || !find_data )
        return false;

    return FindNextFile( find_handle, find_data ) != 0;
}


gboolean w32_find_end(handle_t find_handle)
{
    if ( pyrope_handle_is_invalid( find_handle ) )
        return false;

    return FindClose( find_handle ) != 0;
}


gchar*  w32_search_path(const gchar* find_path, const gchar* filename)
{
    gchar*      result_path;
    size_t      result_path_length;
    gchar*      file_part;

    guint       ret;

    if ( !find_path )
        return NULL;
    if ( !filename )
        return NULL;

    result_path         = NULL;
    result_path_length  = 0;

    ret     = SearchPath( find_path,
                          filename,
                          NULL,
                          __STATIC_CAST(DWORD, result_path_length),
                          result_path,
                          NULL
                          );

    if ( ret > 0 ) {
        result_path_length  = __STATIC_CAST(size_t, floor( ret * 1.5 ) );
        ret                 = 0;
        result_path         = g_new(gchar, result_path_length + 1);

        ret     = SearchPath( find_path,
                              filename,
                              NULL,
                              __STATIC_CAST(DWORD, result_path_length),
                              result_path,
                              &file_part
                              );
        if ( ret == 0 ) {
            g_delete( result_path );

            return NULL;
        }
    } else
        result_path = NULL;

    return result_path;
}


static gchar* _M_get_long_filename_closure( const gchar*        filename,
                                            const gchar*        directory_name,
                                            WIN32_FIND_DATA*    find_data
                                            )
{
    gchar*      find_path;
    gchar*      result_longname;

    handle_t    finder;

    if ( !filename || !directory_name || !find_data )
        return NULL;

    finder  = w32_find_begin( find_path, find_data );
    if ( !pyrope_handle_is_invalid( find_data ) )
        result_longname = pyrope_path_combine( directory_name, find_data->cFileName );
    else
        result_longname = NULL;
    w32_find_end( finder );

    return result_longname;
}
