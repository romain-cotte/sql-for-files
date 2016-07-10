#ifndef __MCSCANNER_HPP__
#define __MCSCANNER_HPP__ 1

#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include "fq_parser.tab.hh"
#include "location.hh"

namespace FQ {

class FQ_Scanner : public yyFlexLexer {
public:

  FQ_Scanner(std::istream *in) : yyFlexLexer(in) {
    loc = new FQ::FQ_Parser::location_type();
  };

  virtual ~FQ_Scanner() {
    delete loc;
  };

  //get rid of override virtual function warning
  using FlexLexer::yylex;

  virtual
  int yylex(FQ::FQ_Parser::semantic_type * const lval,
            FQ::FQ_Parser::location_type *location);
  // YY_DECL defined in FQ_lexer.l
  // Method body created by flex in FQ_lexer.yy.cc


private:
  /* yyval ptr */
  FQ::FQ_Parser::semantic_type *yylval = nullptr;
  /* location ptr */
  FQ::FQ_Parser::location_type *loc   = nullptr;
};

} /* end namespace MC */

#endif /* END __MCSCANNER_HPP__ */
