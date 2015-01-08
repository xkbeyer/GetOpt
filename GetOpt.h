
#include <string>
// TODO implement iterator interface in order to use it w/ a range for loop.
// TODO make an git repo.
class GetOpt
{
public:

    GetOpt( int argc, char* argv[], const std::string optstring );
    std::string get() { return optionArgument; }
    std::string error() { return errorText; }
    int getIndex() { return index; }
    void reset() { index = 1; };
    char operator()();

private:
    std::string optionArgument; /* Global argument pointer. */
    int index; /* Global argv index. */
    int argCount;
    char** argStrings;
    std::string optionString;
    std::string errorText;
};
