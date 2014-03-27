/*
char *ip_address;
char *uri;

ip_address = sapi_getenv("HTTP_X_FORWARDED_FOR", 20 TSRMLS_CC);
if (ip_address == NULL) {
  ip_address = sapi_getenv("REMOTE_ADDR", 11 TSRMLS_CC);
  if (ip_address == NULL) {
    ip_address = "no_ip_address";
  }
}

uri = sapi_getenv("REQUEST_URI", 11 TSRMLS_CC);
if (uri == NULL) {
  uri = "no_uri";
}

php_syslog(LOG_NOTICE, "%.500s [ip:%s][uri:%s]", log_message, ip_address, uri);
 */

//PHP_METHOD(Sleepy, jsony)
SLEEPY_METHOD(jsony)
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

PHP_METHOD(Sleepy, test)
{
    /*
     * From: [main/php_variables.c - php_register_server_variables()]
     *
     * We need to have the $_SERVER superglobals initialized to read them and
     * if it is not invoked via the callee PHP script than we need to do it
     * manually.
     */

    zval *array_ptr = NULL;

    ALLOC_ZVAL(array_ptr);
    array_init(array_ptr);
    INIT_PZVAL(array_ptr);

    if (PG(http_globals)[TRACK_VARS_SERVER]) {
            zval_ptr_dtor(&PG(http_globals)[TRACK_VARS_SERVER]);
    }

    PG(http_globals)[TRACK_VARS_SERVER] = array_ptr;

    if (sapi_module.register_server_variables) {
        sapi_module.register_server_variables(array_ptr TSRMLS_CC);
    }

    /*
     * End super hacky server super global invocation from
     * [main/php_variables.c - php_register_server_variables()]
     */

    //zend_auto_global_disable_jit("_SERVER", sizeof("_SERVER")-1 TSRMLS_DC);
    //zend_activate_auto_globals(TSRMLS_DC);

    zend_llist_position pos;
    sapi_header_struct* h;

    for (h = (sapi_header_struct*)zend_llist_get_first_ex(&SG(sapi_headers).headers, &pos);
         h;
         h = (sapi_header_struct*)zend_llist_get_next_ex(&SG(sapi_headers).headers, &pos))
    {
        php_printf("SAPI! %.*s <br/>", h->header_len, h->header);
    }

    zval **http_user_agent;

    /* This only works if the $_SERVER super global is invoked beforehand. */
    if ( zend_hash_exists(HASH_OF(PG(http_globals)[TRACK_VARS_SERVER]), ZEND_STRS("HTTP_USER_AGENT")) ) {
        /* FYI, zend_hash_exists() returns "1" upon success so you can't use the "SUCCESS" macro which expands to "0" */
        zend_hash_find(HASH_OF(PG(http_globals)[TRACK_VARS_SERVER]), ZEND_STRS("HTTP_USER_AGENT"), (void **)&http_user_agent);
        php_printf("User Agent 007: %s\n", Z_STRVAL_PP(http_user_agent));
    } else {
        php_printf("No user agent found :(\n");
    }

    /* Setting of status code from (which has a lot of good stuff...)
     * [main/SAPI.c - sapi_update_response_code()
     * sapi_update_response_code(int ncode TSRMLS_DC)
     */
    //int ncode = 202;

    /* if the status code did not change, we do not want
       to change the status line, and no need to change the code */
    //if (SG(sapi_headers).http_response_code == ncode) {
    //    return;
    //}
    //if (SG(sapi_headers).http_status_line) {
    //    efree(SG(sapi_headers).http_status_line);
    //    SG(sapi_headers).http_status_line = NULL;
    //}
    //SG(sapi_headers).http_response_code = ncode;


    //if ( zend_hash_exists(HASH_OF(PG(http_globals)[TRACK_VARS_SERVER]), ZEND_STRS("HTTP_USER_AGENT")) ) {

    /*
     * The Z_STRLEN & Z_STRVAL variadic macros expand into the command below. For the "_PP" variants they would presumably prepend "**" to said non-expanded macros.
     *
     * php_printf("|||%.*s|||\n", Z_STRLEN_PP(http_user_agent), Z_STRVAL_PP(http_user_agent));
     * php_printf("|||%.*s|||\n", http_user_agent->value.str.len, http_user_agent->value.str.val);
     */

}
