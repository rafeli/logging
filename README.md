# logging

my solution to log DEBUG/WARNING/ERROR-messages from C/CPP-software

# USE: (include logging.hpp)

int main() {

  double x = 77.7;

  Logging::prepare();
  
  MYLOG(DEBUG, "ENTERING with x=" << x);

}

Each run will (re)create the file "test.log" with e.g.:

DEBUG: int main(): ENTERING with x=77.7
