#include <stdafx.h>
#include <windows.h>

#include <pyrope/_pyrope.h>
#include <pyrope/registory.h>


registory_t PYROPE_API w32_registory_open( registory_t     parent_section,
                                           gchar*          subkey_name,
                                           registry_mask_t mask_desired )
{
    registory_t     result;
    gint            ret;

    if ( !parent_section )
        return NULL;
    if ( !subkey_name )
        return NULL;
    if ( mask_desired == 0 )
        mask_desired = KEY_QUERY_VALUE;

    ret = RegOpenKeyEx( parent_section,
                        subkey_name,
                        0,
                        mask_desired,
                        &result );

    if ( ret == ERROR_SUCCESS )
        return result;

    return NULL;
}


gint PYROPE_API w32_registory_query_value( registory_t     parent_section,
                                           gchar*          entry_name,
                                           guint*          value_type,
                                           gbyte*          value,
                                           guint*          value_size )
{
    gint    ret;

    /*
     * ì¡íËÇÃà¯êîÇ™ñ≥å¯Ç»Ç∆Ç´Ç… -1 Çï‘ÇµèIóπÇµÇ‹Ç∑ÅB
     */
    if ( !parent_section || !entry_name || !value || !value_size )
        return -1;

    ret = RegQueryValueEx( parent_section,
                           entry_name,
                           NULL,
                           value_type,
                           value,
                           value_size );

    return ret;
}


gint PYROPE_API w32_registory_close(registory_t self)
{
    return RegCloseKey( self );
}
