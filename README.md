GetOpt
======
This is somehow a substitution for the function `getopt()`.
My intention was to have a simple class which I can use in MSVS projects.

Installation
============
Just add the GetOpt.cpp and GetOpt.h to your project.

Usage
=====

## First Version ##
In the `main()` function it can be used as follow: 
```CPP
    GetOpt getopt( argc, argv, "H:l:v::dkh" );
    while ( ( opt = getopt() ) != EOF )
    {
        switch ( opt )
        {
			case 'd':
		...
		}
	}
```

## Second Version ##
However, it can be used with a range-based for loop, like:

```CPP
    GetOpt getopt( argc, argv, "H:l:vdkh" );
    for ( auto opt : getopt )
    {
        switch ( opt )
        {
			case 'd':
		...
		}
    }
```
## Option File ##
Another option is to provide a file with some arguments. May be you have a lot of options and the most
doesn't change, but you want to play with some. In such a case put the stable ones in a file and the other
per command line. The options out of the file are put in front of the ones given by `argv`.
```CPP
    GetOpt getopt( argc, argv, "H:l:vdkh", "myargs.txt" );
	...
```
The file `myargs.txt` might look like this:
```
	-d
	-l /home/user/logs
```
*Hint 1: Currently only one argument per line is supported.*

*Hint 2: Command line oprtions win over the ones from the file.*

## Option String ##
The option string (3nd argument) has the same format and meaning as the [`getopt()`](http://man7.org/linux/man-pages/man3/getopt.3.html) function.
Currently the long option format is not supported.

Examples
========
A lot of examples can be found in the unit test folder.

TODO
====
- Find a way to handle options file if given by argv. 
