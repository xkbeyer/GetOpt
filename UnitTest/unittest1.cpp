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
            string sHome;
            string logdir;
            bool bVerbose = false;
            bool bDaemon = false;
            bool bJustKill = false;
            char* argv[] = { "prg.exe", "-H/dev/home", "-v", "-d" };

            Assert::AreEqual( 4, (int)_countof( argv ), L"countof failed" );
            string err;

            GetOpt getopt( _countof( argv ), argv, "H:l:vdkh" );
            while ( ( opt = getopt() ) != EOF )
            {
                switch ( opt )
                {
                    case 'H':
                        sHome = getopt.get();
                        break;
                    case 'l':
                        logdir = getopt.get();
                        break;
                    case 'v':
                        bVerbose = true;
                        break;
                    case 'd':
                        bDaemon = true;
                        break;
                    case 'k':
                        bJustKill = true;
                        break;
                    case '?':
                    case ':':
                        err = getopt.error();
                    case 'h':
                    default:
                        break;
                }
            }
            Assert::IsTrue( bVerbose, L"verbose is not set" );
            Assert::IsTrue( bDaemon, L"daemon is set" );
            Assert::IsFalse( bJustKill, L"justkill is set" );
            Assert::AreEqual( string( "/dev/home" ), sHome, L"home differs" );
            Assert::IsTrue( logdir.empty(), L"logdir differs" );
            Assert::IsTrue( err.empty(), L"err differs" );
        }

        TEST_METHOD( TestOptArg )
        {
            char opt;
            string sHome;
            string logdir;
            bool bVerbose = false;
            bool bDaemon = false;
            bool bJustKill = false;
            char* argv[] = { "prg.exe", "-H", "/dev/home", "-v", "-d" };

            string err;

            GetOpt getopt( _countof( argv ), argv, "H:l:vdkh" );
            while ( ( opt = getopt() ) != EOF )
            {
                switch ( opt )
                {
                    case 'H':
                        sHome = getopt.get();
                        break;
                    case 'l':
                        logdir = getopt.get();
                        break;
                    case 'v':
                        bVerbose = true;
                        break;
                    case 'd':
                        bDaemon = true;
                        break;
                    case 'k':
                        bJustKill = true;
                        break;
                    case '?':
                    case ':':
                        err = getopt.error();
                    case 'h':
                    default:
                        break;
                }
            }
            Assert::IsTrue( bVerbose, L"verbose is not set" );
            Assert::IsTrue( bDaemon, L"daemon is set" );
            Assert::IsFalse( bJustKill, L"justkill is set" );
            Assert::AreEqual( string( "/dev/home" ), sHome, L"home differs" );
            Assert::IsTrue( logdir.empty(), L"logdir differs" );
            Assert::IsTrue( err.empty(), L"err differs" );
        }

        TEST_METHOD( TestOpt2Args )
        {
            char opt;
            string sHome;
            string logdir;
            bool bVerbose = false;
            bool bDaemon = false;
            bool bJustKill = false;
            char* argv[] = { "prg.exe", "-H", "/dev/home", "-l/dev/log", "-d" };

            string err;

            GetOpt getopt( _countof( argv ), argv, "H:l:vdkh" );
            while ( ( opt = getopt() ) != EOF )
            {
                switch ( opt )
                {
                    case 'H':
                        sHome = getopt.get();
                        break;
                    case 'l':
                        logdir = getopt.get();
                        break;
                    case 'v':
                        bVerbose = true;
                        break;
                    case 'd':
                        bDaemon = true;
                        break;
                    case 'k':
                        bJustKill = true;
                        break;
                    case '?':
                    case ':':
                        err = getopt.error();
                    case 'h':
                    default:
                        break;
                }
            }
            Assert::IsFalse( bVerbose, L"verbose is not set" );
            Assert::IsTrue( bDaemon, L"daemon is set" );
            Assert::IsFalse( bJustKill, L"justkill is set" );
            Assert::AreEqual( string( "/dev/home" ), sHome, L"home differs" );
            Assert::AreEqual( string( "/dev/log" ), logdir, L"log differs" );
            Assert::IsTrue( err.empty(), L"err differs" );
        }

        TEST_METHOD( TestOptMissingArg )
        {
            char opt;
            string sHome;
            string logdir;
            bool bVerbose = false;
            bool bDaemon = false;
            bool bJustKill = false;
            char* argv[] = { "prg.exe", "-d", "-l" };

            string err;

            GetOpt getopt( _countof( argv ), argv, "H:l:vdkh" );
            while ( ( opt = getopt() ) != EOF )
            {
                switch ( opt )
                {
                    case 'H':
                        sHome = getopt.get();
                        break;
                    case 'l':
                        logdir = getopt.get();
                        break;
                    case 'v':
                        bVerbose = true;
                        break;
                    case 'd':
                        bDaemon = true;
                        break;
                    case 'k':
                        bJustKill = true;
                        break;
                    case '?':
                    case ':':
                        err = getopt.error();
                    case 'h':
                    default:
                        break;
                }
            }
            Assert::IsFalse( bVerbose, L"verbose is not set" );
            Assert::IsTrue( bDaemon, L"daemon is set" );
            Assert::IsFalse( bJustKill, L"justkill is set" );
            Assert::AreEqual( string( "prg.exe: option requires argument -l\n" ), err, L"error msg differs" );
            Assert::IsTrue( logdir.empty(), L"logdir differs" );
            Assert::IsTrue( sHome.empty(), L"sHome differs" );
        }

        TEST_METHOD( TestOptUnknownArg )
        {
            char opt;
            string sHome;
            string logdir;
            bool bVerbose = false;
            bool bDaemon = false;
            bool bJustKill = false;
            char* argv[] = { "prg.exe", "-d", "-u" };

            string err;

            GetOpt getopt( _countof( argv ), argv, "H:l:vdkh" );
            while ( ( opt = getopt() ) != EOF )
            {
                switch ( opt )
                {
                    case 'H':
                        sHome = getopt.get();
                        break;
                    case 'l':
                        logdir = getopt.get();
                        break;
                    case 'v':
                        bVerbose = true;
                        break;
                    case 'd':
                        bDaemon = true;
                        break;
                    case 'k':
                        bJustKill = true;
                        break;
                    case '?':
                    case ':':
                        err = getopt.error();
                    case 'h':
                    default:
                        break;
                }
            }
            Assert::IsFalse( bVerbose, L"verbose is not set" );
            Assert::IsTrue( bDaemon, L"daemon is set" );
            Assert::IsFalse( bJustKill, L"justkill is set" );
            Assert::AreEqual( string( "prg.exe: unknown option -u\n" ), err, L"error msg differs" );
            Assert::IsTrue( logdir.empty(), L"logdir differs" );
            Assert::IsTrue( sHome.empty(), L"sHome differs" );
        }

        TEST_METHOD( TestOptMissingArgInBetween )
        {
            char opt;
            string sHome;
            string logdir;
            bool bVerbose = false;
            bool bDaemon = false;
            bool bJustKill = false;
            char* argv[] = { "prg.exe", "-d", "-l", "-k" };

            string err;

            GetOpt getopt( _countof( argv ), argv, "H:l:vdkh" );
            while ( ( opt = getopt() ) != EOF )
            {
                switch ( opt )
                {
                    case 'H':
                        sHome = getopt.get();
                        break;
                    case 'l':
                        logdir = getopt.get();
                        break;
                    case 'v':
                        bVerbose = true;
                        break;
                    case 'd':
                        bDaemon = true;
                        break;
                    case 'k':
                        bJustKill = true;
                        break;
                    case '?':
                    case ':':
                        err = getopt.error();
                    case 'h':
                    default:
                        break;
                }
            }
            Assert::IsFalse( bVerbose, L"verbose is not set" );
            Assert::IsTrue( bDaemon, L"daemon is set" );
            Assert::IsTrue( bJustKill, L"justkill is set" );
            Assert::AreEqual( string( "prg.exe: option requires argument -l\n" ), err, L"error msg differs" );
            Assert::IsTrue( logdir.empty(), L"logdir differs" );
            Assert::IsTrue( sHome.empty(), L"sHome differs" );
        }

        TEST_METHOD( TestOptStartWithArgFail )
        {
            char opt;
            string sHome;
            string logdir;
            bool bVerbose = false;
            bool bDaemon = false;
            bool bJustKill = false;
            char* argv[] = { "prg.exe", "test", "-l/dev/home", "-k" };

            string err;

            GetOpt getopt( _countof( argv ), argv, "H:l:vdkh" );
            while ( ( opt = getopt() ) != EOF )
            {
                switch ( opt )
                {
                    case 'H':
                        sHome = getopt.get();
                        break;
                    case 'l':
                        logdir = getopt.get();
                        break;
                    case 'v':
                        bVerbose = true;
                        break;
                    case 'd':
                        bDaemon = true;
                        break;
                    case 'k':
                        bJustKill = true;
                        break;
                    case '?':
                    case ':':
                        err = getopt.error();
                    case 'h':
                    default:
                        break;
                }
            }
            Assert::IsFalse( bVerbose, L"verbose is set" );
            Assert::IsFalse( bDaemon, L"daemon is set" );
            Assert::IsFalse( bJustKill, L"justkill is set" );
            Assert::AreEqual( string( "" ), logdir, L"logdir differs" );
            Assert::AreEqual( string( "" ), err, L"error msg differs" );
            Assert::IsTrue( sHome.empty(), L"sHome differs" );
        }

        TEST_METHOD( TestOptStringStartWithColon )
        {
            char opt, erroropt = 0 ;
            string sHome;
            string logdir;
            bool bVerbose = false;
            bool bDaemon = false;
            bool bJustKill = false;
            char* argv[] = { "prg.exe", "-l/dev/home", "-k" };

            string err;

            GetOpt getopt( _countof( argv ), argv, ":H:l:vdkh" );
            while ( ( opt = getopt() ) != EOF )
            {
                switch ( opt )
                {
                    case 'H':
                        sHome = getopt.get();
                        break;
                    case 'l':
                        logdir = getopt.get();
                        break;
                    case 'v':
                        bVerbose = true;
                        break;
                    case 'd':
                        bDaemon = true;
                        break;
                    case 'k':
                        bJustKill = true;
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
            Assert::IsFalse( bVerbose, L"verbose is set" );
            Assert::IsFalse( bDaemon, L"daemon is set" );
            Assert::IsTrue( bJustKill, L"justkill is set" );
            Assert::AreEqual( string( "/dev/home" ), logdir, L"logdir differs" );
            Assert::AreEqual( string( "prg.exe: missing option argument in :H:l:vdkh\n" ), err, L"error msg differs" );
            Assert::AreEqual( ':', erroropt, L"opt is not :" );
            Assert::IsTrue( sHome.empty(), L"sHome differs" );
        }

        TEST_METHOD( TestOptWithNonOptionArg )
        {
            char opt, erroropt = 0;
            string sHome;
            string logdir;
            bool bVerbose = false;
            bool bDaemon = false;
            bool bJustKill = false;
            char* argv[] = { "prg.exe", "-l/dev/home", ":k" };

            string err;

            GetOpt getopt( _countof( argv ), argv, "H:l:vdkh" );
            while ( ( opt = getopt() ) != EOF )
            {
                switch ( opt )
                {
                    case 'H':
                        sHome = getopt.get();
                        break;
                    case 'l':
                        logdir = getopt.get();
                        break;
                    case 'v':
                        bVerbose = true;
                        break;
                    case 'd':
                        bDaemon = true;
                        break;
                    case 'k':
                        bJustKill = true;
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
            Assert::IsFalse( bVerbose, L"verbose is set" );
            Assert::IsFalse( bDaemon, L"daemon is set" );
            Assert::IsFalse( bJustKill, L"justkill is set" );
            Assert::AreEqual( string( "/dev/home" ), logdir, L"logdir differs" );
            Assert::IsTrue( err.empty() , L"error msg differs" );
            Assert::IsTrue( sHome.empty(), L"sHome differs" );
            Assert::AreEqual( ':', argv[getopt.getIndex()][0], L"First non option argument differs" );
        }

        TEST_METHOD( TestWithStopOptionArg )
        {
            char opt, erroropt = 0;
            string sHome;
            string logdir;
            bool bVerbose = false;
            bool bDaemon = false;
            bool bJustKill = false;
            char* argv[] = { "prg.exe", "-l/dev/home", "--", "noarg" };

            string err;

            GetOpt getopt( _countof(argv), argv, "H:l:vdkh" );
            while ( ( opt = getopt() ) != EOF )
            {
                switch ( opt )
                {
                    case 'H':
                        sHome = getopt.get();
                        break;
                    case 'l':
                        logdir = getopt.get();
                        break;
                    case 'v':
                        bVerbose = true;
                        break;
                    case 'd':
                        bDaemon = true;
                        break;
                    case 'k':
                        bJustKill = true;
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
            Assert::IsFalse( bVerbose, L"verbose is set" );
            Assert::IsFalse( bDaemon, L"daemon is set" );
            Assert::IsFalse( bJustKill, L"justkill is set" );
            Assert::AreEqual( string( "/dev/home" ), logdir, L"logdir differs" );
            Assert::IsTrue( err.empty(), L"error msg differs" );
            Assert::IsTrue( sHome.empty(), L"sHome differs" );
            Assert::AreEqual( std::string( "noarg" ), std::string( argv[getopt.getIndex()] ), L"First non option argument differs" );
        }

        TEST_METHOD( TestEmptyOptString )
        {
            char opt, erroropt = '_';
            int error_count = 0;
            string sHome;
            string logdir;
            bool bVerbose = false;
            bool bDaemon = false;
            bool bJustKill = false;
            char* argv[] = { "prg.exe", "-l/dev/home", "-k" };

            string err;

            GetOpt getopt( _countof(argv), argv, "" );
            while ( ( opt = getopt() ) != EOF )
            {
                switch ( opt )
                {
                    case 'H':
                        sHome = getopt.get();
                        break;
                    case 'l':
                        logdir = getopt.get();
                        break;
                    case 'v':
                        bVerbose = true;
                        break;
                    case 'd':
                        bDaemon = true;
                        break;
                    case 'k':
                        bJustKill = true;
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
            Assert::IsFalse( bVerbose, L"verbose is set" );
            Assert::IsFalse( bDaemon, L"daemon is set" );
            Assert::IsFalse( bJustKill, L"justkill is set" );
            Assert::AreEqual( string( "" ), logdir, L"logdir differs" );
            Assert::AreEqual( string( "prg.exe: unknown option -k\n" ), err, L"last error msg differs" );
            Assert::AreEqual( '?', erroropt, L"opt is not _" );
            Assert::AreEqual( 2, error_count, L"error_count differs" );
            Assert::IsTrue( sHome.empty(), L"sHome differs" );
        }
        
        TEST_METHOD( TestEmptyOption )
        {
            char opt, erroropt = '_';
            int error_count = 0;
            string sHome;
            string logdir;
            bool bVerbose = false;
            bool bDaemon = false;
            bool bJustKill = false;
            char* argv[] = { "prg.exe", "-", "l", "-k" };

            string err;

            GetOpt getopt( _countof( argv ), argv, "H:l:vdkh" );
            while ( ( opt = getopt() ) != EOF )
            {
                switch ( opt )
                {
                    case 'H':
                        sHome = getopt.get();
                        break;
                    case 'l':
                        logdir = getopt.get();
                        break;
                    case 'v':
                        bVerbose = true;
                        break;
                    case 'd':
                        bDaemon = true;
                        break;
                    case 'k':
                        bJustKill = true;
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
            Assert::IsFalse( bVerbose, L"verbose is set" );
            Assert::IsFalse( bDaemon, L"daemon is set" );
            Assert::IsFalse( bJustKill, L"justkill is set" );
            Assert::AreEqual( string( "" ), logdir, L"logdir differs" );
            Assert::AreEqual( string( "" ), sHome, L"sHome differs" );
            Assert::AreEqual( string( "" ), err, L"last error msg differs" );
            Assert::AreEqual( '_', erroropt, L"opt is not _" );
            Assert::AreEqual( 0, error_count, L"error_count differs" );
        }

        TEST_METHOD( TestColonOption )
        {
            char opt, erroropt = '_';
            int error_count = 0;
            string sHome;
            string logdir;
            bool bVerbose = false;
            bool bDaemon = false;
            bool bJustKill = false;
            char* argv[] = { "prg.exe", "-:", "l", "-k" };

            string err;

            GetOpt getopt( _countof( argv ), argv, "H:l:vdkh" );
            while ( ( opt = getopt() ) != EOF )
            {
                switch ( opt )
                {
                    case 'H':
                        sHome = getopt.get();
                        break;
                    case 'l':
                        logdir = getopt.get();
                        break;
                    case 'v':
                        bVerbose = true;
                        break;
                    case 'd':
                        bDaemon = true;
                        break;
                    case 'k':
                        bJustKill = true;
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
            Assert::IsFalse( bVerbose, L"verbose is set" );
            Assert::IsFalse( bDaemon, L"daemon is set" );
            Assert::IsFalse( bJustKill, L"justkill is set" );
            Assert::AreEqual( string( "" ), logdir, L"logdir differs" );
            Assert::AreEqual( string( "" ), sHome, L"sHome differs" );
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
            string sHome;
            string logdir;
            bool bVerbose = false;
            bool bDaemon = false;
            bool bJustKill = false;
            char* argv[] = { "prg.exe", "-H/dev/home", "-v", "-d" };


            GetOpt getopt( _countof( argv ), argv, "H:l:vdkh" );
            while ( ( opt = getopt() ) != EOF )
            {
                switch ( opt )
                {
                    case 'H':
                        sHome = getopt.get();
                        break;
                    case 'l':
                        logdir = getopt.get();
                        break;
                    case 'v':
                        bVerbose = true;
                        break;
                    case 'd':
                        bDaemon = true;
                        break;
                    case 'k':
                        bJustKill = true;
                        break;
                    case '?':
                    case ':':
                        err = getopt.error();
                    case 'h':
                    default:
                        break;
                }
            }
            Assert::IsTrue( bVerbose, L"verbose is not set" );
            Assert::IsTrue( bDaemon, L"daemon is set" );
            Assert::IsFalse( bJustKill, L"justkill is set" );
            Assert::AreEqual( string( "/dev/home" ), sHome, L"home differs" );
            Assert::IsTrue( logdir.empty(), L"logdir differs" );
            Assert::IsTrue( err.empty(), L"err differs" );

            err.clear();
            sHome.clear();
            logdir.clear();
            bVerbose = false;
            bDaemon = false;
            bJustKill = false;

            getopt.reset();
            while ( ( opt = getopt() ) != EOF )
            {
                switch ( opt )
                {
                    case 'H':
                        sHome = getopt.get();
                        break;
                    case 'l':
                        logdir = getopt.get();
                        break;
                    case 'v':
                        bVerbose = true;
                        break;
                    case 'd':
                        bDaemon = true;
                        break;
                    case 'k':
                        bJustKill = true;
                        break;
                    case '?':
                    case ':':
                        err = getopt.error();
                    case 'h':
                    default:
                        break;
                }
            }
            Assert::IsTrue( bVerbose, L"verbose is not set" );
            Assert::IsTrue( bDaemon, L"daemon is set" );
            Assert::IsFalse( bJustKill, L"justkill is set" );
            Assert::AreEqual( string( "/dev/home" ), sHome, L"home differs" );
            Assert::IsTrue( logdir.empty(), L"logdir differs" );
            Assert::IsTrue( err.empty(), L"err differs" );

        }

    };

}