#include "Interpreter.h"

void Interpreter::run() {
    for (const auto& scheme : program.schemes) {
        // Get the vector of attributes
        vector<string> attributes = idListToStrings(scheme.params);

        // Create the relation and add it to the database
        Relation relation = Relation(scheme.name.id, Header(attributes), {});
        database.addRelation(scheme.name.id, relation);
    }

    for (const auto& fact : program.facts) {
        // Make a tuple from the fact
        Tuple tuple = Tuple(stringsListToStrings(fact.args));

        // Add the fact to the relation
        database.addTuple(fact.name.id, tuple);
    }

    /*
    for (const auto& rule : program.rules) {

    }
    */

    for (const auto& query : program.queries) {

    }
}

vector<string> idListToStrings(const vector<ast::Id>& ids) {
    vector<string> result;
    for (const auto& id : ids) result.push_back(id.id);
    return result;
}

vector<string> stringsListToStrings(const vector<ast::String>& strings) {
    vector<string> result;
    for (const auto& string_ : strings) result.push_back(string_.string_);
    return result;
}

vector<string> paramsListToParams(const vector<ast::Parameter>& params) {
    vector<string> result;
    for (const auto& param : params)
        if (param.isId()) result.push_back(param.toId().id);
        else result.push_back(param.toString_().string_);
    return result;
}
