#include "Interpreter.h"

#include <algorithm>
#include <iostream>

tuple<
        vector<pair<ast::Rule, Relation>>,
        int,
        vector<pair<ast::Query, Relation>>
> Interpreter::runQuery() {
    for (const auto &scheme: program.schemes) {
        // Get the vector of attributes
        vector<string> attributes = idListToStrings(scheme.params);

        // Create the relation and add it to the database
        Relation relation = Relation(scheme.name.id, Header(attributes), {});
        database.addRelation(scheme.name.id, relation);
    }

    for (const auto &fact: program.facts) {
        // Make a tuple from the fact
        Tuple tuple = Tuple(stringsListToStrings(fact.args));

        // Add the fact to the relation
        database.addTuple(fact.name.id, tuple);
    }

    bool noAddition;
    int numPasses = 0;
    vector<pair<ast::Rule, Relation>> rulesEval;
    do {
        noAddition = true;
        ++numPasses;
        for (const auto &rule: program.rules) {
            if (rule.predicates.empty())
                throw runtime_error("Rule can't have zero predicates");

            // Evaluate predicates on RHS
            vector<Relation> predicateResults;
            for (const auto &pred: rule.predicates) {
                predicateResults.push_back(evaluatePredicate(pred));
            }

            // Join the resulting relations
            Relation joinResult = predicateResults.at(0);
            for (size_t i = 1; i < predicateResults.size(); i++) {
                joinResult = joinResult.naturalJoin(predicateResults.at(i));
            }

            // Project the columns that appear in the head predicate
            vector<string> header = makeHeader(rule.head.params);
            Relation projectResult = joinResult.project(header);

            // Rename the relation to make it union-compatible
            Relation oldRelation =
                    database.getRelation(rule.head.name.id);
            Relation renameResult =
                    projectResult.rename(oldRelation.getHeader().getAttributes());

            // Union with the relation in the database
            auto [finalRelation, tuplesAdded] = oldRelation.union_(renameResult);
            database.addRelation(rule.head.name.id, finalRelation);

            rulesEval.emplace_back(rule, renameResult);
            noAddition = noAddition && tuplesAdded == 0;
        }
    } while (!noAddition);

    vector<pair<ast::Query, Relation>> queryResults;

    for (const auto &query: program.queries) {
        // Evaluate the predicate
        Relation result = evaluatePredicate(query.pred);

        queryResults.emplace_back(query, result);
    }

    return {rulesEval, numPasses, queryResults};
}

Relation Interpreter::evaluatePredicate(const ast::Predicate &pred) {
    // Get the relation associated with the name
    Relation result = database.getRelation(pred.name.id);

    // NOTE: This can be optimized to do it in less loops

    // Filter out by constant
    for (size_t i = 0; i < pred.params.size(); i++) {
        auto param = pred.params.at(i);
        if (param.isString()) {
            result = result.selectConstant(i, param.toString_().string_);
        }
    }

    // Gather all variablesIdx in a map
    multimap<string, size_t> variablesIdx;
    vector<string> variables;
    for (size_t i = 0; i < pred.params.size(); i++) {
        auto param = pred.params.at(i);
        if (param.isId()) {
            variablesIdx.insert(pair<string, size_t>(param.toId().id, i));
            if (find(variables.begin(), variables.end(), param.toId().id) == variables.end())
                variables.push_back(param.toId().id);
        }
    }

    vector<string> variableNames;
    vector<size_t> variableIdxs;

    // Iterate through each of the variablesIdx and filter out
    // if there is more than one occurrence in the map
    for (const string &variable: variables) {
        auto it = variablesIdx.equal_range(variable);
        auto firstVarName = it.first->first;
        auto firstIdx = it.first->second;

        // If there is more than one occurrence of the variable
        if (variablesIdx.count(variable) > 1) {


            for (auto i = ++it.first; i != it.second; i++) {
                result = result.selectCompare(firstIdx, i->second);
            }
        }

        variableNames.push_back(firstVarName);
        variableIdxs.push_back(firstIdx);
    }

    result = result.project(variableIdxs);
    result = result.rename(variableNames);

    return result;
}

vector<string> idListToStrings(const vector<ast::Id> &ids) {
    vector<string> result;
    for (const auto &id: ids) result.push_back(id.id);
    return result;
}

vector<string> stringsListToStrings(const vector<ast::String> &strings) {
    vector<string> result;
    for (const auto &string_: strings) result.push_back(string_.string_);
    return result;
}

vector<string> paramsListToParams(const vector<ast::Parameter> &params) {
    vector<string> result;
    for (const auto &param: params)
        if (param.isId()) result.push_back(param.toId().id);
        else result.push_back(param.toString_().string_);
    return result;
}

vector<string> makeHeader(const vector<ast::Id> &params) {
    vector<string> result;

    for (const auto &param: params) {
        result.push_back(param.id);
    }

    return result;
}
