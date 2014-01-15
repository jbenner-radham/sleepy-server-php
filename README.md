sleepy-server-php
=================

A RESTful PHP native C library. It's not really anything at all right now and is an experiment, we'll see how it goes...

Class Constants
---------------
```php
Sleepy::REQUEST_METHOD;
Sleepy::REQUEST_URI;
Sleepy::QUERY_STRING;
```

Building
--------
```
phpize
./configure
make
make install
```
And an occasional `make clean` if you're rebuilding a lot.