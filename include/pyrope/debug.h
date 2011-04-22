#ifndef pyrope_debug_h
#define pyrope_debug_h


/**
 * スピーカーから単純な音を鳴らします。
 */
gboolean PYROPE_API w32_beep(guint frequency, guint duration);


/**
 * 
 */
gchar* PYROPE_API w32_str_error(guint err);


#endif  /* pyrope_debug_h */
