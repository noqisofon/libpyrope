#include <stdafx.h>

#include <pyrope/handle.h>
#include <pyrope/w32_signal.h>


w32_signal_t        w32_signal_new( const gchar*             signal_name,
                                           gboolean                 manual_reset,
                                           gboolean                 init_state,
                                           security_attr_t*     attribute
                                          )
{
    return CreateEvent( attribute,
                        manual_reset,
                        init_state,
                        signal_name
                        );
}


gboolean w32_signal_raise(w32_signal_t self)
{
    if ( !self )
        return false;

    return SetEvent( self ) != 0;
}


gboolean w32_signal_sink(w32_signal_t self)
{
    if ( !self )
        return false;

    return ResetEvent( self ) != 0;
}


int w32_signal_pause(w32_signal_t self)
{
    return w32_signal_pause_timeout( self, INFINITE );
}


int w32_signal_pause_timeout(w32_signal_t self, uint32_t millisecond)
{
    DWORD   ret;

    if ( pyrope_handle_is_invalid( self ) )
        return 0;

    ret = WaitForSingleObject( self, millisecond );

    return ret == WAIT_OBJECT_0? -1: 0;
}
