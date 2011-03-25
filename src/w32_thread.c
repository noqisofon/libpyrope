/** \file thread.c
 *
 */
#include <stdafx.h>

#include <process.h>

#include <pyrope/_pyrope.h>
#include <pyrope/handle.h>
#include <pyrope/security_descriptor.h>
#include <pyrope/w32_thread.h>


gint PYROPE_API w32_thread_create( w32_thread_t*        thread_handle,
                        security_attr_t*     attribute,
                        unsigned             (__stdcall *start_routine)(void*),
                        void*                arglist
                        )
{
    if ( !start_routine || !thread_handle )
        return -1;

    /*
     * 常識的に考えた結果、_beginthreadex 関数を使うハメになる。
     */
    *thread_handle  = __REINTERPRET_CAST(w32_thread_t, _beginthreadex( attribute,
                                                                       0,
                                                                       start_routine,
                                                                       arglist,
                                                                       0,
                                                                       NULL
                                                                       )
                                         );

    return *thread_handle != 0? 0: -1;
}


void PYROPE_API w32_thread_exit(unsigned retcode)
{
    _endthreadex( retcode );
}


gint PYROPE_API w32_thread_suspend(w32_thread_t self)
{
    if ( pyrope_handle_is_invalid( self ) )
        return -1;

    return SuspendThread( self );
}


gint PYROPE_API w32_thread_resume(w32_thread_t self)
{
    if ( pyrope_handle_is_invalid( self ) )
        return -1;

    return ResumeThread( self );
}


w32_thread_t PYROPE_API w32_get_current_thread()
{
    return __REINTERPRET_CAST(w32_thread_t, GetCurrentThread());
}


gint PYROPE_API w32_get_thread_priority(w32_thread_t self)
{
    if ( pyrope_handle_is_invalid( self ) )
        return -1;

    return GetThreadPriority( self );
}


gboolean PYROPE_API w32_set_thread_priority(w32_thread_t self, gint priority)
{
    if ( pyrope_handle_is_invalid( self ) )
        return false;

    return SetThreadPriority( self, priority ) != 0;
}


w32_thread_t PYROPE_API w32_thread_open( guint     desired_access,
                              gboolean  inherit_handle,
                              guint     thread_id
                              )
{
    w32_thread_t    ret_handle;

    if ( thread_id != 0 )
        return INVALID_HANDLE_VALUE;

    /*
     * TODO:
     *      desired_access には少なくとも STANDARD_RIGHTS_REQUIRED が
     *      含まれていなければならない。
     */
    ret_handle  = OpenThread( desired_access,
                              inherit_handle,
                              thread_id
                              );
    if ( ret_handle == NULL )
        return INVALID_HANDLE_VALUE;

    return ret_handle;
}


guint PYROPE_API w32_get_current_thread_id()
{
    return __STATIC_CAST( guint, GetCurrentThreadId() );
}
