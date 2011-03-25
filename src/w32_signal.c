#include <stdafx.h>

#include <pyrope/_pyrope.h>
#include <pyrope/handle.h>
#include <pyrope/w32_signal.h>


//static EventWaitHandle* w32_signal_base_new();

Signal* PYROPE_API w32_signal_new()
{
    return w32_signal_new_all( NULL, true, false, NULL );
}
Signal* PYROPE_API w32_signal_new_all( const gchar*             signal_name,
                                       gboolean                 manual_reset,
                                       gboolean                 init_state,
                                       security_attr_t*         attribute )
{
    Signal* result;

    result = g_new(Signal, 1);
    result->handle = CreateEvent( attribute,
                                  manual_reset,
                                  init_state,
                                  signal_name );

    return result;
}


gboolean PYROPE_API w32_signal_raise(Signal* self)
{
    if ( !self )
        return false;
    if ( pyrope_handle_is_invalid( self->handle ) )
        return false;

    return SetEvent( self->handle ) != 0;
}


gboolean PYROPE_API w32_signal_hang(Signal* self)
{
    if ( !self )
        return false;
    if ( pyrope_handle_is_invalid( self->handle ) )
        return false;

    return ResetEvent( self->handle ) != 0;
}


gint PYROPE_API w32_signal_pause(Signal* self)
{
    return w32_signal_pause_timeout( self->handle, INFINITE );
}


gint PYROPE_API w32_signal_pause_timeout(Signal* self, guint millisecond)
{
    DWORD   ret;

    if ( !self )
        return 0;
    if ( pyrope_handle_is_invalid( self->handle ) )
        return 0;

    ret = WaitForSingleObject( self->handle, millisecond );

    return ret == WAIT_OBJECT_0? -1: 0;
}


void PYROPE_API w32_signal_destroy(Signal* self)
{
    if ( !self )
        return ;
    if ( pyrope_handle_is_invalid( self->handle ) )
        return ;

    w32_handle_close( self->handle );
    g_delete( self );
}
