#ifndef __FQDRIVER_HPP__
#define __FQDRIVER_HPP__ 1

#include <string>
#include <cstddef>
#include <istream>
#include <vector>

#include "scanner.hpp"
#include "parser.tab.hh"

namespace sqlforfiles {

class Driver {
public:
   Driver() = default;

   virtual ~Driver();

   /**
    * parse - parse from a file
    * @param filename - valid string with input file
    */
   void parse(const char * const filename);
   /**
    * parse - parse from a c++ input stream
    * @param is - std::istream&, valid input stream
    */
   void parse(std::istream &iss);

   void add_field_selection(const int &i);
   void set_delimiter(const std::string &delimiter);
   void set_mode_interactive(const bool is_interactive);
   void add_filename(const std::string &filename);

   std::ostream& process_query(std::ostream &stream);

private:

   void parse_helper(std::istream &stream);
   std::vector<std::string> selector(const std::vector<int> select,
                                     const std::vector<std::string> input);

   sqlforfiles::Parser  *parser  = nullptr;
   sqlforfiles::Scanner *scanner = nullptr;

   const std::string red   = "\033[1;31m";
   const std::string blue  = "\033[1;36m";
   const std::string norm  = "\033[0m";

   // std::string delimiter = ";";
   char delimiter = ';';
   std::vector<int> select;
   std::string filename;
   bool mode_interactive;
   std::vector<std::vector<std::string> > buffer;

};

} /* end namespace FQ */
#endif /* END __FQDRIVER_HPP__ */
