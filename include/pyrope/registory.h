#ifndef pyrope_registory_h
#define pyrope_registory_h


typedef     HKEY        registory_t;
typedef     guint       registry_mask_t;


struct w32_registry_section_t {
    registory_t     parent_section;     //!< 所属しているレジストリセクション。
    gchar*          entry_name;         //!< エントリ名。
    guint           value_type;         //!< エントリの値の型。
    gbyte*          value;              //!< エントリの値。
    size_t          value_size;         //!< エントリの値のサイズ。
};


typedef     struct w32_registry_section_t       RegistorySection;


/**
 * 指定されたレジストリキーを開きます。
 *
 * \param  parent_section  親セクションのハンドル。
 * \param  subkey_name     開きたいサブキーの名前。
 * \param  mask_desired    セキュリティアクセスマスク。
 */
registory_t PYROPE_API w32_registory_open( registory_t          parent_section,
                                           gchar*               subkey_name,
                                           registry_mask_t      mask_desired );


/**
 * 指定されたレジストリキーに所属している、指定されたエントリのデータ型とデータを取得します。
 *
 * \param  parent_section  所属させるレジストリセクション。
 * \param  entry_name      レジストリエントリの名前。
 * \param  value_type      エントリの値の型。
 * \param  value           エントリの値。
 * \param  value_size      エントリの値のバイト数。
 *
 * \return 成功したら ERROR_SUCCESS。
 */
gint PYROPE_API w32_registory_query_value( registory_t      parent_section,
                                           gchar*           entry_name,
                                           guint*           value_type,
                                           gbyte*           value,
                                           guint*           value_size );


/**
 * 指定されたレジストリキーのハンドルを閉じます。
 */
gint PYROPE_API w32_registory_close(registory_t self);


/**
 * 
 */
gint PYROPE_API pyrope_query_registory_section(RegistorySection* section);


#endif  /* pyrope_registory_h */
