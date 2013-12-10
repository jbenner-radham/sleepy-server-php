#define PHP_SLEEPY_EXTNAME "sleepy"
//#define PHP_SLEEPY_VERSION "0.0.1"
// http://www.php.net/manual/en/internals2.structure.modstruct.php#internals2.structure.modstruct.filling-it-in.counter-mod-ex
#define PHP_SLEEPY_VERSION NO_VERSION_YET

//extern zend_module_entry sleepy_module_entry;

PHP_MINIT_FUNCTION(sleepy);
PHP_RINIT_FUNCTION(sleepy);

//PHP_MSHUTDOWN_FUNCTION(sleepy);

<<<<<<< HEAD
PHP_METHOD(Sleepy, test);
=======
//PHP_FUNCTION(sleepy);
PHP_METHOD(Sleepy, test);
>>>>>>> 8b9608e317b405f588a06244f3ae802fbf9a52bd
