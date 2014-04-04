/*
 * PHPAPI void php_explode(zval *delim, zval *str, zval *return_value, long limit);
 *
 * @see http://lxr.php.net/xref/PHP_5_5/ext/standard/php_string.h#141
 */

SLEEPY_METHOD(negotiateContent)
{
    zval *http_accept, *delim; /*, *accept_array;*/

    /**
     * This methodology is utilized in "main/php_variables.c" in the PHP source and it saved my sanity here.
     */
     zval *accept_array = NULL;

    ALLOC_ZVAL(accept_array);
    array_init(accept_array);
    INIT_PZVAL(accept_array);

    /*ZVAL_EMPTY_STRING(http_accept);*/
    MAKE_STD_ZVAL(http_accept);
    ZVAL_EMPTY_STRING(http_accept);
    MAKE_STD_ZVAL(delim);
    /*array_init(accept_array);*/
    CHECK_ZVAL_STRING(http_accept);

/*
    array_init(accept_array);
    array_init_size(accept_array, 10);
    add_assoc_long(accept_array, "omg", 1337);
*/
    /**
     * 3rd argv is "make a copy of string"
     */
    ZVAL_STRING(delim, ";", 0);

    /**
     * Checks if a string is zero terminated.
     */
    CHECK_ZVAL_STRING(delim);

    /**
     * Using the `ZEND_FETCH_CLASS_SILENT` flag allows `zend_get_constant_ex()` to fail silently.
     */
    if (zend_get_constant_ex(ZEND_STRL("Sleepy::HTTP_ACCEPT"), http_accept, NULL, ZEND_FETCH_CLASS_SILENT TSRMLS_DC)) {
        /*php_printf("%s", Z_STRVAL_P(http_accept));*/
    } else {
        php_printf("Nope");
    }


    /**
     * Doing `25` as our threshold here as a placeholder for "limit" until a proper way is implemented.
     */
    php_explode(delim, http_accept, accept_array, 25);

    /*
    zval_ptr_dtor(delim);
    zval_ptr_dtor(http_accept);
    */

    /**
     * #include <zend_API.h>
     *
     * void RETURN_ZVAL ( zval * zv, bool copy, bool dtor )
     *
     * zv
     *     Pointer to the zval to return.
     * copy
     *     Create a copy of zv before returning it?
     * dtor
     *     Destruct the original value before returning from the function, this is needed if zv was only temporarily created within the function.
     *
     * @see http://www.cs.unomaha.edu/local/php_manual/zend-macro.return-zval.html
     */
    RETURN_ZVAL(accept_array, 0, 1);


    /*php_var_dump(&accept_array, 1 TSRMLS_DC);*/

    /*zval_dtor(&http_accept);*/

    /*RETURN_ZVAL(&accept_array, 1, 1);*/
}
