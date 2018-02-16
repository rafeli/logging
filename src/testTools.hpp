#ifndef _TESTTOOLS_HPP
#define _TESTTOOLS_HPP

#define TESTDIR "./testdir/"
#define EPSILON 1e-15

#include <fstream>
#include <stdexcept>
#include <iostream>

// following includes needed for trimmer
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

namespace momo {

class TestTools {

private:
  static double tolerance;
  static std::string *logFileName;
  static std::ofstream *logStream;

public:

  static void prepare(std::string fn) ;

  static void testingComplete() ;

  static void logMessage(std::string message) ;

  static void report(bool succes, std::string msg);  
  static void report(std::string , const char*, std::string test_); // proxy for report(str,str,str)
  static void report(double , double, std::string);
template <typename T>
static void report(T actual_, T expected_, std::string test_) {

    if ( actual_ == expected_ ) {
      (*logStream) << test_ << "tested and confirmed:\n\t" 
		   << actual_ << std::endl;
    } else {
      (*logStream) << test_ << "FAILED: \n\t(" <<  expected_
    		   << ") <> \n\t(" << actual_ << ")" << std::endl;
      std::cout << "FAILURE in " << test_ << std::endl;
    };
}


  static std::ofstream * getLogStream();

  static void setTolerance(double );

  static std::string * writeFile(std::string fn, std::string content) ;



};
}
#endif // _TESTTOOLS_HPP
