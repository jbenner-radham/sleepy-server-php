/*
 * PHPAPI void php_explode(zval *delim, zval *str, zval *return_value, long limit);
 *
 * @see http://lxr.php.net/xref/PHP_5_5/ext/standard/php_string.h#141
 */

SLEEPY_METHOD(negotiateContent)
{
    zval *http_accept, *delim;

    /*ZVAL_EMPTY_STRING(http_accept);*/
    MAKE_STD_ZVAL(http_accept);
    MAKE_STD_ZVAL(delim);


    /**
     * This methodology is utilized in "main/php_variables.c" in the PHP source
     * and it saved my sanity here after quite a few hours...
     */
    zval *accept_array; /* I don't believe I really need to assign this to null initially but we'll see. */

    /**
     * `ALLOC_INIT_ZVAL()` is a variadic macro that just chains
     * `ALLOC_ZVAL()` and `INIT_PZVAL()` together FYI.
     */
    ALLOC_INIT_ZVAL(accept_array);
    array_init(accept_array);

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
    RETURN_ZVAL(accept_array, 1, 1);


    /*php_var_dump(&accept_array, 1 TSRMLS_DC);*/
}
