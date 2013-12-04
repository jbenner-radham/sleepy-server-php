// include PHP API
#include <SAPI.h>
#include <php.h>

#include "php_sleepy.h"
 
// define the function(s) we want to add
zend_function_entry sleepy_functions[] = {
  PHP_FE(sleepy, NULL)
  { NULL, NULL, NULL }
};
 
// "sleepy_functions" refers to the struct defined above
// we'll be filling in more of this later: you can use this to specify
// globals, php.ini info, startup and teardown functions, etc.
zend_module_entry sleepy_module_entry = {
  STANDARD_MODULE_HEADER,
  PHP_SLEEPY_EXTNAME,
  sleepy_functions,
  NULL,
  NULL,
  NULL,
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

    php_printf("%s\n", SG(request_info).request_method);
}
