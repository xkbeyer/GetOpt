//main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>

#include "GetOpt.h"

using namespace std;

int main(int argc, _TCHAR* argv[])
{
    char opt = -1;
    string aPath;
    string aLogFileName;
    int levelVerbose  = 0;
    bool bDaemon   = false;
    bool bJustKill = false;
    GetOpt getopt( argc, argv, "H:l:v::dkh" );
    while ( ( opt = getopt() ) != EOF )
    {
        switch ( opt )
        {
            case 'H':
                aPath = getopt.get() ;
                break;
            case 'l':
                aLogFileName = getopt.get() ;
                break;
            case 'v':
                if ( !getopt.get().empty() )
                {
                    levelVerbose = std::stoi( getopt.get() ) ;
                }
                else
                {
                    levelVerbose = 1;
                }
                break;
            case 'd':
                bDaemon = true;
                break;
            case 'k':
                bJustKill = true;
                break;
            case '?':
            case ':':
                std::cout << getopt.error();
            case 'h':
            default:
                cout << "usage: " << argv[0] << "[-p path][-l logfile][-v level][-h][-k][-d]\n";
                cout << "      -H HOMEDIR assume the home directory to be HOMEDIR.\n";
                cout << "      -l logfile sets the directory to write logfiles\n";
                cout << "      -v         activates verbose level. Level is optional.\n";
                cout << "      -d         start as a daemon\n";
                cout << "      -k         shut down / kill\n";
                cout << "      -h         shows this help message\n";
                break;
        }
    }

    return 0;
}

