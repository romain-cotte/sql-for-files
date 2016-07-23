#include <cctype>
#include <fstream>
#include <cassert>
#include <fstream>
#include <vector>

#include "driver.hpp"
#include "util/vec.hpp"

sqlforfiles::Driver::~Driver() {
  delete(scanner);
  scanner = nullptr;
  delete(parser);
  parser = nullptr;
}

void sqlforfiles::Driver::parse(const char * const filename) {
  assert(filename != nullptr);
  std::ifstream in_file(filename);

  if (!in_file.good()) {
    std::cout << "can't open file filename" << std::endl;
    exit(EXIT_FAILURE);
  }

  set_mode_interactive(false);

  parse_helper(in_file);
  return;
}

void sqlforfiles::Driver::parse(std::istream &stream) {
  if (!stream.good() && stream.eof()) {
    return;
  }

  set_mode_interactive(true);

  parse_helper(stream);
  return;
}

void sqlforfiles::Driver::parse_helper(std::istream &stream) {
  if (this->mode_interactive) {
    std::cout << "=>";
  }
  delete(scanner);
  try {
    scanner = new sqlforfiles::Scanner(&stream);
  }
  catch(std::bad_alloc &ba) {
    std::cerr << "Failed to allocate scanner: (" <<
      ba.what() << "), exiting!!\n";
    exit(EXIT_FAILURE);
  }
  delete(parser);

  try {
    parser = new sqlforfiles::Parser(
      (*scanner), /* scanner */
      (*this)     /* driver */
    );
  }
  catch (std::bad_alloc &ba) {
    std::cerr << "Failed to allocate parser: (" <<
      ba.what() << "), exiting!!\n";
    exit(EXIT_FAILURE);
  }
  const int accept(0);

  if (parser->parse() != accept) {
    std::cerr << "Parse failed!!\n";
  }
  // else {
  //   std::cout << "parse ok" << std::endl;
  // }

  stream.clear();

  if (this->mode_interactive) {
    parse_helper(stream);
  }

  return;
}

void sqlforfiles::Driver::set_mode_interactive(bool is_interactive) {
  this->mode_interactive = is_interactive;
}


void sqlforfiles::Driver::add_filename(const std::string &filename) {
  this->filename = filename;
}

void sqlforfiles::Driver::add_field_selection(const int &i) {
  select.push_back(i);
}

void sqlforfiles::Driver::set_delimiter(const std::string &delimiter) {
  this->delimiter = delimiter[1];
}


template <class T>
std::ostream& operator<< (std::ostream& out, const std::vector<T>& v) {
  out << "[";
  size_t last = v.size() - 1;
  for(size_t i = 0; i < v.size(); ++i) {
    out << v[i];
    if (i != last) {
      out << ", ";
    }
  }
  out << "]";
  return out;
}


std::ostream& sqlforfiles::Driver::process_query(std::ostream &stream) {
  std::string line;
  std::ifstream file(filename);
  std::string currentString;

  int prevOcc, fieldNumber;
  int i, l;
  bool first;
  std::vector<std::string> buff;
  if (file.is_open()) {
    while (getline(file, line)) {
      prevOcc = -1;
      // fieldNumber = 1;
      first = true;
      for (i = 0, l = line.size(); i < l; i++) {
        buff.clear();
        if (line[i] == this->delimiter) {
          buff.push_back(line.substr(prevOcc + 1, i - prevOcc - 1));
          // std::cout << line.substr(prevOcc + 1, i - prevOcc - 1);

          // auto f = std::find(this->select.begin(),
          //                    this->select.end(),
          //                    fieldNumber);
          // if (f != this->select.end()) {
          //   if (first) {
          //     std::cout << line.substr(prevOcc + 1, i - prevOcc - 1);
          //     first = false;
          //   } else {
          //     std::cout << ";" << line.substr(prevOcc + 1, i - prevOcc - 1);
          //   }
          // }
          prevOcc = i;
          // fieldNumber++;
        }
      }


      std::vector<int>::iterator it;
      for (it = this->select.begin(); it != this->select.end(); ++it) {
        std::cout << *it << std::endl;
      }

      std::cout << "here" << std::endl;

      std::vector<std::string> result = Vec::selector(buff, this->select);

      std::vector<std::string>::iterator it2;
      std::cout << "----:" << std::endl;
      for (it2 = result.begin(); it2 != result.end(); ++it2) {
        std::cout << *it2 << std::endl;
      }


      // std::cout << result << endl;
      // Vec::output(std::cout, result, ';');

      // auto f = std::find(this->select.begin(),
      //                    this->select.end(),
      //                    fieldNumber);
      // if (f != this->select.end()) {
      //   if (first) {
      //     std::cout << line.substr(prevOcc + 1, i - prevOcc - 1);
      //     first = false;
      //   } else {
      //     std::cout << ";" << line.substr(prevOcc + 1, i - prevOcc - 1);
      //   }
      // }

      // std::cout << std::endl;

    }
    file.close();
  } else {
    stream << "Unable to open file " << filename << std::endl;
  }

  if (this->mode_interactive) {
    stream << "=>";
  }

  return stream;
}
