#include "php.h"
#include "SAPI.h"
#include "zend_API.h"

#include "php_sleepy.h"
#include "test.c"

/*
 * ----------------------------------
 * RANDOM ZEND ENGINE MACRO REFERENCE
 * ----------------------------------
 * 
 * #define ZEND_STRL(str)      (str), (sizeof(str)-1)
 * #define ZEND_STRS(str)      (str), (sizeof(str))
 *
 * Cast a value to "zend_bool" which is a typedef for "unsigned char".
 * #define ZEND_TRUTH(x)       ((x) ? 1 : 0)
 *
 * [Zend/zend.h]
 * #define SUCCESS 0
 * #define FAILURE -1  
 * 
 * [zend_API.h]
 * #define ZEND_FE_END            { NULL, NULL, NULL, 0, 0 }
 * #define ZEND_NS_NAME(ns, name)          ns "\\" name
 * #define ZEND_ME(classname, name, arg_info, flags)   ZEND_FENTRY(name, ZEND_MN(classname##_##name), arg_info, flags)
 */

/*
 * --------------
 * RANDOM C NOTES
 * --------------
 * sizeof(unsigned char) == 1
 * sizeof(unsigned int)  == 4
 * sizeof(size_t)        == 8
 */

const zend_function_entry sleepy_class_methods[] = {
    PHP_ME(Sleepy, test, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    {NULL, NULL, NULL}
};

zend_module_entry sleepy_module_entry = {
    STANDARD_MODULE_HEADER,
    PHP_SLEEPY_EXTNAME,
    sleepy_class_methods,      /* Extension Function Entries         */
    PHP_MINIT(sleepy),         /* MINIT     - Module Initialization  */
    NULL,                      /* MSHUTDOWN - Module Shutdown        */
    PHP_RINIT(sleepy),         /* RINIT     - Request Initialization */
    NULL,                      /* RSHUTDOWN - Request Shutdown       */
    NULL,                      /* MINFO     - Module Information     */
    NO_VERSION_YET,            /* Extension Version Number           */
    STANDARD_MODULE_PROPERTIES
};

ZEND_GET_MODULE(sleepy)

zend_class_entry *ce_Sleepy;

PHP_MINIT_FUNCTION(sleepy)
{
    zend_class_entry ce;

    INIT_CLASS_ENTRY(ce, "Sleepy", sleepy_class_methods);
    ce.create_object = NULL;
    ce_Sleepy = zend_register_internal_class(&ce TSRMLS_CC);

    return SUCCESS;
}

PHP_RINIT_FUNCTION(sleepy)
{
    /* Declare your class constants after you register the class, duh me... */

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