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
    COLON_DASH,
    COLON,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    STRING,
    COMMENT,
    UNDEFINED,
    END_OF_FILE,
};

struct Token {
    TokenType type;
    std::string lexeme;
    int line;

    Token(TokenType type, std::string lexeme, int line):
        type(type),
        lexeme(std::move(lexeme)),
        line(line) {}

    [[nodiscard]] bool matches(TokenType tType) const;
    [[nodiscard]] std::string toString() const;
};

std::string tokenTypeToString(const TokenType& type);
std::ostream& operator<<(std::ostream& os, TokenType& type);
std::ostream& operator<<(std::ostream& os, Token& token);
bool operator==(const Token& rhs, const Token& lhs);
bool operator<(const Token& rhs, const Token& lhs);

#endif // TOKEN_H

