SLEEPY_METHOD(encodeJson)
{
    zval *src_array;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_DC, "a", &src_array) == FAILURE) {
        RETURN_FALSE;
    }

    /**
     * `smart_str` info from phpinternalsbook.com
     *
     * @see http://www.phpinternalsbook.com/classes_objects/serialization.html#serializing-internal-objects
     *
     * Furthermore we create a smart string using smart_str buf = {0}. The = {0}
     * initializes all members of the struct with zero. This struct looks as
     * follows:
     *
     *     typedef struct {
     *         char *c;
     *         size_t len;
     *         size_t a;
     *     } smart_str;
     *
     * c is the buffer of the string, len the currently used length and a the
     * size of the current allocation (as this is smart string this doesn’t
     * necessarily match len).
     */
    smart_str dest_str = {0};

    /**
     * zval *val_array;
     * array_init(val_array);
     * array_init_size(val_array, 1000000);
     * add_assoc_long(val_array, "omg", 1337);
    */

    int options = PHP_JSON_PRETTY_PRINT; // 0;

    /**
     * @see http://lxr.php.net/xref/PHP_5_5/ext/json/php_json.h [line 52]
     *
     * PHP_JSON_API void php_json_encode(smart_str *buf, zval *val, int options TSRMLS_DC);
     */
    php_json_encode(&dest_str, src_array, options TSRMLS_CC);

    /**
     * This appears to just be a variadic macro that zero terminates strings.
     *
     * @see http://lxr.php.net/xref/PHP_5_5/ext/standard/php_smart_str.h#31
     *
     * #define smart_str_0(x) do {                                         \
     *     if ((x)->c) {                                                   \
     *         (x)->c[(x)->len] = '\0';                                    \
     *     }                                                               \
     * } while (0)
     */
    smart_str_0(&dest_str);

    /**
     * FYI don't free any of the argument vectors, it will wipe them out in
     * userspace. I kinda guessed, but figured I'd check it out...
     */
    //zval_dtor(src_array);
    //zval_ptr_dtor(&src_array);
    //FREE_ZVAL(src_array);

    /**
     * [smart_str].c   <- Character pointer
     * [smart_str].len <- Character length
     * [Boolean false] <- Make duplicate
     */
    RETURN_STRINGL(dest_str.c, dest_str.len, false);
}
