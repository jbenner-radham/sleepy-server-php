#include "stdbool.h"

#include "php.h"
#include "main/SAPI.h"
#include "ext/standard/info.h"
#include "ext/standard/php_string.h"
#include "ext/standard/php_var.h"     /* php_var_dump() */
#include "ext/json/php_json.h"
#include "zend_API.h"

#include "zend_compile.h"

#include "php_sleepy.h"
#include "sleepy/_ext/sleepy_set_header.c"

// Class Methods
#include "sleepy/createJsonResponse.c"
#include "sleepy/negotiateContent.c"
#include "sleepy/encodeJson.c"
#include "sleepy/setHeader.c"
#include "sleepy/setStatusCode.c"
#include "test.c"

/**
 * OK, `phpize --clean` is awesomesauce!
 */


/**
 * @todo Make the methods actually have a return value!
 */

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

/**
 * --------------
 * RANDOM C NOTES
 * --------------
 * sizeof(unsigned char) == 1
 * sizeof(unsigned int)  == 4
 * sizeof(size_t)        == 8
 */

/*
ZEND_BEGIN_ARG_INFO_EX(zee_arg_infos, 0, 0, 0)
    ZEND_ARG_ARRAY_INFO(0, accept_array, 0)
ZEND_END_ARG_INFO();
*/

static zend_function_entry sleepy_class_methods[] = {
    PHP_ME(Sleepy, test,               NULL, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(Sleepy, createJsonResponse, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(Sleepy, encodeJson,         NULL, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(Sleepy, negotiateContent,   NULL, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(Sleepy, setJsonHeader,      NULL, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(Sleepy, setStatusCode,      NULL, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
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
    PHP_SLEEPY_VERSION,        /* Extension Version Number           */
    STANDARD_MODULE_PROPERTIES
};

ZEND_GET_MODULE(sleepy)

zend_class_entry *ce_Sleepy;

PHP_MINIT_FUNCTION(sleepy)
{
    zend_class_entry ce;

    INIT_CLASS_ENTRY(ce, "Sleepy", sleepy_class_methods);
    ce.create_object = NULL;
    ce_Sleepy = zend_register_internal_class(&ce TSRMLS_DC);

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
        //zend_declare_class_constant_string(ce_Sleepy, ZEND_STRL("REQUEST_URI"), sapi_getenv("REQUEST_URI", 11 TSRMLS_DC) TSRMLS_DC);
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

    /* HTTP Accept */

    zval **http_accept;

    /**
     * @todo Look at the following link later!
     * @see  http://stackoverflow.com/questions/10275462/a-confuse-about-post-or-get-variables-in-php-c-extensions
     */
    if ( zend_hash_exists(HASH_OF(PG(http_globals)[TRACK_VARS_SERVER]), ZEND_STRS("HTTP_ACCEPT")) ) {
        //zend_hash_find(HASH_OF(PG(http_globals)[TRACK_VARS_SERVER]), ZEND_STRS("HTTP_ACCEPT"), (void **)&http_accept);
        zend_hash_find(
            HASH_OF(PG(http_globals)[TRACK_VARS_SERVER]),
            ZEND_STRS("HTTP_ACCEPT"),
            (void **)&http_accept
        );
        /**
         * Both of these two are functionally equivalent, deciding which is more semantic...
         *
         * 1) Literal struct access
         *
         *     (**http_accept).value.str.val
         *
         * 2) Variadic macro
         *
         *     Z_STRVAL_PP(http_accept)
         */
        zend_declare_class_constant_string(ce_Sleepy, ZEND_STRL("HTTP_ACCEPT"), (**http_accept).value.str.val TSRMLS_DC);
    } else {
        zend_declare_class_constant_bool(ce_Sleepy, ZEND_STRL("HTTP_ACCEPT"), 0 TSRMLS_DC);
    }

    return SUCCESS;
}
