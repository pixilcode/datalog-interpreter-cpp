#ifndef TOKEN_H
#define TOKEN_H
#include <string>

enum class TokenType {
    COMMA,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    COLON,
    COLON_DASH,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    STRING,
    COMMENT,
    END_OF_FILE,
    UNDEFINED
};

struct Token {
TokenType type;
std::string lexeme;
int line;

Token(TokenType type, std::string lexeme, int line):
    type(type),
    lexeme(lexeme),
    line(line) {}
};

#endif // TOKEN_H

