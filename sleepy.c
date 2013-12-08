#include <php.h>
#include "php_sleepy.h"
#include <SAPI.h>
#include <zend_API.h>

zend_module_entry sleepy_module_entry = {
    STANDARD_MODULE_HEADER,
    PHP_SLEEPY_EXTNAME,
    NULL,               /* Extension Function Entries         */
    PHP_MINIT(sleepy),  /* MINIT     - Module Initialization  */
    NULL,               /* MSHUTDOWN - Module Shutdown        */
    PHP_RINIT(sleepy),  /* RINIT     - Request Initialization */
    NULL,               /* RSHUTDOWN - Request Shutdown       */
    NULL,               /* MINFO     - Module Information     */
    PHP_SLEEPY_VERSION, /* Extension Version Number           */
    STANDARD_MODULE_PROPERTIES
};

ZEND_GET_MODULE(sleepy)

zend_class_entry *ce_Sleepy;

PHP_MINIT_FUNCTION(sleepy)
{
    zend_class_entry ce;

    INIT_CLASS_ENTRY(ce, "Sleepy", NULL);
    ce.create_object = NULL;
    ce_Sleepy = zend_register_internal_class(&ce TSRMLS_CC);

    /* Declare your class constants after you register the class, duh me... */
    //zend_declare_class_constant_bool(ce_Sleepy, ZEND_STRL("SLEEPY_URI"), 0 TSRMLS_DC);

    return SUCCESS;
}

PHP_RINIT_FUNCTION(sleepy)
{
    /* Request Method */
    if (SG(request_info).request_method) {
        zend_declare_class_constant_string(ce_Sleepy, ZEND_STRL("REQUEST_METHOD"), SG(request_info).request_method TSRMLS_DC);
    } else {
        zend_declare_class_constant_bool(ce_Sleepy, ZEND_STRL("REQUEST_METHOD"), 0 TSRMLS_DC);
    }
    
    /* Request URI */
    if (SG(request_info).request_uri) {
        zend_declare_class_constant_string(ce_Sleepy, ZEND_STRL("REQUEST_URI"), SG(request_info).request_uri TSRMLS_DC);
    } else {
        zend_declare_class_constant_bool(ce_Sleepy, ZEND_STRL("REQUEST_URI"), 0 TSRMLS_DC);
    }

    /* Query String */
    if (SG(request_info).query_string) {
        zend_declare_class_constant_string(ce_Sleepy, ZEND_STRL("QUERY_STRING"), SG(request_info).query_string TSRMLS_DC);
    } else {
        zend_declare_class_constant_bool(ce_Sleepy, ZEND_STRL("QUERY_STRING"), 0 TSRMLS_DC);
    }

    /* Response Code */
    if (SG(sapi_headers).http_response_code) {
        zend_declare_class_constant_long(ce_Sleepy, ZEND_STRL("RESPONSE_CODE"), SG(sapi_headers).http_response_code TSRMLS_DC);
    } else {
        zend_declare_class_constant_bool(ce_Sleepy, ZEND_STRL("RESPONSE_CODE"), 0 TSRMLS_DC);
    }

    return SUCCESS;
}
