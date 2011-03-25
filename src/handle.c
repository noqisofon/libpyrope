#include <stdafx.h>

#include <pyrope/_pyrope.h>
#include <pyrope/handle.h>


gboolean PYROPE_API pyrope_handle_is_invalid(handle_t handle)
{
    return handle == NULL
        || handle == INVALID_HANDLE_VALUE;
}


gboolean PYROPE_API w32_handle_close(handle_t handle)
{
    if ( pyrope_handle_is_invalid( handle ) )
        return false;

    return CloseHandle( handle ) != 0;
}
