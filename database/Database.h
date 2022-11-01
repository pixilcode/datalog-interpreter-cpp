#ifndef PROJECT_2_DATABASE_H
#define PROJECT_2_DATABASE_H

#include <map>
#include <utility>
#include "Relation.h"

class Database {
private:
    map<string, Relation> relations;

public:
    explicit Database(map<string, Relation> relations): relations(std::move(relations)) {}
};


#endif //PROJECT_2_DATABASE_H
