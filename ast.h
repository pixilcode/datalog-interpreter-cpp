#ifndef PROJECT_2_AST_H
#define PROJECT_2_AST_H

#include <utility>
#include <vector>
#include <sstream>
#include <string>
#include <set>
#include <variant>

using namespace std;

namespace ast {
    // Literals
    struct Id {
        string id;
        
        explicit Id(string id): id(std::move(id)) {}

        [[nodiscard]] string toString() const { return id; }
    };

    struct String {
        string string_;

        explicit String(string string_): string_(std::move(string_)) {}
        [[nodiscard]] string toString() const { return string_; }
    };

    struct Parameter {
        variant<Id, String> param;

        explicit Parameter(Id id): param(id) {}
        explicit Parameter(String string_): param(string_) {}

        [[nodiscard]] bool isId() const { return holds_alternative<Id>(param); }
        [[nodiscard]] Id toId() const { return get<Id>(param); }

        [[nodiscard]] bool isString() const { return holds_alternative<String>(param); }
        [[nodiscard]] String toString_() const { return get<String>(param); }

        [[nodiscard]] string toString() const { return (isId()) ? toId().id : toString_().string_; }
    };

    string paramsToString(vector<Parameter> params);
    string stringsToString(vector<String> strings);
    string idsToString(vector<Id> ids);

    // PREDICATES
    struct HeadPredicate {
        Id name;
        vector<Id> params;

        HeadPredicate(Id name, vector<Id> params):
                name(std::move(name)),
                params(std::move(params)) {}

        [[nodiscard]] string toString() const { return name.toString() + "(" + idsToString(params) + ")"; }
    };

    struct Predicate {
        Id name;
        vector<Parameter> params;

        Predicate(Id name, vector<Parameter> params):
                name(std::move(name)),
                params(std::move(params)) {}

        [[nodiscard]] string toString() const { return name.toString() + "(" + paramsToString(params) + ")"; }
    };

    string predicatesToString(vector<Predicate> predicates);

    // SECTIONS
    struct Scheme {
        Id name;
        vector<Id> params;

        Scheme(Id name, vector<Id> params):
                name(std::move(name)),
                params(std::move(params)) {}

        [[nodiscard]] string toString() const { return "  " + name.toString() + "(" + idsToString(params) + ")"; }
    };

    struct Fact {
        Id name;
        vector<String> args;

        Fact(Id name, vector<String> args):
                name(std::move(name)),
                args(std::move(args)) {}

        [[nodiscard]] string toString() const { return "  " + name.toString() + "(" + stringsToString(args) + ")."; }
    };

    struct Rule {
        HeadPredicate head;
        vector<Predicate> predicates;

        Rule(HeadPredicate head, vector<Predicate> predicates):
                head(std::move(head)),
                predicates(std::move(predicates)) {}

        [[nodiscard]] string toString() const { return "  " + head.toString() + " :- " + predicatesToString(predicates) + "."; }
    };

    struct Query {
        Predicate pred;

        explicit Query(Predicate pred): pred(std::move(pred)) {}

        [[nodiscard]] string toString() const { return "  " + pred.toString() + "?"; }
    };

    set<string> getDomain(const vector<Fact>& facts);

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

        [[nodiscard]] string toString() const {
            ostringstream out;
            out << "Schemes(" << schemes.size() << "):" << endl;
            for(const Scheme& scheme : schemes)
                out << scheme.toString() << endl;

            out << "Facts(" << facts.size() << "):" << endl;
            for(const Fact& fact : facts)
                out << fact.toString() << endl;

            out << "Rules(" << rules.size() << "):" << endl;
            for(const Rule& rule : rules)
                out << rule.toString() << endl;

            out << "Queries(" << queries.size() << "):" << endl;
            for(const Query& query : queries)
                out << query.toString() << endl;

            auto domain = getDomain(facts);
            out << "Domain(" << domain.size() << "):" << endl;
            for(const string& input : domain)
                out << "  " << input << endl;

            return out.str();
        }
    };
}

#endif //PROJECT_2_AST_H
