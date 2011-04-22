#include <stdafx.h>

#include <pyrope/handle.h>
#include <pyrope/w32_process_module.h>
#include <pyrope/w32_process.h>


gboolean PYROPE_API w32_process_kill(const Process* self)
{
    if ( !self )
        return false;
    if ( pyrope_handle_is_invalid( self->handle ) )
        return false;

    return !TerminateProcess( self->handle, 1 );
}
