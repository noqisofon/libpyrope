#ifndef pyrope_security_descriptor_h
#define pyrope_security_descriptor_h


typedef     SECURITY_DESCRIPTOR         security_descriptor_t;
typedef     SECURITY_ATTRIBUTES         security_attr_t;
typedef     ACL                         access_control_list_t;


/**
 * セキュリティ記述子を作成して返します。
 *
 * \return 新しいセキュリティ記述子。
 */
security_descriptor_t*
PYROPE_API
w32_security_descriptor_new();


/**
 * 指定されたセキュリティ記述子の長さを返します。
 * \param descriptor セキュリティ記述子。
 *
 * \return セキュリティ記述子の長さ。
 */
size_t
PYROPE_API
w32_security_descriptor_length(security_descriptor_t* descriptor);



/**
 * descriptor に指定された随意アクセス制御リストを追加したりしなかったりします。
 */
gboolean
PYROPE_API
w32_set_security_descriptor_dacl( security_descriptor_t*     descriptor,
                                  gboolean                   present,
                                  access_control_list_t*     dacl,
                                  gboolean                   defailted );


#endif  /* pyrope_security_descriptor_h */
