#ifndef PROJECT_2_INTERPRETER_H
#define PROJECT_2_INTERPRETER_H

#include <utility>

#include "ast.h"
#include "database/Database.h"

class Interpreter {
private:
    ast::Program program;
    Database database;

public:
    Interpreter(ast::Program program, Database database):
            program(std::move(program)),
            database(std::move(database)) {}

    vector<pair<ast::Query, Relation>> runQuery();
    Relation evaluatePredicate(const ast::Predicate& pred);
};

vector<string> idListToStrings(const vector<ast::Id>& ids);
vector<string> stringsListToStrings(const vector<ast::String>& strings);
vector<string> paramsListToParams(const vector<ast::Parameter>& params);

#endif //PROJECT_2_INTERPRETER_H
