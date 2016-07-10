%{
/* C++ string header, for string ops below */
#include <string>

/* Implementation of yyFlexScanner */
#include "fq_scanner.hpp"
#undef  YY_DECL
#define YY_DECL int FQ::FQ_Scanner::yylex(FQ::FQ_Parser::semantic_type * const lval, FQ::FQ_Parser::location_type *location)

/* typedef to make the returns for the tokens shorter */
using token = FQ::FQ_Parser::token;

/* define yyterminate as this instead of NULL */
#define yyterminate() return token::END;

/* msvc2010 requires that we exclude this header file. */
#define YY_NO_UNISTD_H

/* update location on matching */
#define YY_USER_ACTION loc->step(); loc->columns(yyleng);

%}

%option debug
%option nodefault
%option yyclass="FQ::FQ_Scanner"
%option noyywrap
%option c++

%%
%{
  /** Code executed at the beginning of yylex **/
  yylval = lval;
%}


select    { return token::SELECT;    }
SELECT    { return token::SELECT;    }
from      { return token::FROM;      }
FROM      { return token::FROM;      }
as        { return token::AS;        }
AS        { return token::AS;        }
delimiter { return token::DELIMITER; }
DELIMITER { return token::DELIMITER; }

[0-9]+    {
            yylval->build<int> (atoi(yytext));
            return token::INTEGER;
          }

[a-zA-Z0-9]+\.[a-zA-Z0-9]+ {
            yylval->build<std::string> (yytext);
            return token::FILENAME;
          }

[a-z]     { return token::LOWER; }
[A-Z]     { return token::UPPER; }

[a-zA-Z]+ {
            yylval->build<std::string> (yytext);
            return token::WORD;
          }

'[\\t;,]' {
            yylval->build<std::string> (yytext);
            return token::DELIMITER_CHARACTER;
          }

\n        { }
,         { return token::COMMA; }
;         { return token::SEMICOLON; }
.         { }

%%
