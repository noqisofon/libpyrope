/**
 * �w�肳�ꂽ���W�X�g���Z�N�V�����̃n���h����Ԃ��܂��B
 */
registory_t w32_registory_open( registory_t    parent_section,
                                const gchar*   sub_section_name,
                                access_mask_t  security_access_mask
                             );


/**
 * �w�肳�ꂽ���W�X�g���Z�N�V�����̃n���h������܂��B
 */
gboolean w32_registory_close(registory_t section);