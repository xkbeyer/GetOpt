
#include <string>
class GetOpt
{
public:

    GetOpt( int argc, char* argv[], const std::string optstring );
    std::string get() { return optionArgument; }
    std::string error() { return errorText; }
    int getIndex() { return index; }
    void reset() { index = 1; };
    char operator()();

    class iterator
    {
    public:
       iterator(GetOpt* getopt) : getopt( getopt ), position(1) {};
       iterator(int pos) : position( pos ) {};
       iterator& operator++( ) { 
          ++position ; 
          return *this; 
       }  // prefix
       bool operator!=( iterator rhs ) { return position != rhs.position; }
       char operator*( );
    private:
       int position;
       GetOpt* getopt;
    };
    iterator begin() { return iterator( this); }
    iterator end() { return iterator(argCount); }
    friend class iterator;
private:
    std::string optionArgument; /* Global argument pointer. */
    int index; /* Global argv index. */
    int argCount;
    char** argStrings;
    std::string optionString;
    std::string errorText;
};
