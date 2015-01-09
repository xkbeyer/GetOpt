#include "stdafx.h"
#include "CppUnitTest.h"

#include "../GetOpt.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTest
{
    TEST_CLASS( UnitTestGetOpt )
    {
    public:

        TEST_METHOD( TestOpt )
        {
            char opt;
            string homePath;
            string logdir;
            bool verbose = false;
            bool daemon = false;
            bool kill = false;
            char* argv[] = { "prg.exe", "-H/user/home", "-v", "-d" };

            string err;

            GetOpt getopt( _countof( argv ), argv, "H:l:vdkh" );
            while ( ( opt = getopt() ) != EOF )
            {
                switch ( opt )
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
                    case '?':
                    case ':':
                        err = getopt.error();
                    case 'h':
                    default:
                        break;
                }
            }
            Assert::IsTrue( verbose, L"verbose is not set" );
            Assert::IsTrue( daemon, L"daemon is set" );
            Assert::IsFalse( kill, L"kill is set" );
            Assert::AreEqual( string( "/user/home" ), homePath, L"home differs" );
            Assert::IsTrue( logdir.empty(), L"logdir differs" );
            Assert::IsTrue( err.empty(), L"err differs" );
        }

        TEST_METHOD( TestOptArg )
        {
            char opt;
            string homePath;
            string logdir;
            bool verbose = false;
            bool daemon = false;
            bool kill = false;
            char* argv[] = { "prg.exe", "-H", "/user/home", "-v", "-d" };

            string err;

            GetOpt getopt( _countof( argv ), argv, "H:l:vdkh" );
            while ( ( opt = getopt() ) != EOF )
            {
                switch ( opt )
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
                    case '?':
                    case ':':
                        err = getopt.error();
                    case 'h':
                    default:
                        break;
                }
            }
            Assert::IsTrue( verbose, L"verbose is not set" );
            Assert::IsTrue( daemon, L"daemon is set" );
            Assert::IsFalse( kill, L"kill is set" );
            Assert::AreEqual( string( "/user/home" ), homePath, L"home differs" );
            Assert::IsTrue( logdir.empty(), L"logdir differs" );
            Assert::IsTrue( err.empty(), L"err differs" );
        }

        TEST_METHOD( TestOpt2Args )
        {
            char opt;
            string homePath;
            string logdir;
            bool verbose = false;
            bool daemon = false;
            bool kill = false;
            char* argv[] = { "prg.exe", "-H", "/user/home", "-l/user/log", "-d" };

            string err;

            GetOpt getopt( _countof( argv ), argv, "H:l:vdkh" );
            while ( ( opt = getopt() ) != EOF )
            {
                switch ( opt )
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
                    case '?':
                    case ':':
                        err = getopt.error();
                    case 'h':
                    default:
                        break;
                }
            }
            Assert::IsFalse( verbose, L"verbose is not set" );
            Assert::IsTrue( daemon, L"daemon is set" );
            Assert::IsFalse( kill, L"kill is set" );
            Assert::AreEqual( string( "/user/home" ), homePath, L"home differs" );
            Assert::AreEqual( string( "/user/log" ), logdir, L"log differs" );
            Assert::IsTrue( err.empty(), L"err differs" );
        }

        TEST_METHOD( TestOptMissingArg )
        {
            char opt;
            string homePath;
            string logdir;
            bool verbose = false;
            bool daemon = false;
            bool kill = false;
            char* argv[] = { "prg.exe", "-d", "-l" };

            string err;

            GetOpt getopt( _countof( argv ), argv, "H:l:vdkh" );
            while ( ( opt = getopt() ) != EOF )
            {
                switch ( opt )
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
                    case '?':
                    case ':':
                        err = getopt.error();
                    case 'h':
                    default:
                        break;
                }
            }
            Assert::IsFalse( verbose, L"verbose is not set" );
            Assert::IsTrue( daemon, L"daemon is set" );
            Assert::IsFalse( kill, L"kill is set" );
            Assert::AreEqual( string( "prg.exe: option requires argument -l\n" ), err, L"error msg differs" );
            Assert::IsTrue( logdir.empty(), L"logdir differs" );
            Assert::IsTrue( homePath.empty(), L"homePath differs" );
        }

        TEST_METHOD( TestOptUnknownArg )
        {
            char opt;
            string homePath;
            string logdir;
            bool verbose = false;
            bool daemon = false;
            bool kill = false;
            char* argv[] = { "prg.exe", "-d", "-u" };

            string err;

            GetOpt getopt( _countof( argv ), argv, "H:l:vdkh" );
            while ( ( opt = getopt() ) != EOF )
            {
                switch ( opt )
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
                    case '?':
                    case ':':
                        err = getopt.error();
                    case 'h':
                    default:
                        break;
                }
            }
            Assert::IsFalse( verbose, L"verbose is not set" );
            Assert::IsTrue( daemon, L"daemon is set" );
            Assert::IsFalse( kill, L"kill is set" );
            Assert::AreEqual( string( "prg.exe: unknown option -u\n" ), err, L"error msg differs" );
            Assert::IsTrue( logdir.empty(), L"logdir differs" );
            Assert::IsTrue( homePath.empty(), L"homePath differs" );
        }

        TEST_METHOD( TestOptMissingArgInBetween )
        {
            char opt;
            string homePath;
            string logdir;
            bool verbose = false;
            bool daemon = false;
            bool kill = false;
            char* argv[] = { "prg.exe", "-d", "-l", "-k" };

            string err;

            GetOpt getopt( _countof( argv ), argv, "H:l:vdkh" );
            while ( ( opt = getopt() ) != EOF )
            {
                switch ( opt )
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
                    case '?':
                    case ':':
                        err = getopt.error();
                    case 'h':
                    default:
                        break;
                }
            }
            Assert::IsFalse( verbose, L"verbose is not set" );
            Assert::IsTrue( daemon, L"daemon is set" );
            Assert::IsTrue( kill, L"kill is set" );
            Assert::AreEqual( string( "prg.exe: option requires argument -l\n" ), err, L"error msg differs" );
            Assert::IsTrue( logdir.empty(), L"logdir differs" );
            Assert::IsTrue( homePath.empty(), L"homePath differs" );
        }

        TEST_METHOD( TestOptStartWithArgFail )
        {
            char opt;
            string homePath;
            string logdir;
            bool verbose = false;
            bool daemon = false;
            bool kill = false;
            char* argv[] = { "prg.exe", "test", "-l/user/home", "-k" };

            string err;

            GetOpt getopt( _countof( argv ), argv, "H:l:vdkh" );
            while ( ( opt = getopt() ) != EOF )
            {
                switch ( opt )
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
                    case '?':
                    case ':':
                        err = getopt.error();
                    case 'h':
                    default:
                        break;
                }
            }
            Assert::IsFalse( verbose, L"verbose is set" );
            Assert::IsFalse( daemon, L"daemon is set" );
            Assert::IsFalse( kill, L"kill is set" );
            Assert::AreEqual( string( "" ), logdir, L"logdir differs" );
            Assert::AreEqual( string( "" ), err, L"error msg differs" );
            Assert::IsTrue( homePath.empty(), L"homePath differs" );
        }

        TEST_METHOD( TestOptStringStartWithColon )
        {
            char opt, erroropt = 0 ;
            string homePath;
            string logdir;
            bool verbose = false;
            bool daemon = false;
            bool kill = false;
            char* argv[] = { "prg.exe", "-l/user/home", "-k" };

            string err;

            GetOpt getopt( _countof( argv ), argv, ":H:l:vdkh" );
            while ( ( opt = getopt() ) != EOF )
            {
                switch ( opt )
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
                    case '?':
                    case ':':
                        erroropt = opt;
                        err = getopt.error();
                    case 'h':
                    default:
                        break;
                }
            }
            Assert::IsFalse( verbose, L"verbose is set" );
            Assert::IsFalse( daemon, L"daemon is set" );
            Assert::IsTrue( kill, L"kill is set" );
            Assert::AreEqual( string( "/user/home" ), logdir, L"logdir differs" );
            Assert::AreEqual( string( "prg.exe: missing option argument in :H:l:vdkh\n" ), err, L"error msg differs" );
            Assert::AreEqual( ':', erroropt, L"opt is not :" );
            Assert::IsTrue( homePath.empty(), L"homePath differs" );
        }

        TEST_METHOD( TestOptWithNonOptionArg )
        {
            char opt, erroropt = 0;
            string homePath;
            string logdir;
            bool verbose = false;
            bool daemon = false;
            bool kill = false;
            char* argv[] = { "prg.exe", "-l/user/home", ":k" };

            string err;

            GetOpt getopt( _countof( argv ), argv, "H:l:vdkh" );
            while ( ( opt = getopt() ) != EOF )
            {
                switch ( opt )
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
                    case '?':
                    case ':':
                        erroropt = opt;
                        err = getopt.error();
                    case 'h':
                    default:
                        break;
                }
            }
            Assert::IsFalse( verbose, L"verbose is set" );
            Assert::IsFalse( daemon, L"daemon is set" );
            Assert::IsFalse( kill, L"kill is set" );
            Assert::AreEqual( string( "/user/home" ), logdir, L"logdir differs" );
            Assert::IsTrue( err.empty() , L"error msg differs" );
            Assert::IsTrue( homePath.empty(), L"homePath differs" );
            Assert::AreEqual( ':', argv[getopt.getIndex()][0], L"First non option argument differs" );
        }

        TEST_METHOD( TestWithStopOptionArg )
        {
            char opt, erroropt = 0;
            string homePath;
            string logdir;
            bool verbose = false;
            bool daemon = false;
            bool kill = false;
            char* argv[] = { "prg.exe", "-l/user/home", "--", "noarg" };

            string err;

            GetOpt getopt( _countof(argv), argv, "H:l:vdkh" );
            while ( ( opt = getopt() ) != EOF )
            {
                switch ( opt )
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
                    case '?':
                    case ':':
                        erroropt = opt;
                        err = getopt.error();
                    case 'h':
                    default:
                        break;
                }
            }
            Assert::IsFalse( verbose, L"verbose is set" );
            Assert::IsFalse( daemon, L"daemon is set" );
            Assert::IsFalse( kill, L"kill is set" );
            Assert::AreEqual( string( "/user/home" ), logdir, L"logdir differs" );
            Assert::IsTrue( err.empty(), L"error msg differs" );
            Assert::IsTrue( homePath.empty(), L"homePath differs" );
            Assert::AreEqual( std::string( "noarg" ), std::string( argv[getopt.getIndex()] ), L"First non option argument differs" );
        }

        TEST_METHOD( TestEmptyOptString )
        {
            char opt, erroropt = '_';
            int error_count = 0;
            string homePath;
            string logdir;
            bool verbose = false;
            bool daemon = false;
            bool kill = false;
            char* argv[] = { "prg.exe", "-l/user/home", "-k" };

            string err;

            GetOpt getopt( _countof(argv), argv, "" );
            while ( ( opt = getopt() ) != EOF )
            {
                switch ( opt )
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
                    case '?':
                    case ':':
                        error_count++;
                        erroropt = opt;
                        err = getopt.error();
                    case 'h':
                    default:
                        break;
                }
            }
            Assert::IsFalse( verbose, L"verbose is set" );
            Assert::IsFalse( daemon, L"daemon is set" );
            Assert::IsFalse( kill, L"kill is set" );
            Assert::AreEqual( string( "" ), logdir, L"logdir differs" );
            Assert::AreEqual( string( "prg.exe: unknown option -k\n" ), err, L"last error msg differs" );
            Assert::AreEqual( '?', erroropt, L"opt is not _" );
            Assert::AreEqual( 2, error_count, L"error_count differs" );
            Assert::IsTrue( homePath.empty(), L"homePath differs" );
        }
        
        TEST_METHOD( TestEmptyOption )
        {
            char opt, erroropt = '_';
            int error_count = 0;
            string homePath;
            string logdir;
            bool verbose = false;
            bool daemon = false;
            bool kill = false;
            char* argv[] = { "prg.exe", "-", "l", "-k" };

            string err;

            GetOpt getopt( _countof( argv ), argv, "H:l:vdkh" );
            while ( ( opt = getopt() ) != EOF )
            {
                switch ( opt )
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
                    case '?':
                    case ':':
                        error_count++;
                        erroropt = opt;
                        err = getopt.error();
                    case 'h':
                    default:
                        break;
                }
            }
            Assert::IsFalse( verbose, L"verbose is set" );
            Assert::IsFalse( daemon, L"daemon is set" );
            Assert::IsFalse( kill, L"kill is set" );
            Assert::AreEqual( string( "" ), logdir, L"logdir differs" );
            Assert::AreEqual( string( "" ), homePath, L"homePath differs" );
            Assert::AreEqual( string( "" ), err, L"last error msg differs" );
            Assert::AreEqual( '_', erroropt, L"opt is not _" );
            Assert::AreEqual( 0, error_count, L"error_count differs" );
        }

        TEST_METHOD( TestColonOption )
        {
            char opt, erroropt = '_';
            int error_count = 0;
            string homePath;
            string logdir;
            bool verbose = false;
            bool daemon = false;
            bool kill = false;
            char* argv[] = { "prg.exe", "-:", "l", "-k" };

            string err;

            GetOpt getopt( _countof( argv ), argv, "H:l:vdkh" );
            while ( ( opt = getopt() ) != EOF )
            {
                switch ( opt )
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
                    case '?':
                    case ':':
                        error_count++;
                        erroropt = opt;
                        err = getopt.error();
                    case 'h':
                    default:
                        break;
                }
            }
            Assert::IsFalse( verbose, L"verbose is set" );
            Assert::IsFalse( daemon, L"daemon is set" );
            Assert::IsFalse( kill, L"kill is set" );
            Assert::AreEqual( string( "" ), logdir, L"logdir differs" );
            Assert::AreEqual( string( "" ), homePath, L"homePath differs" );
            Assert::AreEqual( string( "prg.exe: unknown option -:\n" ), err, L"last error msg differs" );
            Assert::AreEqual( '?', erroropt, L"opt is not ?" );
            Assert::AreEqual( 1, error_count, L"error_count differs" );
        }

        TEST_METHOD( TestOptionalArgument )
        {
            char opt, erroropt = '_';
            int error_count = 0;
            char* argv[] = { "prg.exe", "-v 7" };

            string err;
            int level = 0;
            GetOpt getopt( _countof(argv), argv, "v::" );
            while ( ( opt = getopt() ) != EOF )
            {
                switch ( opt )
                {
                    case 'v':
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
                        erroropt = opt;
                        err = getopt.error();
                    case 'h':
                    default:
                        break;
                }
            }
            Assert::AreEqual( 7, level, L"level isn't 7" );
            Assert::AreNotEqual( string( "prg.exe: unknown option -:\n" ), err, L"last error msg differs" );
            Assert::AreNotEqual( '?', erroropt, L"opt is not ?" );
            Assert::AreEqual( 0, error_count, L"error_count differs" );
        }

        TEST_METHOD( TestOptionalArgumentNotGiven )
        {
            char opt, erroropt = '_';
            int error_count = 0;
            char* argv[] = { "prg.exe", "-v" };

            string err;
            int level = 0;
            GetOpt getopt( _countof(argv), argv, "v::" );
            while ( ( opt = getopt() ) != EOF )
            {
                switch ( opt )
                {
                    case 'v':
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
                        erroropt = opt;
                        err = getopt.error();
                    case 'h':
                    default:
                        break;
                }
            }
            Assert::AreEqual( 1, level, L"level isn't 1" );
            Assert::AreNotEqual( string( "prg.exe: unknown option -:\n" ), err, L"last error msg differs" );
            Assert::AreNotEqual( '?', erroropt, L"opt is not ?" );
            Assert::AreEqual( 0, error_count, L"error_count differs" );
        }

        TEST_METHOD( TestOptionalArgumentNotGivenAndNotOnly )
        {
            char opt, erroropt = '_';
            int error_count = 0;
            char* argv[] = { "prg.exe", "-v", "-x" };

            string err;
            int level = 0;
            bool xSet = false;
            GetOpt getopt( _countof(argv), argv, "v::x" );
            while ( ( opt = getopt() ) != EOF )
            {
                switch ( opt )
                {
                    case 'v':
                        if ( !getopt.get().empty() )
                        {
                            level = std::stoi( getopt.get() );
                        }
                        else
                        {
                            level = 1;
                        }
                        break;
                    case 'x':
                        xSet = true;
                        break;
                    case '?':
                    case ':':
                        error_count++;
                        erroropt = opt;
                        err = getopt.error();
                    case 'h':
                    default:
                        break;
                }
            }
            Assert::AreEqual( 1, level, L"level isn't 1" );
            Assert::IsTrue( xSet, L"x option is not set" );
            Assert::AreNotEqual( string( "prg.exe: unknown option -:\n" ), err, L"last error msg differs" );
            Assert::AreNotEqual( '?', erroropt, L"opt is not ?" );
            Assert::AreEqual( 0, error_count, L"error_count differs" );
        }

        TEST_METHOD( TestOptReset )
        {
            char opt;
            string err;
            string homePath;
            string logdir;
            bool verbose = false;
            bool daemon = false;
            bool kill = false;
            char* argv[] = { "prg.exe", "-H/user/home", "-v", "-d" };


            GetOpt getopt( _countof( argv ), argv, "H:l:vdkh" );
            while ( ( opt = getopt() ) != EOF )
            {
                switch ( opt )
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
                    case '?':
                    case ':':
                        err = getopt.error();
                    case 'h':
                    default:
                        break;
                }
            }
            Assert::IsTrue( verbose, L"verbose is not set" );
            Assert::IsTrue( daemon, L"daemon is set" );
            Assert::IsFalse( kill, L"kill is set" );
            Assert::AreEqual( string( "/user/home" ), homePath, L"home differs" );
            Assert::IsTrue( logdir.empty(), L"logdir differs" );
            Assert::IsTrue( err.empty(), L"err differs" );

            err.clear();
            homePath.clear();
            logdir.clear();
            verbose = false;
            daemon = false;
            kill = false;

            getopt.reset();
            while ( ( opt = getopt() ) != EOF )
            {
                switch ( opt )
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
                    case '?':
                    case ':':
                        err = getopt.error();
                    case 'h':
                    default:
                        break;
                }
            }
            Assert::IsTrue( verbose, L"verbose is not set" );
            Assert::IsTrue( daemon, L"daemon is set" );
            Assert::IsFalse( kill, L"kill is set" );
            Assert::AreEqual( string( "/user/home" ), homePath, L"home differs" );
            Assert::IsTrue( logdir.empty(), L"logdir differs" );
            Assert::IsTrue( err.empty(), L"err differs" );

        }

    };

}