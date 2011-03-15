%{
#include <iostream>
#include <vector>
#include <string>

std::vector<std::string> _clades;
%}

%x subclades
%option noyywrap

clade [a-zA-Z]+
valid [a-zA-Z\| \(\)]
linkclade "[["{valid}+"]]"
tempclade "{{"("sp"|"splast")\|{valid}+"}}"

%{
void reboot()
{
   if (_clades.size()) {
      yy_scan_string(_clades[_clades.size() - 1].c_str());
      _clades.clear();
   }
}
%}

%%


^{clade}:.*$           _clades.push_back(yytext);
"</html>"              {
                          reboot();
                          BEGIN(subclades);
                       }
\n|.                   ;

<subclades>
{
\(={linkclade}\)        ;
{linkclade}             _clades.push_back(yytext);
{tempclade}             _clades.push_back(yytext);
\n|.                    ;
}

<<EOF>>                 {
                          BEGIN(INITIAL);
                          yyterminate();
                        }

%%