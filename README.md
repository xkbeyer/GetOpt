GetOpt
======
This is in some way a substitution for the function `getopt()`.
The intention is to have a simple class usable in MSVS projects.

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
Another option is to provide a file with arguments. May be you have a lot of options and most
do not change, but you want to play with some. In such scenario, put the stable ones in a file and the other via command line. The options that are not in the file are put in front of the ones given by `argv`.
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

*Hint 2: Command line options win over the ones from the file.*
 
## Option String ##
The option string (3nd argument) has the same format and meaning as the [`getopt()`](http://man7.org/linux/man-pages/man3/getopt.3.html) function.
Currently the long option format is not supported.

## Remaining Arguments ##
All arguments not handled by by the option string are stored internally and can be retrieved via the method `getRemainingArguments()`. This works only after looping over the options, otherwise all arguments are returned as they are.
```CPP
	auto noopts = getopt.getRemainingArguments();
	for( auto arg : noopt ) {
	...
	}
```

Examples
========
```CPP
   char opt = 0;
   char* argv[] = { "prg.exe", "-a", "firstfile", "-H", "/user/home", "filename", "-x" };
   string optionH;
   string filename;
   bool optA = false;
   bool optX = false;
   GetOpt getopt(_countof(argv), argv, "axH:");
   for( auto opt : getopt ) {
      switch( opt ) {
         case 'H':
            optionH = getopt.get();
            break;
         case 'a':
            optA = true;
            break;
         case 'x':
            optX = true;
            break;
      }
   }
   std::cout << "Remainig arguments are:\n";
   auto noopts = getopt.getRemainingArguments();
   for( auto arg : noopts ) {
      std::cout << arg << " ";
   }

```
A lot of examples can be found in the unit test folder.

TODO
====
- Find a way to handle a options file name given by argv. 
