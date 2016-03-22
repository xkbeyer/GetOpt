#include "stdafx.h"
#include "CppUnitTest.h"

#include "../GetOpt.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTest {
TEST_CLASS(UnitTestNonOptionParameter)
{
public:
   TEST_METHOD_INITIALIZE(Setup)
   {}

   TEST_METHOD(OneNonOptionArgumentAtFirst)
   {
      char opt = 0;
      char* argv[] = { "prg.exe", "filename", "-H", "/user/home" };
      string optionH;
      string filename;
      GetOpt getopt(_countof(argv), argv, "H:");
      for( auto opt : getopt ) {
         switch( opt ) {
            case 'H':
               optionH = getopt.get();
               break;
            case EOF:
               Assert::Fail(L"unexpected end of input");
               break;
            default:
               wstring fail = L"unknown option ";
               fail += opt;
               Assert::Fail(fail.c_str());
         }
      }
      Assert::AreEqual(string("/user/home"), optionH);
      auto noopts = getopt.getRemainingArguments();
      Assert::AreEqual(1, (int) noopts.size(), L"size of no opts.");
      Assert::AreEqual(std::string("filename"), noopts[0]);
   }

   TEST_METHOD(OneNonOptionArgumentAtSecond)
   {
      char opt = 0;
      char* argv[] = { "prg.exe", "-H/user/home", "filename" };
      string optionH;
      string filename;
      GetOpt getopt(_countof(argv), argv, "H:");
      for( auto opt : getopt ) {
         switch( opt ) {
            case 'H':
               optionH = getopt.get();
               break;
            case EOF:
               //Assert::Fail(L"unexpected end of input");
               break;
            default:
               wstring fail = L"unknown option ";
               fail += opt;
               Assert::Fail(fail.c_str());
         }
      }

      Assert::AreEqual(string("/user/home"), optionH);
      auto noopts = getopt.getRemainingArguments();
      Assert::AreEqual(1, (int) noopts.size(), L"size of no opts.");
      Assert::AreEqual(std::string("filename"), noopts[0]);
   }

   TEST_METHOD(TwoNonOptionArgument)
   {
      char opt = 0;
      char* argv[] = { "prg.exe", "firstfile", "-H", "/user/home", "filename" };
      string optionH;
      string filename;
      GetOpt getopt(_countof(argv), argv, "H:");
      for( auto opt : getopt ) {
         switch( opt ) {
            case 'H':
               optionH = getopt.get();
               break;
            case EOF:
               //Assert::Fail(L"unexpected end of input");
               break;
            default:
               wstring fail = L"unknown option ";
               fail += opt;
               Assert::Fail(fail.c_str());
         }
      }
      Assert::AreEqual(string("/user/home"), optionH);

      auto noopts = getopt.getRemainingArguments();
      Assert::AreEqual(2, (int) noopts.size(), L"size of no opts.");
      Assert::AreEqual(std::string("filename"), noopts[0]);
      Assert::AreEqual(std::string("firstfile"), noopts[1]);
   }
   TEST_METHOD(TwoNonOptionArgumentInBetween)
   {
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
            case EOF:
               Assert::Fail(L"unexpected end of input");
               break;
            default:
               wstring fail = L"unknown option ";
               fail += opt;
               Assert::Fail(fail.c_str());
         }
      }
      Assert::AreEqual(string("/user/home"), optionH);
      Assert::IsTrue(optA, L"option -a not found.");
      Assert::IsTrue(optX, L"option -x not found.");
      auto noopts = getopt.getRemainingArguments();
      Assert::AreEqual(2, (int) noopts.size(), L"size of no opts.");
      Assert::AreEqual(std::string("firstfile"), noopts[0]);
      Assert::AreEqual(std::string("filename"), noopts[1]);
   }

   TEST_METHOD(GetRemainingArgsOnly)
   {
      char opt = 0;
      char* argv[] = { "prg.exe", "-a", "firstfile", "-H", "/user/home", "filename", "-x" };
      GetOpt getopt(_countof(argv), argv, "axH:");
      auto noopts = getopt.getRemainingArguments();
      for( int i = 0; i < noopts.size(); ++i ) {
         Assert::AreEqual(string(argv[i+1]), noopts[i]);
      }
   }

   TEST_METHOD(GetRemainingArgsOnlyWithFileOptions)
   {
      char opt = 0;
      char* argv[] = { "prg.exe", "-a", "firstfile", "-H", "/user/home", "filename", "-x" };
      GetOpt getopt(_countof(argv), argv, "axH:");
      auto noopts = getopt.getRemainingArguments();
      for( int i = 0; i < noopts.size(); ++i ) {
         Assert::AreEqual(string(argv[i + 1]), noopts[i]);
      }
   }
};

}
