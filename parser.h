#ifndef PROJECT_2_PARSER_H

#include <utility>
#include <variant>
#include <optional>
#include <stdexcept>
#include "ast.h"
#include "Token.h"

namespace parser {
    using namespace ast;

    struct ParseInput {
        vector<Token> tokens;
        size_t curr;

        explicit ParseInput(vector<Token> tokens, size_t curr = 0):
                tokens(std::move(tokens)),
                curr(curr) {}

        [[nodiscard]] ParseInput advance(size_t numTokens = 1) const {
            return ParseInput(tokens, curr + numTokens);
        }

        [[nodiscard]] Token currToken() const {
            if (curr > tokens.size()) throw runtime_error("attempted to access token out of bounds");
            return tokens.at(curr);
        }
    };

    struct Error : exception {
        string message;
        Token token;

        Error(string message, Token token): message(std::move(message)), token(std::move(token)) {}
    };

    template<typename T>
    using Result = pair<ParseInput, T>;

    Result<Program> parse(const vector<Token>& tokens);
    Result<Program> program(const ParseInput& input);

    Result<vector<Scheme>> schemes(const ParseInput& input);
    Result<vector<Fact>> facts(const ParseInput& input);
    Result<vector<Rule>> rules(const ParseInput& input);
    Result<vector<Query>> queries(const ParseInput& input);

    Result<vector<Scheme>> schemeList(const ParseInput& input, vector<Scheme> schemesList = {});
    Result<vector<Fact>> factList(const ParseInput& input, vector<Fact> factsList = {});
    Result<vector<Rule>> ruleList(const ParseInput& input, vector<Rule> rulesList = {});
    Result<vector<Query>> queryList(const ParseInput& input, vector<Query> queriesList = {});

    Result<Scheme> scheme(const ParseInput& input);
    Result<Fact> fact(const ParseInput& input);
    Result<Rule> rule(const ParseInput& input);
    Result<Query> query(const ParseInput& input);

    Result<HeadPredicate> headPredicate(const ParseInput& input);
    Result<Predicate> predicate(const ParseInput& input);

    Result<vector<Predicate>> predicateList(const ParseInput& input, vector<Predicate> predicatesList = {});
    Result<vector<Parameter>> parameterList(const ParseInput& input, vector<Parameter> parametersList = {});
    Result<vector<Id>> idList(const ParseInput& input, vector<Id> idsList = {});
    Result<vector<String>> stringList(const ParseInput& input, vector<String> stringsList = {});

    Result<Id> id(const ParseInput& input);
    Result<String> string(const ParseInput& input);
    Result<Parameter> parameter(const ParseInput& input);

    pair<ParseInput, Token> matchToken(const ParseInput& token, TokenType tType);
    optional<pair<ParseInput, Token>> tryToken(const ParseInput& input, TokenType tType);
}

#define PROJECT_2_PARSER_H

#endif //PROJECT_2_PARSER_H
