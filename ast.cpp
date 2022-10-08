#include "ast.h"

string ast::paramsToString(vector<ast::Parameter> params) {
    ostringstream out;
    out << params[0].toString();
    for (int i = 1; i < params.size(); i++) {
        out << "," << params[i].toString();
    }
    return out.str();
}

string ast::stringsToString(vector<ast::String> strings) {
    ostringstream out;
    out << strings[0].toString();
    for (int i = 1; i < strings.size(); i++) {
        out << "," << strings[i].toString();
    }
    return out.str();
}

string ast::idsToString(vector<ast::Id> ids) {
    ostringstream out;
    out << ids[0].toString();
    for (int i = 1; i < ids.size(); i++) {
        out << "," << ids[i].toString();
    }
    return out.str();
}

string ast::predicatesToString(vector<ast::Predicate> predicates) {
    ostringstream out;
    out << predicates[0].toString();
    for (int i = 1; i < predicates.size(); i++) {
        out << "," << predicates[i].toString();
    }
    return out.str();
}

set<string> ast::getDomain(const vector<ast::Fact>& facts) {
    set<string> domain;
    for (const ast::Fact& fact : facts)
        for (const ast::String& string_ : fact.args)
            domain.insert(string_.toString());
    return domain;
}