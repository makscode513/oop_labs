#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <set>

using namespace std;

enum { width = 50 };
enum { height = 50 };

struct life_input {
    ifstream input;
    int iteration;
    ofstream output;
};

class Universe {
public:
    Universe();

    void create_universe(struct life_input& params);

    void save_universe(struct life_input& params);

    void step_universe(int iterations = 1);

    void parse_rule(set<int>& birth, set<int>& survival);

    void print_universe();

    Universe(const Universe& universe);

    ~Universe();

private:
    vector<vector<int>> grid;
    string rule_universe;
    string universe_name;

    int count_heighbors(int x, int y) const;
};

void set_game(struct life_input* params, int argc, char* argv[]);

void print_help();

void game_offline(struct life_input& params);

void game_online(struct life_input& params);

void start_game(struct life_input& params, int argc);
