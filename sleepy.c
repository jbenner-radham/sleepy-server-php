// include PHP API
#include <SAPI.h>
#include <php.h>

#include "php_sleepy.h"

// http://php.find-info.ru/php/016/ch21lev1sec1.html

/**
 * Reference: http://www.php.net/manual/en/internals2.ze1.zendapi.php#internals2.ze1.zendapi.tab.create-const
 */
PHP_MINIT_FUNCTION(sleepy)
{
    //php_printf(SG(request_info).request_method);
    //if (SG(request_info).request_method != NULL)
    //    REGISTER_STRING_CONSTANT("SLEEPY_HTTP_REQUEST", (char *)SG(request_info).request_method, CONST_CS | CONST_PERSISTENT);
    REGISTER_STRING_CONSTANT("SLEEPY_HELLO", "Hello world!", CONST_CS);

    return SUCCESS;
}

// Request Initializer...
PHP_RINIT_FUNCTION(sleepy)
{
    if (SG(request_info).request_method != NULL) {
        REGISTER_STRING_CONSTANT("SLEEPY_HTTP_REQUEST", (char *)SG(request_info).request_method, CONST_CS | CONST_PERSISTENT);
    }

    if (SG(request_info).request_uri != NULL) {
        REGISTER_STRING_CONSTANT("SLEEPY_HTTP_REQUEST_URI", SG(request_info).request_uri, CONST_CS | CONST_PERSISTENT);
    }

    return SUCCESS;
}

PHP_RSHUTDOWN_FUNCTION(sleepy)
{
    //free_zend_constant(SLEEPY_HTTP_REQUEST);

    return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(sleepy)
{
    return SUCCESS;
}

// define the function(s) we want to add
zend_function_entry sleepy_functions[] = {
  PHP_FE(sleepy, NULL)
  { NULL, NULL, NULL }
};
 
// http://php.net/manual/en/internals2.structure.modstruct.php

// "sleepy_functions" refers to the struct defined above
// we'll be filling in more of this later: you can use this to specify
// globals, php.ini info, startup and teardown functions, etc.
zend_module_entry sleepy_module_entry = {
  STANDARD_MODULE_HEADER,
  PHP_SLEEPY_EXTNAME,
  sleepy_functions,
  PHP_MINIT(sleepy),
  PHP_MSHUTDOWN(sleepy),
  PHP_RINIT(sleepy),
  NULL,
  NULL,
  PHP_SLEEPY_VERSION,
  STANDARD_MODULE_PROPERTIES
};
 
// install module
ZEND_GET_MODULE(sleepy)
 
PHP_FUNCTION(sleepy) {

/**
 * ---------------------------
 * FROM PHP-5.4.22/main/SAPI.h
 * ---------------------------
 */
//  typedef struct {
//        const char *request_method;
//        char *query_string;
//        char *post_data, *raw_post_data;
//        char *cookie_data;
//        long content_length;
//        uint post_data_length, raw_post_data_length;
//
//        char *path_translated;
//        char *request_uri;
//
//        const char *content_type;
//
//        zend_bool headers_only;
//        zend_bool no_headers;
//        zend_bool headers_read;
//
//        sapi_post_entry *post_entry;
//
//        char *content_type_dup;
//
//       /* for HTTP authentication */
//        char *auth_user;
//        char *auth_password;
//        char *auth_digest;
//
//        /* this is necessary for the CGI SAPI module */
//        char *argv0;
//
//        char *current_user;
//        int current_user_length;
//
//        /* this is necessary for CLI module */
//        int argc;
//        char **argv;
//        int proto_num;
//  } sapi_request_info;
 


    // The SAPI module is cli
    //php_printf("The SAPI module is %s\n", sapi_module.name);

    // "/htdocs/cthulhu.php" <- Returns the symlink relative path... interesting.
    //php_printf("The SAPI module is %s\n", SG(request_info).request_uri);

/**
 * Z_STRLEN_P is not a function but a macro to the string length value stored within the variable structure, so they's no unnecessary computation.
 * 
 * zend_operators.h:
 *
 * #define Z_STRLEN(zval) (zval).value.str.len
 * ...
 * #define Z_STRLEN_P(zval_p) Z_STRLEN(*zval_p)
 */

/**
 * =============================================================
 * FROM http://us1.php.net/manual/en/internals2.ze1.zendapi.php
 * Because there's no Zend Engine 2 API docs ugh... :(
 * =============================================================
 * RETURN_STRING(string, duplicate)  Returns a string. The duplicate flag indicates whether the string should be duplicated using estrdup().
 * RETURN_STRINGL(string, length, duplicate)  Returns a string of the specified length; otherwise, behaves like RETURN_STRING. This macro is faster and binary-safe, however.
 */

 // http://www.php.net/manual/en/internals2.variables.intro.php

    //php_printf("%s\n", SG(request_info).request_method);

    const char *request_method = SG(request_info).request_method;
    //MAKE_STD_ZVAL(request_method);

    //request_method = SG(request_info).request_method;

    //if (SG(request_info).request_method == NULL) {
    //    RETURN_FALSE;
    //}

    /**
     * Not sure if they want "strlen() + 1" for the length or just vanilla
     * "strlen()", none of the variadic macros like this e.g. Z_STRINGL,
     * Z_STRINGL_P, Z_STRINGL_PP. Maybe I should just use "RETURN_STRING" instead even
     * though it's listed as slower...
     */
    //size_t len = strlen(SG(request_info).request_method);
    //RETURN_STRINGL(SG(request_info).request_method, len, 1);
    
     /**
      * -------
      * WORKING
      * -------
      * RETURN_STRING(SG(request_info).query_string, 1);
      * RETURN_STRING(SG(request_info).request_method, 1);
      */
      //RETURN_STRING(request_method, 1);
    //RETURN_STRING(SG(request_info).request_method, 1);
    RETURN_STRING(request_method, 1);

}
