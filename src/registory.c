registory_t w32_registory_open( registory_t    parent_section,
                                const gchar*   sub_section_name,
                                access_mask_t  security_access_mask
                             )
{
    long            ret;
    regisotry_t     result_section;

    ret = RegOpenKeyEx( parent_section,
                        sub_section_name,
                        0,
                        security_acess_mask,
                        &result_section
                        );

    if ( ret != ERROR_SUCCESS )
        return INVALID_VALUE_HANDLE;

    return result_section;
}


gboolean w32_registory_close(registory_t section)
{
    
}
