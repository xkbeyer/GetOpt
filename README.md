GetOpt
======
This is somehow a substitution for the function `getopt()`.
My intention was to have a simple class which I can use in MSVS projects.

Installation
============
Just add the GetOpt.cpp and GetOpt.h to your project.

Usage
=====
In the `main()` function it can be used as follow: 
```CPP
    GetOpt getopt( argc, argv, "H:l:v::dkh" );
    while ( ( opt = getopt() ) != EOF )
    {
        switch ( opt )
        {
		...
		}
	}
```
	
However, the second option is to use it with a range-based for loop:

```CPP
    GetOpt getopt( argc, argv, "H:l:vdkh" );
    for ( auto opt : getopt )
    {
        switch ( opt )
        {
		...
		}
    }
```

The option string (3nd argument) has the same format and meaning as the [`getopt()`](http://man7.org/linux/man-pages/man3/getopt.3.html) function.
Currently the long option format is not supported.

A lot of examples can be found in the unit test folder.

