PHP_METHOD(Sleepy, setJsonHeader)
{
    sleepy_set_header("Content-Type: application/json");

    return;
}
