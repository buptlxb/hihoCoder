#include <iostream>
#include <vector>
#include <map>

using namespace std;

enum class Color{ WHITE, GRAY, BLACK };

struct Query;

struct Person {
    string name;
    Person *parent;
    Color color;
    vector<Person *> children;
    vector<Query *> queries;
private:
    static map<string, Person *> dict;
    Person (string n) : name(n), parent(nullptr), color(Color::WHITE) {}
public:
    static Person *get(string n) {
        if (dict.find(n) == dict.end())
            dict[n] = new Person(n);
        return dict[n];
    }
};

struct Query {
    Query(Person *p, int idx) : person(p), index(idx) {}
    Person *person;
    int index;
};

map<string, Person *> Person::dict;

Person *gray(Person *p)
{
    if (p->color == Color::GRAY)
        return p;
    return p->parent = gray(p->parent);
}

void solve(Person *root, vector<string> &res)
{
    root->color = Color::GRAY;
    for (auto query : root->queries) {
        if (query->person->color == Color::WHITE)
            continue;
        res[query->index] = gray(query->person)->name;
    }
    for (auto child : root->children)
        solve(child, res);
    root->color = Color::BLACK;
}

int main(void)
{
    int n;
    cin >> n;
    string a, b;
    Person *root = nullptr;
    for (int i = 0; i < n; ++i) {
        cin >> a >> b;
        Person *p = Person::get(a);
        Person *c = Person::get(b);
        p->children.push_back(c);
        c->parent = p;
        if (!root)
            root = p;
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        cin >> a >> b;
        Person *x = Person::get(a);
        Person *y = Person::get(b);
        x->queries.push_back(new Query(y, i));
        y->queries.push_back(new Query(x, i));
    }
    vector<string> res(m);
    solve(root, res);
    for (auto r : res)
        cout << r << "\n";
    return 0;
}
