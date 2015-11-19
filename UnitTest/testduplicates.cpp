#include "stdafx.h"
#include "CppUnitTest.h"
#include <iostream>
#include <fstream>
#include <unordered_set>
#include "../GetOpt.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTest
{
TEST_CLASS(UnitTestDuplicates)
{
   using optarray = std::vector < std::string >;
   string optFileName = "options.txt";
   void createOptionFile(const optarray& fileoptions)
   {
      std::ofstream file(optFileName);
      for(auto opt : fileoptions) {
         file << opt << std::endl;
      }
      file.close();
   }

public:
   TEST_METHOD_INITIALIZE(Setup)
   {
   }

   TEST_METHOD(TestForSingleOptionDouble)
   {
      char* argv[] = { "prg.exe", "-v", "-d",  };
      optarray options = { "-x", "-d" };
      createOptionFile(options);
      GetOpt getopt(_countof(argv), argv, "vdx", optFileName);
      std::unordered_multiset<char> test;
      for(auto opt : getopt) {
         test.emplace(opt);
      }
      Assert::IsFalse(test.count('v') > 1, L"option v is not unique.");
      Assert::IsFalse(test.count('d') > 1, L"option d is not unique.");
      Assert::IsFalse(test.count('x') > 1, L"option x is not unique.");
   }

   TEST_METHOD(TestForSingleOptionDouble2)
   {
      char* argv[] = { "prg.exe", "-v", "-d", "-a", "-f" };
      optarray options = { "-x", "-d", "-f", "-o" };
      createOptionFile(options);
      GetOpt getopt(_countof(argv), argv, "vdxafo", optFileName);
      std::unordered_multiset<char> test;
      for(auto opt : getopt) {
         test.emplace(opt);
      }
      Assert::IsFalse(test.count('v') > 1, L"option v is not unique.");
      Assert::IsFalse(test.count('d') > 1, L"option d is not unique.");
      Assert::IsFalse(test.count('x') > 1, L"option x is not unique.");
      Assert::IsFalse(test.count('a') > 1, L"option a is not unique.");
      Assert::IsFalse(test.count('f') > 1, L"option f is not unique.");
      Assert::IsFalse(test.count('o') > 1, L"option o is not unique.");
   }
   TEST_METHOD(TestForDoubleOptionWithArguments)
   {
      char* argv[] = { "prg.exe", "-v", "-d", "-H", "home" };
      optarray options = { "-l", "long", "-H", "hit" };
      createOptionFile(options);
      GetOpt getopt(_countof(argv), argv, "H:l:vd", optFileName);
      std::unordered_multiset<char> test;
      std::string dummy;
      std::string home;
      for(auto opt : getopt) {
         switch(opt) {
            case 'H':
               test.emplace(opt);
               home = getopt.get();
               break;
            case 'l':
               test.emplace(opt);
               dummy = getopt.get();
               break;
            default:
               test.emplace(opt);
               break;
         }
      }
      Assert::IsFalse(test.count('v') > 1, L"option v is not unique.");
      Assert::IsFalse(test.count('d') > 1, L"option d is not unique.");
      Assert::IsFalse(test.count('H') > 1, L"option H is not unique.");
      Assert::IsFalse(test.count('l') > 1, L"option l is not unique.");
      Assert::AreEqual("home", home.c_str(), L"H is not set with home (cmd line option wins).");
   }
};

}