#include <stdafx.h>

#include <pyrope/_pyrope.h>
#include <pyrope/security_descriptor.h>


security_descriptor_t* PYROPE_API w32_security_descriptor_new()
{
    security_descriptor_t*   descriptor;

    descriptor = ALLOC(security_descriptor_t);

    if ( !InitializeSecurityDescriptor( descriptor, SECURITY_DESCRIPTOR_REVISION ) ) {
        g_delete(descriptor);

        return NULL;
    }
    return descriptor;
}


size_t PYROPE_API w32_security_descriptor_length(security_descriptor_t* descriptor)
{
    DWORD   declen;

    if ( !descriptor )
        return 0;

    declen  = GetSecurityDescriptorLength( descriptor );

    return __STATIC_CAST(size_t, declen);
}


gboolean PYROPE_API w32_set_security_descriptor_dacl( security_descriptor_t*     descriptor,
                                                      gboolean                   present,
                                                      access_control_list_t*     dacl,
                                                      gboolean                   defaulted )
{
    if ( !descriptor )
        return 0;

    if ( !SetSecurityDescriptorDacl( descriptor,
                                     present,
                                     dacl,
                                     defaulted ) )
        return false;

    return true;
}
