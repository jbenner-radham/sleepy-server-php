PHP_METHOD(Sleepy, setStatusCode)
{
    long status_code;

    // http://www.php.net/manual/en/internals2.variables.intro.php

    // http://lxr.php.net/xref/PHP_5_5/ext/standard/head.c#290
    // This should get changed into class property at some point in the future...
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_DC, "l", &status_code) == FAILURE) {
        RETURN_NULL();
    }

    /* if the status code did not change, we do not want
       to change the status line, and no need to change the code */
    if (SG(sapi_headers).http_response_code == status_code) {
        return;
    }

    if (SG(sapi_headers).http_status_line) {
        efree(SG(sapi_headers).http_status_line);
        SG(sapi_headers).http_status_line = NULL;
    }

    SG(sapi_headers).http_response_code = status_code;
}
