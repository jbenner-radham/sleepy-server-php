PHP_METHOD(Sleepy, test)
{
    // When in doubt... "make clean"!
    zend_llist_position pos;
    sapi_header_struct* h;
    for (h = (sapi_header_struct*)zend_llist_get_first_ex(&SG(sapi_headers).headers, &pos);
         h;
         h = (sapi_header_struct*)zend_llist_get_next_ex(&SG(sapi_headers).headers, &pos))
    {
        php_printf("SAPI! %.*s <br/>", h->header_len, h->header);
    }

    zval **http_user_agent;
    zend_hash_find(HASH_OF(PG(http_globals)[TRACK_VARS_SERVER]), "HTTP_USER_AGENT", sizeof("HTTP_USER_AGENT"), (void **)&http_user_agent);
    /* 
     * The Z_STRLEN & Z_STRVAL variadic macros expand into the command below. For the "_PP" variants they would presumably prepend "**" to said non-expanded macros.
     * php_printf("|||%.*s|||\n", http_user_agent->value.str.len, http_user_agent->value.str.val);
     */
    php_printf("|||%.*s|||\n", Z_STRLEN_PP(http_user_agent), Z_STRVAL_PP(http_user_agent));

    //php_printf("MIME Type yo! %s\n", SG(default_mimetype));
}
