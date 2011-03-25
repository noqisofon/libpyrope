#ifndef pyrope_security_descriptor_h
#define pyrope_security_descriptor_h


typedef     SECURITY_DESCRIPTOR         security_descriptor_t;
typedef     SECURITY_ATTRIBUTES         security_attr_t;
typedef     ACL                         access_control_list_t;


/**
 * �Z�L�����e�B�L�q�q���쐬���ĕԂ��܂��B
 *
 * \return �V�����Z�L�����e�B�L�q�q�B
 */
security_descriptor_t*
PYROPE_API
w32_security_descriptor_new();


/**
 * �w�肳�ꂽ�Z�L�����e�B�L�q�q�̒�����Ԃ��܂��B
 * \param descriptor �Z�L�����e�B�L�q�q�B
 *
 * \return �Z�L�����e�B�L�q�q�̒����B
 */
size_t
PYROPE_API
w32_security_descriptor_length(security_descriptor_t* descriptor);



/**
 * descriptor �Ɏw�肳�ꂽ���ӃA�N�Z�X���䃊�X�g��ǉ������肵�Ȃ������肵�܂��B
 */
gboolean
PYROPE_API
w32_set_security_descriptor_dacl( security_descriptor_t*     descriptor,
                                  gboolean                   present,
                                  access_control_list_t*     dacl,
                                  gboolean                   defailted );


#endif  /* pyrope_security_descriptor_h */
