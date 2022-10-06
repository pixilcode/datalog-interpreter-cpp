#ifndef PROJECT_2_AST_H
#define PROJECT_2_AST_H

#include <utility>
#include <vector>
#include <string>
#include <variant>

using namespace std;

namespace ast {
    // Literals
    struct Id {
        string id;
        
        explicit Id(string id): id(std::move(id)) {}
    };

    struct String {
        string string_;

        explicit String(string string_): string_(std::move(string_)) {}
    };

    struct Parameter {
        variant<Id, String> param;

        explicit Parameter(Id id): param(id) {}
        explicit Parameter(String string_): param(string_) {}

        [[nodiscard]] bool isId() const { return holds_alternative<Id>(param); }
        Id toId() { return get<Id>(param); }

        [[nodiscard]] bool isString() const { return holds_alternative<String>(param); }
        String toString() { return get<String>(param); }
    };

    // PREDICATES
    struct HeadPredicate {
        Id name;
        vector<Id> params;

        HeadPredicate(Id name, vector<Id> params):
                name(std::move(name)),
                params(std::move(params)) {}
    };

    struct Predicate {
        Id name;
        vector<Parameter> params;

        Predicate(Id name, vector<Parameter> params):
                name(std::move(name)),
                params(std::move(params)) {}
    };

    // SECTIONS
    struct Scheme {
        Id name;
        vector<Id> params;

        Scheme(Id name, vector<Id> params):
                name(std::move(name)),
                params(std::move(params)) {}
    };

    struct Fact {
        Id name;
        vector<String> args;

        Fact(Id name, vector<String> args):
                name(std::move(name)),
                args(std::move(args)) {}

    };

    struct Rule {
        HeadPredicate head;
        vector<Predicate> predicates;

        Rule(HeadPredicate head, vector<Predicate> predicates):
                head(std::move(head)),
                predicates(std::move(predicates)) {}
    };

    struct Query {
        Predicate pred;

        explicit Query(Predicate pred): pred(std::move(pred)) {}
    };

    // PROGRAM
    struct Program {
        vector<Scheme> schemes;
        vector<Fact> facts;
        vector<Rule> rules;
        vector<Query> queries;

        Program(vector<Scheme> schemes, vector<Fact> facts, vector<Rule> rules, vector<Query> queries):
                schemes(std::move(schemes)),
                facts(std::move(facts)),
                rules(std::move(rules)),
                queries(std::move(queries)) {}
    };
}

#endif //PROJECT_2_AST_H
