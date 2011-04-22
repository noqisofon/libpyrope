#include <stdafx.h>

#include <psapi.h>

#include <pyrope/handle.h>
#include <pyrope/w32_process_module.h>


ProcessModule* pyrope_process_module_new(handle_t process, handle_t module)
{
    ProcessModule*   self;
    DWORD            len;
    MODULEINFO       module_info;

    if ( pyrope_handle_is_invalid( module ) )
        return NULL;

    self = g_new(ProcessModule, 1);

    len = GetModuleFileNameEx( process, module, self->filename, 0 );
    self->filename = g_strnfill( len, '\0' );
    len = GetModuleFileNameEx( process, module, self->filename, len );

    if ( !GetModuleInformation( process, module, &module_info, sizeof(MODULEINFO) ) ) {
        self->base_address = module_info.lpBaseOfDll;
        self->entrypoint_address = module_info.EntryPoint;
        self->memory_size = module_info.SizeOfImage;
    } else {
        self->base_address = NULL;
        self->entrypoint_address = NULL;
        self->memory_size = 0;
    }

    len = GetModuleBaseName( process, module, self->name, 0  );
    self->name = g_strnfill( len, '\0' );
    len = GetModuleBaseName( process, module, self->name, len  );

    return self;
}


void pyrope_process_module_destroy(ProcessModule* self)
{
    if ( !self )
        return ;

    g_delete( self->filename );
    g_delete( self->name );
    g_delete( self );
}
