#ifndef PROJECT_2_TUPLE_H
#define PROJECT_2_TUPLE_H

#include <string>
#include <utility>
#include <vector>

using namespace std;

class Tuple {
private:
    vector<string> values;

public:
    explicit Tuple(vector<string> values): values(std::move(values)) {}

    bool operator<(const Tuple &rhs) const {
        return values < rhs.values;
    }
};

#endif //PROJECT_2_TUPLE_H
