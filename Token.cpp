#include "Token.h"

bool operator==(const Token& rhs, const Token& lhs) {
    return
    rhs.type == lhs.type &&
    rhs.lexeme == lhs.lexeme &&
    rhs.line == lhs.line;
}

// Determine which token is the "least" in terms of which
// token should be accepted
bool operator<(const Token& rhs, const Token& lhs) {
    // RHS is less  if...
    return
    // ...the lexeme is shorter or...
    rhs.lexeme.size() < lhs.lexeme.size() ||
    // ...the token type of RHS is lower on the list than LHS
    (rhs.lexeme.size() == lhs.lexeme.size() && rhs.type > lhs.type);
}

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

std::string Token::toString() const {
    return
            "(" +
            tokenTypeToString(type) +
            ",\"" +
            lexeme +
            "\"," +
            std::to_string(line) +
            ")";
}

std::ostream& operator<<(std::ostream& os, Token& token) {
    os << token.toString();
    return os;
}

std::ostream& operator<<(std::ostream& os, TokenType& type) {
    os << tokenTypeToString(type);
    return os;
}
