#include "testTools.hpp"

namespace momo {

double TestTools::tolerance = 1e-4;
std::string * TestTools::logFileName =0;
std::ofstream * TestTools::logStream = 0;

  void TestTools::prepare(std::string fn) {
    // singletons scheinen in cpp nicht "gut"zu sein:
    // stackoverflow.com/questions/86582/singleton-how-should-it-be-used
    // static classes sind u.U nicht viel besser ...
    TestTools::logFileName = new std::string(fn)     ;
    TestTools::logStream = new std::ofstream((TESTDIR + (*logFileName)).c_str());
  }

  void TestTools::testingComplete() {
    if (logStream->is_open()) {
      logStream->close();
    }
    delete TestTools::logFileName;
  }

  void TestTools::logMessage(std::string message) {
    (*(logStream)) << message;
  }

  void TestTools::report(std::string a, const char* b, std::string c) {
    report(a, std::string(b), c);
  }


void TestTools::report(bool success, std::string msg_) {

    if ( success ) {
      (*logStream) << "tested and confirmed." << msg_ << std::endl;
    } else {
      (*logStream) << "FAILED: \t" <<  msg_  << std::endl;
      std::cout << "FAILURE:  " << msg_ << std::endl;
    };
}

void TestTools::report(double result, double expected, std::string msg_) {

  if (fabs(result-expected) < tolerance) {
      (*logStream) << "confirmed " << msg_ << expected << std::endl;
  } else {
      (*logStream) << "FAILED: \t" << result << " <> " << expected << " for: " <<  msg_  << std::endl;
      std::cout << "FAILED: \t" << result << " <> " << expected << " for: " <<  msg_  << std::endl;
  }

}

std::ofstream * TestTools::getLogStream(){
  return TestTools::logStream;
}

  std::string * TestTools::writeFile(std::string fn, std::string content) {

    // opens a file in testdirectory with specified filename=fn
    // writes content into this file, then closes and returns filepath

     std::string *fpath = new std::string(TESTDIR + fn);
    std::ofstream ofs(fpath->c_str());
    if (!ofs.is_open()) throw std::runtime_error("couldnt open file for writing: " + (*fpath));
    ofs << content << std::endl;
    if (ofs.is_open()) ofs.close();
    return fpath;
  }



}
