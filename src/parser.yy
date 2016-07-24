%skeleton "lalr1.cc"
%require  "3.0"
%debug
%defines
%define api.namespace { sqlforfiles }
%define parser_class_name { Parser }

%code requires {
  namespace sqlforfiles {
    class Driver;
    class Scanner;
  }

// The following definitions is missing when %locations isn't used
# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

}

%parse-param { Scanner &scanner }
%parse-param { Driver &driver }

%code{
   #include <iostream>
   #include <cstdlib>
   #include <fstream>

   /* include for all driver functions */
   #include "driver.hpp"

#undef yylex
#define yylex scanner.yylex
}

%define api.value.type variant
%define parse.assert

%token               END    0     "end of file"
%token               SELECT
%token               AS
%token               FROM
%token               DELIMITER
%token               UPPER
%token               LOWER
%token <std::string> WORD
%token <std::string> FILENAME
%token <std::string> FROM_FILENAME
%token <std::string> DELIMITER_CHARACTER
%token               NEWLINE
%token               CHAR
%token <int>         INTEGER
%token               COMMA
%token               SEMICOLON

%locations

%%

list_query
  : query
  | query list_query
  ;

query: SELECT list_integer FROM_FILENAME options SEMICOLON {
  driver.add_filename($3);
  driver.process_query(std::cout);
};

options
  :
  | DELIMITER DELIMITER_CHARACTER { driver.set_delimiter($2); }
  ;

list_integer
  : INTEGER                    { driver.add_field_selection($1); }
  | list_integer COMMA INTEGER { driver.add_field_selection($3); }
  ;


%%

void sqlforfiles::Parser::error(const location_type &l, const std::string &err_message) {
  std::cerr << "Error: " << err_message << " at " << l << "\n";
}
