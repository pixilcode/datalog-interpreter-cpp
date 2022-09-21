#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <utility>

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
        lexeme(std::move(lexeme)),
        line(line) {}
};

inline bool operator==(const Token& rhs, const Token& lhs) {
    return
    rhs.type == lhs.type &&
    rhs.lexeme == lhs.lexeme &&
    rhs.line == lhs.line;
}

#endif // TOKEN_H

