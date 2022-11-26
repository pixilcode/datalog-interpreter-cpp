#ifndef PROJECT_2_INTERPRETER_H
#define PROJECT_2_INTERPRETER_H

#include <utility>

#include "ast.h"
#include "database/Database.h"

class Interpreter {
private:
    ast::Program program;
    Database database;

    Relation evaluatePredicate(const ast::Predicate &pred);

public:
    explicit Interpreter(ast::Program program, Database database = Database()) :
            program(std::move(program)),
            database(std::move(database)) {}

    tuple<
            vector<pair<ast::Rule, Relation>>,
            int,
            vector<pair<ast::Query, Relation>>
    > runQuery();
};

vector<string> idListToStrings(const vector<ast::Id> &ids);

vector<string> stringsListToStrings(const vector<ast::String> &strings);

vector<string> paramsListToParams(const vector<ast::Parameter> &params);

vector<string> makeHeader(const vector<ast::Id> &params);

#endif //PROJECT_2_INTERPRETER_H
