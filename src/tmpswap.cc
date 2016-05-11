#include "process.hh"
#include "static_config.hh"
#include <iostream>
#include <stdexcept>

int main(int argc, char* argv[]) {
  if(argc != 2) {
    std::cout << "Usage: " << PACKAGE_NAME << " <filename>\n";
    return 1;
  }
  try {
    tms::process(argv[1]);
  } catch(std::exception const& e) {
    std::cerr << "error:" << e.what() << '\n';
    return 2;
  }
}
