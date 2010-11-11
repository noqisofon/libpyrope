gchar*  w32_str_error(guint err)
{
    VALUE       message_buffer;
    gchar*      result_text;
    size_t      result_text_length;

    result_text_length = FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER
                                        | FORMAT_MESSAGE_FROM_SYSTEM
                                        | FORMAT_MESSAGE_IGNORE_INSERTS,
                                        NULL,
                                        err,
                                        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                                        __REINTERPRET_CAST(LPTSTR, &message_buffer),
                                        0,
                                        NULL
                                        );
    /* 
     * 
     */
    if ( result_text_length == 0 )
        return NULL;
    /* 
     * 末尾の改行コードを 0 で埋めます。
     */
    __REINTERPRET_CAST(LPTSTR, message_buffer)[result_text_length - 1]  = '\0';
    __REINTERPRET_CAST(LPTSTR, message_buffer)[result_text_length - 2]  = '\0';

    result_text     = g_strdup( __REINTERPRET_CAST(LPTSTR, message_buffer) );

    LocalFree( message_buffer );

    return result_text;
}
