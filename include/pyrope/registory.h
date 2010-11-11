/**
 * 指定されたレジストリセクションのハンドルを返します。
 */
registory_t w32_registory_open( registory_t    parent_section,
                                const gchar*   sub_section_name,
                                access_mask_t  security_access_mask
                             );


/**
 * 指定されたレジストリセクションのハンドルを閉じます。
 */
gboolean w32_registory_close(registory_t section);