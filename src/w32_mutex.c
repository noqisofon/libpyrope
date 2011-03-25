#include <stdafx.h>

#include <stdlib.h>
#include <string.h>
#include <memory.h>

#include <pyrope/_pyrope.h>
#include <pyrope/w32_mutex.h>


#if !defined(g_new)
#   define     g_new(_type_, n)        (_type_ *)g_malloc(sizeof(_type_) * n)
static void* g_malloc(size_t n)
{
    void* memret;

    if ( n == 0 )
        n = 1;
    memret = malloc( n );

    return memret;
}
#endif  /* !defined(g_new) */

#if !defined(g_delete)
#   define     g_delete(p)             free(p);
#endif  /* !defined(g_delete) */


Mutex* PYROPE_API w32_mutex_new()
{
    return w32_mutex_new_is_initially_create( TRUE, NULL, NULL );
}
Mutex* PYROPE_API w32_mutex_new_from_name(const gchar* name)
{
    return w32_mutex_new_is_initially_create( TRUE, name, NULL );
}
Mutex* PYROPE_API w32_mutex_new_owned(gboolean initially_owned, const gchar* name)
{
    return w32_mutex_new_is_initially_create( initially_owned, name, NULL );
}
Mutex* PYROPE_API w32_mutex_new_is_initially_create(gboolean initially_owned, const gchar* name, gboolean* create_new)
{
    guint   err;
    Mutex*  result;

    if ( !name )
        return NULL;

    result = g_new(Mutex, 1);
    result->handle = CreateMutex( NULL, initially_owned, name );
    result->released = FALSE;

    if ( create_new ) {
        err = GetLastError();

        if ( err == ERROR_ALREADY_EXISTS )
            *create_new = FALSE;
        else
            *create_new = TRUE;
    }

    return result;
}


Mutex* PYROPE_API w32_mutex_open_existing(const gchar* name)
{
    Mutex* result;

    if ( !name )
        return NULL;

    result = g_new(Mutex, 1);
    result->handle = OpenMutex( MUTEX_ALL_ACCESS, TRUE, name );
    result->released = FALSE;

    return result;
}


gboolean PYROPE_API w32_mutex_release(Mutex* self)
{
    gboolean ret;

    if ( !self )
        return FALSE;
    if ( self->released )
        return FALSE;

    ret = !ReleaseMutex( self->handle )? TRUE: FALSE;
    if ( ret )
        self->released = TRUE;

    return ret;
}


gboolean PYROPE_API w32_mutex_wait(Mutex* self)
{
    return w32_mutex_wait_timeout( self, INFINITE );
}
gboolean PYROPE_API w32_mutex_wait_timeout(Mutex* self, guint milliseconds)
{
    guint ret;

    if ( !self )
        return FALSE;
    if ( !self->handle )
        return FALSE;
    if ( self->released )
        return FALSE;

    ret = WaitForSingleObject( self->handle, milliseconds );

    if ( ret != WAIT_OBJECT_0 )
        return FALSE;

    return TRUE;
}


void PYROPE_API w32_mutex_destroy(Mutex* self)
{
    if ( !self )
        return ;
    if ( !self->released )
        w32_mutex_release( self );

    g_delete( self );
}
