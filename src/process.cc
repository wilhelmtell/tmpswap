#include "process.hh"
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

namespace fs = boost::filesystem;

namespace tms {
void process(std::string const& tgt) {
  using isbic = std::istreambuf_iterator<char>;
  auto const tmp = fs::temp_directory_path() / fs::unique_path();
  std::ofstream out{tmp.string()};
  std::copy(isbic{std::cin}, isbic{}, std::ostream_iterator<char>{out});
  fs::rename(tmp, tgt);
}
}
