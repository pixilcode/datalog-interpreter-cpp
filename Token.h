#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <utility>
#include <iostream>

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

std::string tokenTypeToString(const TokenType& type) {
    switch (type) {
        case TokenType::COMMA:
            return "COMMA";
        case TokenType::PERIOD:
            return "PERIOD";
        case TokenType::Q_MARK:
            return "Q_MARK";
        case TokenType::LEFT_PAREN:
            return "LEFT_PAREN";
        case TokenType::RIGHT_PAREN:
            return "RIGHT_PAREN";
        case TokenType::COLON:
            return "COLON";
        case TokenType::COLON_DASH:
            return "COLON_DASH";
        case TokenType::MULTIPLY:
            return "MULTIPLY";
        case TokenType::ADD:
            return "ADD";
        case TokenType::SCHEMES:
            return "SCHEMES";
        case TokenType::FACTS:
            return "FACTS";
        case TokenType::RULES:
            return "RULES";
        case TokenType::QUERIES:
            return "QUERIES";
        case TokenType::ID:
            return "ID";
        case TokenType::STRING:
            return "STRING";
        case TokenType::COMMENT:
            return "COMMENT";
        case TokenType::END_OF_FILE:
            return "EOF";
        case TokenType::UNDEFINED:
            return "UNDEFINED";
        default:
            return "(ERROR: UNDEFINED TOKEN TYPE STRING)";
    }
}

std::ostream& operator<<(std::ostream& os, TokenType& type) {
    os << tokenTypeToString(type);
    return os;
}

struct Token {
    TokenType type;
    std::string lexeme;
    int line;

    Token(TokenType type, std::string lexeme, int line):
        type(type),
        lexeme(std::move(lexeme)),
        line(line) {}

    std::string toString() const {
        return
        "(" +
        tokenTypeToString(type) +
        ",\"" +
        lexeme +
        "\"," +
        std::to_string(line) +
        ")";
    }
};

inline bool operator==(const Token& rhs, const Token& lhs) {
    return
    rhs.type == lhs.type &&
    rhs.lexeme == lhs.lexeme &&
    rhs.line == lhs.line;
}

std::ostream& operator<<(std::ostream& os, Token& token) {
    os << token.toString();
    return os;
}

#endif // TOKEN_H

