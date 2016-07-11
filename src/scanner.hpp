#ifndef __MCSCANNER_HPP__
#define __MCSCANNER_HPP__ 1

#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include "parser.tab.hh"
#include "location.hh"

namespace sqlforfiles {

class Scanner : public yyFlexLexer {
public:

  Scanner(std::istream *in) : yyFlexLexer(in) {
    loc = new sqlforfiles::Parser::location_type();
  };

  virtual ~Scanner() {
    delete loc;
  };

  //get rid of override virtual function warning
  using FlexLexer::yylex;

  virtual
  int yylex(sqlforfiles::Parser::semantic_type * const lval,
            sqlforfiles::Parser::location_type *location);
  // YY_DECL defined in lexer.l
  // Method body created by flex in lexer.yy.cc


private:
  /* yyval ptr */
  sqlforfiles::Parser::semantic_type *yylval = nullptr;
  /* location ptr */
  sqlforfiles::Parser::location_type *loc   = nullptr;
};

} /* end namespace MC */

#endif /* END __MCSCANNER_HPP__ */
