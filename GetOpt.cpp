/* GetOpt - getopt as a c++ class.
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Klaus Beyer
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <stdio.h>  // EOF const

#include "GetOpt.h"


GetOpt::GetOpt( int argc, char* argv[], const std::string optstring ) 
    : index( 1 )
    , argCount( argc )
    , argStrings( argv )
    , optionString( optstring )
{
}
char GetOpt::operator()()
{
    optionArgument.clear();
    errorText.clear();

    // Is first character of option string a ':'
    if ( optionString[0] == ':' )
    {
        errorText = argStrings[0] + std::string( ": missing option argument in " ) + optionString + "\n";
        optionString.erase( 0, 1 );
        return ':';
    }

    // Is end of argument list? or not an option or empty option 
    if ( index >= argCount )
        return EOF;

    // Is end of argument list reached? or empty option 
    if ( argStrings[index][0] != '-' || argStrings[index][1] == '\0' )
        return EOF;

    // Is end of argument list reached? 
    if ( argStrings[index][0] == '-' && argStrings[index][1] == '-' )
    {
        index++;
        return EOF;
    }

    // Skip '-'
    auto scan = argStrings[index] + 1;
    index++;

    // Is current character in the option string 
    char c = *scan++;
    auto place = optionString.find_first_of( c );
    if ( place == std::string::npos || c == ':' )
    {
        errorText = argStrings[0] + std::string( ": unknown option -" ) + c + "\n";
        return '?';
    }

    // Check if an additional argument is needed.
    place++;
    if ( optionString[place] == ':' )
    {
        place++;
        bool argIsOptional = optionString[place] == ':';
        // Check if no space is between option and its argument.
        if ( *scan != '\0' )
        {
            optionArgument = scan;
        }
        else if ( index < argCount )
        {
            if ( argStrings[index][0] != '-' )
            {
                optionArgument = argStrings[index];
                index++;
            }
            else if ( !argIsOptional )
            {
                errorText = argStrings[0] + std::string( ": option requires argument -" ) + c + "\n";
                return ':';
            }
        }
        else if( !argIsOptional )
        {
            errorText = argStrings[0] + std::string( ": option requires argument -" ) + c + "\n";
            return ':';
        }
    }
    return c;
}


char GetOpt::iterator::operator*( )
{
   auto ret = getopt->operator()();
   if ( ret == EOF )
   {
      position = getopt->argCount - 1; // Set iterator to the end
   }
   else
   {
      position = getopt->index - 1; // In case index has advanced more than one position.
   }

   return ret;
}
