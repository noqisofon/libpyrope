#include <pyrope/w32_process_module.h>


struct w32_process_heap_t {
    handle_t      handle;
    guint         options;
    size_t        initial_size;
    size_t        maximum_size;
};



typedef     struct w32_process_heap_t       ProcessHeap;
