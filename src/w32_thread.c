/** \file thread.c
 *
 */
#include <stdafx.h>

#include <process.h>
#include <pyrope/security_descriptor.h>
#include <pyrope/w32_thread.h>


int w32_thread_create( w32_thread_t*        thread_handle,
                       security_attr_t*     attr,
                       unsigned             (__stdcall *start_routine)(void*),
                       void*                arg
                       )
{
    if ( !start_routine || !thread_handle )
        return -1;

    /*
     * 常識的に考えた結果、_beginthreadex 関数を使うハメになる。
     */
    *thread_handle  = __REINTERPRET_CAST(w32_thread_t, _beginthreadex( attr,
                                                                       0,
                                                                       start_routine,
                                                                       arg,
                                                                       0,
                                                                       NULL
                                                                       )
                                         );

    return *thread_handle != 0? 0: -1;
}


void w32_thread_exit(unsigned retcode)
{
    _endthreadex( retcode );
}


int w32_thread_suspend(w32_thread_t self)
{
    return SuspendThread( self );
}


int w32_thread_resume(w32_thread_t self)
{
    return ResumeThread( self );
}


w32_thread_t w32_get_current_thread()
{
    return __REINTERPRET_CAST( w32_thread_t, GetCurrentThread() );
}


int w32_get_thread_priority(w32_thread_t self)
{
    if ( !self )
        return -1;

    return GetThreadPriority( self );
}


gboolean w32_set_thread_priority(w32_thread_t self, int priority)
{

    if ( !self )
        return false;

    return SetThreadPriority( self, priority ) != 0;
}


w32_thread_t w32_thread_open( uint32_t   desired_access,
                              gboolean   inherit_handle,
                              uint32_t   thread_id
                              )
{
    w32_thread_t    ret_handle;

    if ( thread_id != 0 )
        return INVALID_HANDLE_VALUE;

    /*
     * desired_access には少なくとも STANDARD_RIGHTS_REQUIRED が含まれていなければならない。
     */
    ret_handle  = OpenThread( desired_access,
                              inherit_handle,
                              thread_id
                              );
    if ( ret_handle == NULL )
        return INVALID_HANDLE_VALUE;

    return ret_handle;
}


uint32_t w32_get_current_thread_id()
{
    return __STATIC_CAST( uint32_t, GetCurrentThread() );
}
