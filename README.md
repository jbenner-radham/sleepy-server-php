sleepy-server-php
=================

A RESTful PHP native C library. It's not really anything at all right now and is an experiment, we'll see how it goes...

Class Constants
---------------
```php
Sleepy::QUERY_STRING;
Sleepy::REQUEST_METHOD;
Sleepy::REQUEST_URI;
Sleepy::RESPONSE_CODE
```

Class Methods
-------------
### `Sleepy::setJsonHeader();`

Sets the `Content-Type` header to `application/json`.

### `Sleepy::setStatusCode($status_code);`

Sets the HTTP status code as the provided integer.

Building
--------
```
phpize
./configure
make clean
make
make install
```