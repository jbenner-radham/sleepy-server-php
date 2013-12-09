PHP_METHOD(Sleepy, test)
{
    /* 
     * Taken from [main/php_variables.c]
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
     * [main/php_variables.c]
     */

    zend_llist_position pos;
    sapi_header_struct* h;

    for (h = (sapi_header_struct*)zend_llist_get_first_ex(&SG(sapi_headers).headers, &pos);
         h;
         h = (sapi_header_struct*)zend_llist_get_next_ex(&SG(sapi_headers).headers, &pos))
    {
        php_printf("SAPI! %.*s <br/>", h->header_len, h->header);
    }

    php_printf("SAPI MIME type: %s\n", SG(sapi_headers).mimetype);

    zval **http_user_agent;

    /* This only works if the $_SERVER super global is invoked beforehand. */
    int stuff = zend_hash_exists(HASH_OF(PG(http_globals)[TRACK_VARS_SERVER]), ZEND_STRS("HTTP_USER_AGENT"));
    php_printf("!!! %d !!!\n", stuff);
    //capi_sapi_module.sapi_capi_register_server_variables;
    //php_printf("__%s\n", SG(server_context));
    //php_printf("!!!!@@@%s\n", SG(sapi_headers).http_status_line);
    /* zend_hash_exists() returns "1" uppon success so you can't use the "SUCCESS" macro which expands to "0" */
    if ( zend_hash_exists(HASH_OF(PG(http_globals)[TRACK_VARS_SERVER]), ZEND_STRS("HTTP_USER_AGENT")) ) {
        //php_printf("YOLO DAWG@!! %s\n", Z_STRVAL_PP(http_user_agent));
        zend_hash_find(HASH_OF(PG(http_globals)[TRACK_VARS_SERVER]), ZEND_STRS("HTTP_USER_AGENT"), (void **)&http_user_agent);
        php_printf("User Agent 007: %s\n", Z_STRVAL_PP(http_user_agent));
        php_printf("Unsigned char: %lu\n", sizeof(unsigned char)); /* 1 */
        php_printf("Unsigned int: %lu\n", sizeof(unsigned int));   /* 4 */
        php_printf("Size_t: %lu\n", sizeof(size_t));               /* 8 */
    } else {
        php_printf("NOLO G!!!\n");
    }
    //print("!!!%n!!!\n", hi);
    //zend_hash_find( HASH_OF( PG(http_globals)[TRACK_VARS_SERVER] ), ZEND_STRS("HTTP_USER_AGENT"), (void **)&http_user_agent );
    //php_printf("Ummm... %c\n", are_you_there);
    /*if (PG(http_globals)[TRACK_VARS_SERVER] &&
        zend_hash_find(
            //HASH_OF(PG(http_globals)[TRACK_VARS_SERVER]),
            Z_ARRVAL_P(PG(http_globals)[TRACK_VARS_SERVER]), 
            ZEND_STRS("HTTP_USER_AGENT"),
            (void **)&http_user_agent
        ) == SUCCESS)
    {
        //php_printf("%s\n", Z_STRVAL_PP(http_user_agent));
        php_printf("%d\n", zend_hash_find(
            //HASH_OF(PG(http_globals)[TRACK_VARS_SERVER]),
            Z_ARRVAL_P(PG(http_globals)[TRACK_VARS_SERVER]), 
            ZEND_STRS("HTTP_USER_AGENT"),
            (void **)&http_user_agent
        ));
    }*/
    /* 
     * The Z_STRLEN & Z_STRVAL variadic macros expand into the command below. For the "_PP" variants they would presumably prepend "**" to said non-expanded macros.
     * php_printf("|||%.*s|||\n", http_user_agent->value.str.len, http_user_agent->value.str.val);
     */
    //php_printf("|||%.*s|||\n", Z_STRLEN_PP(http_user_agent), Z_STRVAL_PP(http_user_agent));

    //php_printf("%s", SG(default_mimetype));
    //php_printf("MIME Type yo! %s\n", SG(default_mimetype));
    //php_set_error_handling(EH_NORMAL, NULL TSRMLS_CC);
}
