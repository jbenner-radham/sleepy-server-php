/**
 * @todo Get rid of this non-DRY copy-pasta!!! Just doing this for quick testing...
 */
SLEEPY_METHOD(createJsonResponse)
{
    zval *src_array;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_DC, "a", &src_array) == FAILURE) {
        RETURN_FALSE;
    }

    sleepy_set_header("Content-Type: application/json");

    smart_str dest_str = {0};

    int options = PHP_JSON_PRETTY_PRINT;

    php_json_encode(&dest_str, src_array, options TSRMLS_CC);

    smart_str_0(&dest_str);

    RETURN_STRINGL(dest_str.c, dest_str.len, false);
}
