PHP_METHOD(Sleepy, setStatusCode)
{
    long status_code;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_DC, "l", &status_code) == FAILURE) {
        RETURN_NULL();
    }

    //long stuff = status_code;

    /* if the status code did not change, we do not want
       to change the status line, and no need to change the code */
    //if (SG(sapi_headers).http_response_code == stuff) {
    if (SG(sapi_headers).http_response_code == status_code) {
        return;
    }
    if (SG(sapi_headers).http_status_line) {
        efree(SG(sapi_headers).http_status_line);
        SG(sapi_headers).http_status_line = NULL;
    }
    //SG(sapi_headers).http_response_code = stuff;
    SG(sapi_headers).http_response_code = status_code;
}

//"l", &maxGear) == FAILURE) {
//        RETURN_NULL();
//    }