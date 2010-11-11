#include <stdafx.h>

#include <pyrope/handle.h>


gboolean pyrope_handle_is_invalid(handle_t handle)
{
    return handle == NULL
        || handle == INVALID_HANDLE_VALUE;
}


gboolean w32_handle_close(handle_t handle)
{
    if ( pyrope_handle_is_invalid( handle ) )
        return false;

    return CloseHandle( handle ) != 0;
}
