#include "Interpreter.h"
#include "Graph.h"

#include <algorithm>
#include <iostream>

typedef size_t Id;

vector<pair<ast::Query, Relation>> Interpreter::runQuery() {
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

    vector<Id> range;

    // Find the producers
    map<string, set<Id>> produces;
    for (Id i = 0; i < program.rules.size(); i++) {
        const auto &produce = program.rules.at(i).head.name.id;
        produces.try_emplace(produce, set<Id>());
        produces.at(produce).insert(i);

        // Add to the range
        range.push_back(i);
    }

    // Add an edge for each dependency (consumer depends on producer, c -> p)
    set<pair<Id, Id>> edges;
    for (Id i = 0; i < program.rules.size(); i++) {
        for (const auto &pred: program.rules.at(i).predicates) {
            if (produces.find(pred.name.id) == produces.end()) continue;
            for (const auto &producer: produces.at(pred.name.id)) {
                edges.insert({i, producer});
            }
        }
    }

    Graph depGraph(set<Id>(range.begin(), range.end()), edges);

    // Print out dependency graph
    cout << "Dependency Graph" << endl;
    cout << depGraph.toString() << endl;

    Graph inverseGraph = depGraph.reverse();
    vector<Id> postorder = inverseGraph.postorder(range);
    vector<Id> reversed(postorder);
    reverse(reversed.begin(), reversed.end());
    vector<set<Id>> scc = depGraph.scc(reversed);

    cout << "Rule Evaluation" << endl;
    for (const auto &s: scc) {
        {
            cout << "SCC: ";

            size_t i = 0;
            for (const auto &id: s) {
                cout << "R" << id;
                if (i++ < s.size() - 1) cout << ",";
            }
            cout << endl;
        }

        vector<ast::Rule> rules;
        Id only;
        for (const auto &id: s) {
            only = id;
            rules.push_back(program.rules.at(id));
        }

        bool trivial = rules.size() == 1 && !depGraph.hasIdLoop(only);

        bool noAddition;
        int numPasses = 0;
        vector<pair<ast::Rule, Relation>> rulesEval;
        do {
            noAddition = true;
            ++numPasses;
            for (const auto &rule: rules) {
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
                auto [finalRelation, newTuples] = oldRelation.union_(renameResult);
                database.addRelation(rule.head.name.id, finalRelation);

                rulesEval.emplace_back(rule, newTuples);
                noAddition = noAddition && newTuples.empty();
            }
        } while (!noAddition && !trivial);

        for (const auto &[rule, relation]: rulesEval) {
            cout << rule.toString(false) << endl;

            auto header = relation.getHeader();
            auto tuples = relation.getTuples();
            for (const auto &tuple: tuples) {
                auto values = tuple.getValues();

                cout << "  ";
                for (size_t i = 0; i < values.size(); i++) {
                    if (i > 0) cout << ", ";
                    cout << header.getAttributes().at(i);
                    cout << "=";
                    cout << values.at(i);
                }
                cout << endl;
            }
        }

        {
            cout << numPasses << " passes: ";

            size_t i = 0;
            for (const auto &id: s) {
                cout << "R" << id;
                if (i++ < s.size() - 1) cout << ",";
            }
            cout << endl;
        }
    }

    vector<pair<ast::Query, Relation>> queryResults;

    for (const auto &query: program.queries) {
        // Evaluate the predicate
        Relation result = evaluatePredicate(query.pred);

        queryResults.emplace_back(query, result);
    }

    return queryResults;
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
