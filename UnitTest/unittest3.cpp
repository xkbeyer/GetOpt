#include "stdafx.h"
#include "CppUnitTest.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "../GetOpt.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTest
{
   using optarray = std::vector < std::string > ;
   TEST_CLASS( UnitTestGetOptFileOptions )
   {
      char erroropt;
      int error_count;
      int level;
      string homePath;
      string logdir;
      string err;
      bool verbose;
      bool daemon;
      bool kill;
      string optFileName = "options.txt";
      void setOptions( char optionChar, GetOpt& getopt )
      {
         switch ( optionChar )
         {
            case 'H':
               homePath = getopt.get();
               break;
            case 'l':
               logdir = getopt.get();
               break;
            case 'v':
               verbose = true;
               break;
            case 'd':
               daemon = true;
               break;
            case 'k':
               kill = true;
               break;
            case 'a':
               if ( !getopt.get().empty() )
               {
                  level = std::stoi( getopt.get() );
               }
               else
               {
                  level = 1;
               }
               break;
            case '?':
            case ':':
               error_count++;
               erroropt = optionChar;
               err = getopt.error();
            case 'h':
            default:
               break;
         }
      }
      void createOptionFile(const optarray& fileoptions )
      {
         std::ofstream file( optFileName );
         for( auto opt : fileoptions ) {
            file << opt << std::endl;
         }
         file.close();
      }
   public:
      TEST_METHOD_INITIALIZE( Setup )
      {
         erroropt = '_';
         error_count = 0;
         level = 0;
         verbose = false;
         daemon = false;
         kill = false;
         homePath.clear();
         logdir.clear();
         err.clear();
         remove( optFileName.c_str() );
      }

      TEST_METHOD( TestEmptyFile )
      {
         char* argv[] = { "prg.exe", "-H/user/home", "-v", "-d" };
         createOptionFile( optarray() );
         GetOpt getopt( _countof( argv ), argv, "H:l:vdkh", optFileName );
         for ( auto opt : getopt )
         {
            setOptions( opt, getopt );
         }
         Assert::IsTrue( verbose, L"verbose is not set" );
         Assert::IsTrue( daemon, L"daemon is set" );
         Assert::IsFalse( kill, L"kill is set" );
         Assert::AreEqual( string( "/user/home" ), homePath, L"home differs" );
         Assert::IsTrue( logdir.empty(), L"logdir differs" );
         Assert::IsTrue( err.empty(), L"err differs" );
      }

      TEST_METHOD( TestMissingFile )
      {
         char* argv[] = { "prg.exe", "-H", "/user/home", "-v", "-d" };
         GetOpt getopt( _countof( argv ), argv, "H:l:vdkh", optFileName );
         for ( auto opt : getopt )
         {
            setOptions( opt, getopt );
         }
         Assert::IsTrue( verbose, L"verbose is not set" );
         Assert::IsTrue( daemon, L"daemon is set" );
         Assert::IsFalse( kill, L"kill is set" );
         Assert::AreEqual( string( "/user/home" ), homePath, L"home differs" );
         Assert::IsTrue( logdir.empty(), L"logdir differs" );
         Assert::IsTrue( err.empty(), L"err differs" );
      }

      TEST_METHOD( TestFileOpt2ndArgOnNewLine )
      {
         char* argv[] = { "prg.exe", "-v" };
         optarray options = { "-H", "/user/home", "-d" };
         createOptionFile( options );

         GetOpt getopt( _countof( argv ), argv, "H:l:vdkh", optFileName );
         for( auto opt : getopt ) {
            setOptions( opt, getopt );
         }
         Assert::IsTrue( verbose, L"verbose is not set" );
         Assert::IsTrue( daemon, L"daemon is set" );
         Assert::IsFalse( kill, L"kill is set" );
         Assert::AreEqual( string( "/user/home" ), homePath, L"home differs" );
         Assert::IsTrue( logdir.empty(), L"logdir differs" );
         Assert::IsTrue( err.empty(), L"err differs" );
      }

      TEST_METHOD( TestFileOpt2Args )
      {
         char* argv[] = { "prg.exe", "-l/user/log" };
         optarray options = { "-H /user/home", "-d" };
         createOptionFile(options);

         GetOpt getopt( _countof( argv ), argv, "H:l:vdkh", optFileName );
         for ( auto opt : getopt )
         {
            setOptions( opt, getopt );
         }
         Assert::IsFalse( verbose, L"verbose is not set" );
         Assert::IsTrue( daemon, L"daemon is set" );
         Assert::IsFalse( kill, L"kill is set" );
         Assert::AreEqual( string( "/user/home" ), homePath, L"home differs" );
         Assert::AreEqual( string( "/user/log" ), logdir, L"log differs" );
         Assert::IsTrue( err.empty(), L"err differs" );
      }

      TEST_METHOD( TestFileOptMissingArg )
      {
         char* argv[] = { "prg.exe" };
         optarray options = { "-l", "-d" };
         createOptionFile( options );

         GetOpt getopt( _countof( argv ), argv, "H:l:vdkh", optFileName );
         for ( auto opt : getopt )
         {
            setOptions( opt, getopt );
         }
         Assert::IsFalse( verbose, L"verbose is not set" );
         Assert::IsTrue( daemon, L"daemon is set" );
         Assert::IsFalse( kill, L"kill is set" );
         Assert::AreEqual( string( "prg.exe: option requires argument -l\n" ), err, L"error msg differs" );
         Assert::IsTrue( logdir.empty(), L"logdir differs" );
         Assert::IsTrue( homePath.empty(), L"homePath differs" );
      }

      TEST_METHOD( TestFileOptUnknownArg )
      {
         char* argv[] = { "prg.exe", "-d" };
         optarray options = { "-u" };
         createOptionFile( options );

         GetOpt getopt( _countof( argv ), argv, "H:l:vdkh", optFileName );
         for ( auto opt : getopt )
         {
            setOptions( opt, getopt );
         }
         Assert::IsFalse( verbose, L"verbose is not set" );
         Assert::IsTrue( daemon, L"daemon is set" );
         Assert::IsFalse( kill, L"kill is set" );
         Assert::AreEqual( string( "prg.exe: unknown option -u\n" ), err, L"error msg differs" );
         Assert::IsTrue( logdir.empty(), L"logdir differs" );
         Assert::IsTrue( homePath.empty(), L"homePath differs" );
      }

      TEST_METHOD( TestFileOptStartWithArgFail )
      {
         char* argv[] = { "prg.exe" };
         optarray options = { "test", "-l/user/home", "-k" };
         createOptionFile( options );

         GetOpt getopt( _countof( argv ), argv, "H:l:vdkh", optFileName );
         for ( auto opt : getopt )
         {
            setOptions( opt, getopt );
         }
         Assert::IsFalse( verbose, L"verbose is set" );
         Assert::IsFalse( daemon, L"daemon is set" );
         Assert::IsFalse( kill, L"kill is set" );
         Assert::AreEqual( string( "" ), logdir, L"logdir differs" );
         Assert::AreEqual( string( "" ), err, L"error msg differs" );
         Assert::IsTrue( homePath.empty(), L"homePath differs" );
      }

      TEST_METHOD( TestFileOptWithNonOptionArg )
      {
         char* argv[] = { "prg.exe" };
         optarray options = { "-l/user/home", ":k" };
         createOptionFile( options );

         GetOpt getopt( _countof( argv ), argv, "H:l:vdkh", optFileName );
         for ( auto opt : getopt )
         {
            setOptions( opt, getopt );
         }
         Assert::IsFalse( verbose, L"verbose is set" );
         Assert::IsFalse( daemon, L"daemon is set" );
         Assert::IsFalse( kill, L"kill is set" );
         Assert::AreEqual( string( "/user/home" ), logdir, L"logdir differs" );
         Assert::IsTrue( err.empty(), L"error msg differs" );
         Assert::IsTrue( homePath.empty(), L"homePath differs" );
         Assert::AreEqual( ':', options[getopt.getIndex()-1][0], L"First non option argument differs" );
      }

      TEST_METHOD( TestFileWithStopOptionArg )
      {
         char* argv[] = { "prg.exe", "--", "noarg" };
         optarray options = { "-l/user/home", "-k" };
         createOptionFile( options );

         GetOpt getopt( _countof( argv ), argv, "H:l:vdkh", optFileName );
         for ( auto opt : getopt )
         {
            setOptions( opt, getopt );
         }
         Assert::IsFalse( verbose, L"verbose is set" );
         Assert::IsFalse( daemon, L"daemon is set" );
         Assert::IsTrue( kill, L"kill is set" );
         Assert::AreEqual( string( "/user/home" ), logdir, L"logdir differs" );
         Assert::IsTrue( err.empty(), L"error msg differs" );
         Assert::IsTrue( homePath.empty(), L"homePath differs" );
         Assert::AreEqual( std::string( "noarg" ), std::string( argv[getopt.getIndex()-2] ), L"First non option argument differs" );
      }

      TEST_METHOD( TestFileWithStopOptionArgInFile )
      {
         char* argv[] = { "prg.exe", "-d", "noarg" };
         optarray options = { "-l/user/home", "-k", "--" };
         createOptionFile( options );

         GetOpt getopt( _countof( argv ), argv, "H:l:vdkh", optFileName );
         for( auto opt : getopt ) {
            setOptions( opt, getopt );
         }
         Assert::IsFalse( verbose, L"verbose is set" );
         Assert::IsFalse( daemon, L"daemon is set" );
         Assert::IsTrue( kill, L"kill is set" );
         Assert::AreEqual( string( "/user/home" ), logdir, L"logdir differs" );
         Assert::IsTrue( err.empty(), L"error msg differs" );
         Assert::IsTrue( homePath.empty(), L"homePath differs" );
         Assert::AreEqual( std::string( "-d" ), std::string( argv[getopt.getIndex()-3] ), L"First non option argument differs" );
      }

      TEST_METHOD( TestFileOptionalArgument )
      {
         char* argv[] = { "prg.exe" };
         optarray options = { "-a 7" };
         createOptionFile( options );

         GetOpt getopt( _countof( argv ), argv, "a::", optFileName );
         for ( auto opt : getopt )
         {
            setOptions( opt, getopt );
         }
         Assert::AreEqual( 7, level, L"level isn't 7" );
         Assert::AreNotEqual( string( "prg.exe: unknown option -:\n" ), err, L"last error msg differs" );
         Assert::AreNotEqual( '?', erroropt, L"opt is not ?" );
         Assert::AreEqual( 0, error_count, L"error_count differs" );
      }

      TEST_METHOD( TestFileOptionalArgumentNotGiven )
      {
         char* argv[] = { "prg.exe", "-k" };
         optarray options = { "-a" };
         createOptionFile( options );

         GetOpt getopt( _countof( argv ), argv, "a::k", optFileName );
         for ( auto opt : getopt )
         {
            setOptions( opt, getopt );
         }
         Assert::IsTrue( kill, L"kill is set" );
         Assert::AreEqual( 1, level, L"level isn't 1" );
         Assert::AreNotEqual( string( "prg.exe: unknown option -:\n" ), err, L"last error msg differs" );
         Assert::AreNotEqual( '?', erroropt, L"opt is not ?" );
         Assert::AreEqual( 0, error_count, L"error_count differs" );
      }



   };

}