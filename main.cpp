//main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>

#include "GetOpt.h"

using namespace std;

int main(int argc, char* argv[])
{
    char opt = -1;
    string aPath;
    string aLogFileName;
    int levelVerbose  = 0;
    bool daemon   = false;
    bool kill = false;
    GetOpt getopt( argc, argv, "p:l:v::dkh" );
    while ( ( opt = getopt() ) != EOF )
    {
        switch ( opt )
        {
            case 'p':
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
                daemon = true;
                break;
            case 'k':
                kill = true;
                break;
            case '?':
            case ':':
                std::cout << getopt.error();
            case 'h':
            default:
                cout << "usage: " << argv[0] << "[-p path][-l logfile][-v level][-h][-k][-d]\n";
                cout << "      -p path    assume the home directory to be path.\n";
                cout << "      -l logfile sets the directory to write logfiles\n";
                cout << "      -v         activates verbose level. Level is optional.\n";
                cout << "      -d         start as a daemon\n";
                cout << "      -k         shut down / kill\n";
                cout << "      -h         shows this help message\n";
                break;
        }
    }
    cout << "homepath is set to " << aPath << '\n';
    cout << "Name of the log file is set to " << aLogFileName << '\n';
    cout << "Verbose level is set to " << levelVerbose << '\n';
    cout << "Action daemon is set to " << daemon << '\n';
    cout << "Action kill is set to " << kill << '\n';

    return 0;
}

