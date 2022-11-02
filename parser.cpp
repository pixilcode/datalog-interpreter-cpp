#include "parser.h"

#include <utility>

namespace parser {
    Result<Program> parse(const vector<Token>& tokens) {
        return program(ParseInput(tokens));
    }

    Result<Program> program(const ParseInput& input) {
        auto schemesResult = schemes(input);
        auto nextInput = schemesResult.first;

        auto factsResult = facts(nextInput);
        nextInput = factsResult.first;

        auto rulesResult = rules(nextInput);
        nextInput = rulesResult.first;

        auto queriesResult = queries(nextInput);
        nextInput = queriesResult.first;

        nextInput = matchToken(nextInput, TokenType::END_OF_FILE).first;
        auto finalSchemes = schemesResult.second;
        auto finalFacts = factsResult.second;
        auto finalRules = rulesResult.second;
        auto finalQueries = queriesResult.second;

        return Result<Program>({nextInput, Program(finalSchemes, finalFacts, finalRules, finalQueries)});
    }

    Result<vector<Scheme>> schemes(const ParseInput& input) {
        auto nextInput = matchToken(input, TokenType::SCHEMES).first;
        nextInput = matchToken(nextInput, TokenType::COLON).first;

        return schemeList(nextInput);
    }
    Result<vector<Fact>> facts(const ParseInput& input) {
        auto nextInput = matchToken(input, TokenType::FACTS).first;
        nextInput = matchToken(nextInput, TokenType::COLON).first;

        return factList(nextInput);
    }
    Result<vector<Rule>> rules(const ParseInput& input) {
        auto nextInput = matchToken(input, TokenType::RULES).first;
        nextInput = matchToken(nextInput, TokenType::COLON).first;

        return ruleList(nextInput);
    }
    Result<vector<Query>> queries(const ParseInput& input) {
        auto nextInput = matchToken(input, TokenType::QUERIES).first;
        nextInput = matchToken(nextInput, TokenType::COLON).first;

        return queryList(nextInput);
    }

    Result<vector<Scheme>> schemeList(const ParseInput& input, vector<Scheme> schemesList) {
        try {
            auto schemeResult = scheme(input);
            schemesList.push_back(schemeResult.second);
            return schemeList(schemeResult.first, schemesList);
        } catch(RecoverableError& e) {
            if (e.message != "Expected ID") throw e;
            if (schemesList.empty()) throw Error("Must have at least one scheme", input.currToken());
            return {input, schemesList};
        }
    }
    Result<vector<Fact>> factList(const ParseInput& input, vector<Fact> factsList) {
        try {
            auto factResult = fact(input);
            factsList.push_back(factResult.second);
            return factList(factResult.first, factsList);
        } catch(RecoverableError& e) {
            if (e.message != "Expected ID") throw e;
            return {input, factsList};
        }
    }
    Result<vector<Rule>> ruleList(const ParseInput& input, vector<Rule> rulesList) {
        try {
            auto ruleResult = rule(input);
            rulesList.push_back(ruleResult.second);
            return ruleList(ruleResult.first, rulesList);
        } catch(RecoverableError& e) {
            if (e.message != "Expected ID") throw e;
            return {input, rulesList};
        }
    }
    Result<vector<Query>> queryList(const ParseInput& input, vector<Query> queriesList) {
        try {
            auto queryResult = query(input);
            queriesList.push_back(queryResult.second);
            return queryList(queryResult.first, queriesList);
        } catch(RecoverableError& e) {
            if (e.message != "Expected ID") throw e;
            if (queriesList.empty()) throw Error("Must have at least one runQuery", input.currToken());
            return {input, queriesList};
        }
    }

    Result<Scheme> scheme(const ParseInput& input) {
        auto nameResult = id(input, true);
        auto nextInput =
                matchToken(nameResult.first, TokenType::LEFT_PAREN).first;
        auto paramsResult = idList(nextInput);
        nextInput = matchToken(paramsResult.first, TokenType::RIGHT_PAREN).first;

        return Result<Scheme>({nextInput, Scheme(nameResult.second, paramsResult.second)});
    }
    Result<Fact> fact(const ParseInput& input) {
        auto nameResult = id(input, true);
        auto nextInput =
                matchToken(nameResult.first, TokenType::LEFT_PAREN).first;
        auto argsResult = stringList(nextInput);
        nextInput = matchToken(argsResult.first, TokenType::RIGHT_PAREN).first;
        nextInput = matchToken(nextInput, TokenType::PERIOD).first;

        return Result<Fact>({nextInput, Fact(nameResult.second, argsResult.second)});
    }
    Result<Rule> rule(const ParseInput& input) {
        auto headResults = headPredicate(input);
        auto nextInput =
                matchToken(headResults.first, TokenType::COLON_DASH).first;
        auto predicatesResult = predicateList(nextInput);
        nextInput = matchToken(predicatesResult.first, TokenType::PERIOD).first;

        return Result<Rule>({nextInput, Rule(headResults.second, predicatesResult.second)});
    }
    Result<Query> query(const ParseInput& input) {
        auto predicatesResult = predicate(input, true);
        auto nextInput = matchToken(predicatesResult.first, TokenType::Q_MARK).first;

        return Result<Query>({nextInput, Query(predicatesResult.second)});
    }

    Result<HeadPredicate> headPredicate(const ParseInput& input) {
        auto nameResult = id(input, true);
        auto nextInput =
                matchToken(nameResult.first, TokenType::LEFT_PAREN).first;
        auto idsList = idList(nextInput);
        nextInput = matchToken(idsList.first, TokenType::RIGHT_PAREN).first;

        return Result<HeadPredicate>({nextInput, HeadPredicate(nameResult.second, idsList.second)});
    }
    Result<Predicate> predicate(const ParseInput& input, bool recoverable) {
        auto nameResult = id(input, recoverable);
        auto nextInput =
                matchToken(nameResult.first, TokenType::LEFT_PAREN).first;
        auto idsList = parameterList(nextInput);
        nextInput = matchToken(idsList.first, TokenType::RIGHT_PAREN).first;

        return Result<Predicate>({nextInput, Predicate(nameResult.second, idsList.second)});
    }

    Result<vector<Predicate>> predicateList(const ParseInput& input, vector<Predicate> predicatesList) {
        auto predicatesResult = predicate(input);
        predicatesList.push_back(predicatesResult.second);
        auto commaResult = tryToken(predicatesResult.first, TokenType::COMMA);
        if (!commaResult.has_value())
            if (predicatesList.empty()) throw Error("Must have at least one predicate", predicatesResult.first.currToken());
            else return {predicatesResult.first, predicatesList};
        else return predicateList(commaResult->first, predicatesList);
    }
    Result<vector<Parameter>> parameterList(const ParseInput& input, vector<Parameter> parametersList) {
        auto parametersResult = parameter(input);
        parametersList.push_back(parametersResult.second);
        auto commaResult = tryToken(parametersResult.first, TokenType::COMMA);
        if (!commaResult.has_value())
            if (parametersList.empty()) throw Error("Must have at least one parameter", parametersResult.first.currToken());
            else return {parametersResult.first, parametersList};
        else return parameterList(commaResult->first, parametersList);
    }
    Result<vector<Id>> idList(const ParseInput& input, vector<Id> idsList) {
        auto idResult = id(input);
        idsList.push_back(idResult.second);
        auto commaResult = tryToken(idResult.first, TokenType::COMMA);
        if (!commaResult.has_value())
            if (idsList.empty()) throw Error("Must have at least one ID", idResult.first.currToken());
            else return {idResult.first, idsList};
        else return idList(commaResult->first, idsList);
    }
    Result<vector<String>> stringList(const ParseInput& input, vector<String> stringsList) {
        auto stringResult = string(input);
        stringsList.push_back(stringResult.second);
        auto commaResult = tryToken(stringResult.first, TokenType::COMMA);
        if (!commaResult.has_value())
            if (stringsList.empty()) throw Error("Must have at least one string", stringResult.first.currToken());
            else return {stringResult.first, stringsList};
        else return stringList(commaResult->first, stringsList);
    }

    Result<Id> id(const ParseInput& input, bool recoverable) {
        try {
            auto idResult = matchToken(input, TokenType::ID);
            return Result<Id>({idResult.first, Id(idResult.second.lexeme)});
        } catch (Error& e) {
            if (recoverable) {
                throw RecoverableError(e.message, e.token);
            } else {
                throw e;
            }
        }
    }
    Result<String> string(const ParseInput& input) {
        auto stringResult = matchToken(input, TokenType::STRING);
        return Result<String>({stringResult.first, String(stringResult.second.lexeme)});
    }
    Result<Parameter> parameter(const ParseInput& input) {
        auto idResult = tryToken(input, TokenType::ID);
        if (idResult.has_value())
            return Result<Parameter>({idResult->first, Parameter(Id(idResult->second.lexeme))});
        auto stringResult = tryToken(input, TokenType::STRING);
        if (stringResult.has_value())
            return Result<Parameter>({stringResult->first, Parameter(String(stringResult->second.lexeme))});
        throw Error("Expected string or id parameter", input.currToken());
    }

    pair<ParseInput, Token> matchToken(const ParseInput& input, TokenType tType) {
        if (!input.currToken().matches(tType)) throw Error("Expected " + tokenTypeToString(tType), input.currToken());
        return {input.advance(), input.currToken()};
    }
    optional<pair<ParseInput, Token>> tryToken(const ParseInput& input, TokenType tType) {
        if (!input.currToken().matches(tType)) return nullopt;
        return pair<ParseInput, Token>({input.advance(), input.currToken()});
    }
}
