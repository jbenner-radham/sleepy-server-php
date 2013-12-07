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

    return SUCCESS;
}

PHP_RINIT_FUNCTION(sleepy)
{
    /*
     * -----------
     * Access via:
     * -----------
     * echo Sleepy::$request_method;
     * echo '<br>';
     * echo Sleepy::$request_uri;
     */

    if (SG(request_info).request_method != NULL) {
        zend_declare_property_string(ce_Sleepy, ZEND_STRL("request_method"), SG(request_info).request_method, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC TSRMLS_CC);
    }
    
    if (SG(request_info).request_uri != NULL)
        zend_declare_property_string(ce_Sleepy, ZEND_STRL("request_uri"), SG(request_info).request_uri, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC TSRMLS_CC);

    return SUCCESS;
}
