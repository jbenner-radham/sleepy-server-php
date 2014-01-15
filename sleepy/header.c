void sleepy_set_header(const char *header_str)
{
    zval param_str;
    INIT_ZVAL(param_str);
    ZVAL_STRING(&param_str, header_str, 1);

    zval *params = {&param_str};
    zend_uint param_count = 1;
    
    zval retval;

    zval function_name;
    INIT_ZVAL(function_name);
    ZVAL_STRING(&function_name, "header", 1);

    if (call_user_function(
            CG(function_table), 
            NULL, 
            &function_name,
            &retval, 
            param_count, 
            &params TSRMLS_DC
        ) == SUCCESS
    ) {
        // Do something if it fails...
    }

    // free the zvals yo! 
    zval_dtor(&retval);         // <- IDK if you need to free the retval...
    zval_dtor(&function_name);
}

PHP_METHOD(Sleepy, setJsonHeader)
{
    sleepy_set_header("Content-Type: application/json");
}