sleepy-server-php
=================

A RESTful PHP native C library. It's not really anything at all right now and is an experiment, we'll see how it goes...

Class Constants
---------------

```php
Sleepy::HTTP_ACCEPT;
Sleepy::QUERY_STRING;
Sleepy::REQUEST_METHOD;
Sleepy::REQUEST_URI;
Sleepy::RESPONSE_CODE
```

Class Methods
-------------

### `Sleepy::createJsonResponse([array]);`

Sets the appropriate header and then encodes JSON from the provided array.

### `Sleepy::encodeJson([array]);`

The equivalent of `json_encode([array], JSON_PRETTY_PRINT);`

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

Or if you have a shell environment and are lazy like me...

```
./lazy-build.sh
``` 
