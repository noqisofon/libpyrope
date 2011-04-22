#include <stdafx.h>

#include <pyrope/handle.h>
#include <pyrope/w32_process_module.h>
#include <pyrope/w32_process.h>


Process* w32_process_new()
{
    Process* self;

    self = g_new(Process, 1);

    self->application_name = NULL;
    self->command_line = NULL;
    self->process_attr = NULL;
    self->thread_attr = NULL;
    self->inherit_handles = FALSE;
    self->creation_flags = 0;
    self->environment = GetEnvironmentStrings();
    self->current_directory = NULL;
    self->startup_info = g_new(startup_info_t, 1);
    self->process_info = g_new(process_infomation_t, 1);

    ZeroMemory( self->startup_info, sizeof(startup_info_t) );
    ZeroMemory( self->process_info, sizeof(process_infomation_t) );

    return self;
}


Process* w32_get_current_process()
{
    Process* self = w32_process_new();

    self->command_line = GetCommandLine();
    
    self->process_info->hProcess = GetCurrentProcess();
    self->process_info->dwProcessId = GetCurrentProcessId();
    self->process_info->hThread = GetCurrentThread();
    self->process_info->dwThreadId = GetCurrentThreadId();

    GetStartupInfo( self->startup_info );

    return self;
}


handle_t w32_process_get_process_handle(Process* self)
{
    if ( !self )
        return INVALID_HANDLE_VALUE;
    if ( !self->process_info )
        return INVALID_HANDLE_VALUE;

    return GET_PROCESS_HANDLE(self);
}


gboolean w32_process_start(Process* self)
{
    gboolean ret;
    if ( !self )
        return false;
    if ( !self->startup_info )
        return false;
    if ( !self->process_info )
        return false;

    ret = CreateProcess( self->application_name,
                         self->command_line,
                         self->process_attr,
                         self->thread_attr,
                         self->inherit_handles,
                         self->creation_flags,
                         self->environment,
                         self->current_directory,
                         self->startup_info,
                         self->process_info ) != 0;

    return ret;
}


gboolean w32_process_exit(Process* self, guint exit_code)
{
    gboolean ret;
    if ( !self )
        return false;
    if ( !self->process_info )
        return false;

    ret = TerminateProcess( GET_PROCESS_HANDLE(self), exit_code ) != 0;

    return ret;
}


gboolean PYROPE_API w32_process_kill(const Process* self)
{
    if ( !self )
        return false;
    if ( pyrope_handle_is_invalid( self->handle ) )
        return false;

    return !TerminateProcess( self->handle, 1 );
}


gboolean w32_process_get_exitcode(Process* self, gint* exit_code)
{
    gboolean ret;
    if ( !self )
        return false;
    if ( !self->process_info )
        return false;
    if ( !exit_code )
        return false;

    ret = GetExitCodeProcess( GET_PROCESS_HANDLE(self), (LPDWORD)&exit_code ) != 0;

    return ret;
}


void w32_process_wait(Process* self, guint milliseconds)
{
    WaitForSingleObject( GET_PROCESS_HANDLE(self), milliseconds );
}


void w32_process_wait_for(Process* self)
{
    WaitForSingleObject( GET_PROCESS_HANDLE(self), INFINITE );
}


void w32_process_destroy(Process* self)
{
    FreeEnvironmentStrings( (LPCH)(self->environment) );
    g_delete( self->startup_info );
    g_delete( self->process_info );

    g_delete( self );
}
