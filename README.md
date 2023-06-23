# testmem64
Tiny memory testing utility, that writes selected pattern to allocateed memory and then verifies it.

Build:
-
~~~
make
~~~
Run:
-
~~~
make run
~~~
or
~~~
./build/testmem64
~~~
Command line arguments:
-
- -m - specifies amount of testing pages (default - 64 pages)
- -s - enables stress mode (infinite read-write loop until CTRL+C pressed)
- -p - sets the size of testing page (default - 1 MByte)
- -c - sets record pattern (default - 'Z')
- -i - sets amount of testing iterations (default - 1)
- -v - be more verbose
- -h - print help
