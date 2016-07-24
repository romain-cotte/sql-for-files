%{
/* C++ string header, for string ops below */
#include <string>

/* Implementation of yyFlexScanner */
#include "scanner.hpp"
#undef  YY_DECL
#define YY_DECL int sqlforfiles::Scanner::yylex(sqlforfiles::Parser::semantic_type * const lval, sqlforfiles::Parser::location_type *location)

/* typedef to make the returns for the tokens shorter */
using token = sqlforfiles::Parser::token;

/* define yyterminate as this instead of NULL */
#define yyterminate() return token::END;

/* msvc2010 requires that we exclude this header file. */
#define YY_NO_UNISTD_H

/* update location on matching */
#define YY_USER_ACTION loc->step(); loc->columns(yyleng);

%}

%option debug
%option nodefault
%option yyclass="sqlforfiles::Scanner"
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
            yylval->build<int> (atoi(yytext)-1);
            return token::INTEGER;
          }

\*        {
            yylval->build<int> (-1);
            return token::INTEGER;
          }

[a-zA-Z0-9]+\.[a-zA-Z0-9]+ {
            yylval->build<std::string> (yytext);
            return token::FILENAME;
          }

FROM\ [^\ ]+  {
                yylval->build<std::string> (yytext+5);
                return token::FROM_FILENAME;
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
