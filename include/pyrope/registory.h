#ifndef pyrope_registory_h
#define pyrope_registory_h


typedef     HKEY        registory_t;
typedef     guint       registry_mask_t;


struct w32_registry_section_t {
    registory_t     parent_section;     //!< �������Ă��郌�W�X�g���Z�N�V�����B
    gchar*          entry_name;         //!< �G���g�����B
    guint           value_type;         //!< �G���g���̒l�̌^�B
    gbyte*          value;              //!< �G���g���̒l�B
    size_t          value_size;         //!< �G���g���̒l�̃T�C�Y�B
};


typedef     struct w32_registry_section_t       RegistorySection;


/**
 * �w�肳�ꂽ���W�X�g���L�[���J���܂��B
 *
 * \param  parent_section  �e�Z�N�V�����̃n���h���B
 * \param  subkey_name     �J�������T�u�L�[�̖��O�B
 * \param  mask_desired    �Z�L�����e�B�A�N�Z�X�}�X�N�B
 */
registory_t PYROPE_API w32_registory_open( registory_t          parent_section,
                                           gchar*               subkey_name,
                                           registry_mask_t      mask_desired );


/**
 * �w�肳�ꂽ���W�X�g���L�[�ɏ������Ă���A�w�肳�ꂽ�G���g���̃f�[�^�^�ƃf�[�^���擾���܂��B
 *
 * \param  parent_section  ���������郌�W�X�g���Z�N�V�����B
 * \param  entry_name      ���W�X�g���G���g���̖��O�B
 * \param  value_type      �G���g���̒l�̌^�B
 * \param  value           �G���g���̒l�B
 * \param  value_size      �G���g���̒l�̃o�C�g���B
 *
 * \return ���������� ERROR_SUCCESS�B
 */
gint PYROPE_API w32_registory_query_value( registory_t      parent_section,
                                           gchar*           entry_name,
                                           guint*           value_type,
                                           gbyte*           value,
                                           guint*           value_size );


/**
 * �w�肳�ꂽ���W�X�g���L�[�̃n���h������܂��B
 */
gint PYROPE_API w32_registory_close(registory_t self);


/**
 * 
 */
gint PYROPE_API pyrope_query_registory_section(RegistorySection* section);


#endif  /* pyrope_registory_h */
