#ifndef PROJECT_2_PARSER_H

#include <utility>
#include <variant>
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
            return tokens.at(curr);
        }
    };

    typedef pair<string, Token> Error;
    template<typename T>
    using ParseSuccess = pair<ParseInput, T>;

    template<typename T>
    struct Result {
        variant<ParseSuccess<T>, Error> result;

        explicit Result(ParseSuccess<T> value): result(value) {}
        explicit Result(Error error): result(error) {}

        static Result<T> ok(ParseSuccess<T> value) { return Result(value); }
        static Result<T> error(string message, Token token) { return Result({message, token}); }

        bool isOk() { return holds_alternative<ParseSuccess<T>>(result); }
        bool isError() { return holds_alternative<Error>(result); }

        ParseSuccess<T> getOk() { return get<ParseSuccess<T>>(result); }
        Error getError() { return get<Error>(result); }
    };

    Result<Program> parse(vector<Token> tokens);
    Result<Program> program(ParseInput input);

    Result<vector<Scheme>> schemes(ParseInput input);
    Result<vector<Fact>> facts(ParseInput input);
    Result<vector<Rule>> rules(ParseInput input);
    Result<vector<Query>> queries(ParseInput input);

    Result<Scheme> scheme(ParseInput input);
    Result<Fact> fact(ParseInput input);
    Result<Rule> rule(ParseInput input);
    Result<Query> query(ParseInput input);

    Result<HeadPredicate> headPredicate(ParseInput input);
    Result<Predicate> predicate(ParseInput input);

    Result<Id> id(ParseInput input);
    Result<String> string(ParseInput input);
    Result<Parameter> parameter(ParseInput input);
}

#define PROJECT_2_PARSER_H

#endif //PROJECT_2_PARSER_H
