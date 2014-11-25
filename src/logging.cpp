#include "logging.hpp"

std::ofstream *Logging::ofs = 0;
std::stringstream *Logging::buffer = 0;
std::streambuf *oldCerrBuf;

Logging::Logging() {
}

Logging::~Logging() {
}

void Logging::prepare() {
  // dont know how to set a std::ofstream* to std::cout
  // but logging to a file is probably better anyway ...
  Logging::ofs = new std::ofstream("./test.log");
  Logging::buffer = new std::stringstream();

  // redirect error to logfile
  oldCerrBuf = std::clog.rdbuf((Logging::buffer)->rdbuf());
  
}

void Logging::finalize() {

  // reset cerr
  std::clog.rdbuf(oldCerrBuf);

  // close logfile
  if (ofs->is_open()) {
    ofs -> close();
  }
}

void Logging::log(int status, std::string method) {


  std::string s = (*Logging::buffer).str();

  // output the status, method and message, e.g.: 
  // void MyModule::myMethod(): entering  ...
  // skip if status of message unimportant
  if (status <= logLevel) {
    switch  (status) {
    case DEBUGD: 
      (*ofs) << "DEBUGD: ";
      break;
    case DEBUG: 
      (*ofs) << "DEBUG: ";
      break;
    case INFO: 
      (*ofs) << "INFO: ";
      break;
    case WARNING: 
      (*ofs) << "WARNING: ";
      break;
    case THROWING: 
      (*ofs) << "THROWING: ";
      break;
    case ERROR: 
      (*ofs) << "ERROR: ";
      break;
    default:
      std::cout << "LOGGING ERROR: unknown status\n";
      break;
    }
    (*ofs) <<  method << ": " << (*Logging::buffer).str() << std::endl;
  }

  // clear buffer (has been written in Macro)
  (*Logging::buffer).clear();
  (*Logging::buffer).str("");

}

