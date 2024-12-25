#include "Game_of_life.h"

Universe::Universe() {
    vector<vector<int>> grid(width, vector<int>(height, 0));
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            grid[i][j] = 0;
        }
    }
    this->grid = grid;
}

void Universe::create_universe(struct life_input& params) {
    string line;
    getline(params.input, line);
    while (getline(params.input, line)) {
        if (line[0] == '#') {
            if (line[1] == 'N') {
                universe_name = line.substr(3);
            }
            if (line[1] == 'R') {
                rule_universe = line.substr(3);
            }
        }
        else {
            istringstream iss(line);
            int x, y;
            if (iss >> x >> y) {
                grid[x][y] = 1;
            }
        }
    }
    params.input.close();
}

void Universe::save_universe(struct life_input& params) {
    string version = "#Life 1.06";
    params.output << version << endl;
    params.output << "#N" + universe_name << endl;
    params.output << "#R" + rule_universe << endl;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (grid[i][j] == 1) {
                params.output << i + " " + j << endl;
            }
        }
    }
    params.output.close();
}

void Universe::step_universe(int iterations) {
    set<int> birth, survival;
    parse_rule(birth, survival);


    for (int z = 0; z < iterations; z++) {
        vector<vector<int>> newgrid = grid;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                int neighbors = count_heighbors(i, j);
                if (grid[i][j] == 1) { // Живая клетка
                    newgrid[i][j] = survival.count(neighbors) ? 1 : 0;
                }
                else {
                    newgrid[i][j] = birth.count(neighbors) ? 1 : 0;
                }
            }
        }
        grid = newgrid;
    }
}

void Universe::parse_rule(set<int>& birth, set<int>& survival) {
    birth.clear();
    survival.clear();

    int b_pos = rule_universe.find('B');
    int s_pos = rule_universe.find('S');

    for (size_t i = b_pos + 1; i < s_pos; ++i) {
        if (isdigit(rule_universe[i])) {
            birth.insert(rule_universe[i] - '0');
        }
    }

    for (size_t i = s_pos + 1; i < rule_universe.size(); ++i) {
        if (isdigit(rule_universe[i])) {
            survival.insert(rule_universe[i] - '0');
        }
    }
}

void Universe::print_universe() {
    cout << universe_name << endl;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            cout << (grid[i][j] == 1 ? '0' : '.');
        }
        cout << endl;
    }
}

Universe::Universe(const Universe& universe) {
    for (auto& row : grid) {
        row.clear();
    }
    grid.clear();
    this->grid = universe.grid;
    this->rule_universe = universe.rule_universe;
    this->universe_name = universe.universe_name;
}

Universe::~Universe() {
    for (auto& row : grid) {
        row.clear();
    }
    grid.clear();
}

int Universe::count_heighbors(int x, int y) const {
    int count = 0;
    int dx[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    int dy[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

    for (int i = 0; i < 8; i++) {
        int nx = (x + dx[i] + height) % height;
        int ny = (y + dy[i] + width) % width;
        count += grid[nx][ny];
    }
    return count;
}

void set_game(struct life_input* params, int argc, string* argv) {
    string param = argv[1];
    if (param.find(".txt") != 0) {
        params->input.open(param);
        if (!params->input) {
            cerr << "Неудалось открыть файл:" << param << endl;
            return;
        }
        param = argv[2];
    }
    if (param.find("--iterations=") == 0) {
        params->iteration = atoi(param.substr(13).c_str());
        param = argv[3];
    }
    if (param.find("--output=") == 0) {
        param = param.substr(9);
        params->output.open(param);
    }
}

void set_game(struct life_input* params, int argc, char* argv[]) {
    string param = argv[1];
    if (param.find(".txt") != 0) {
        params->input.open(param);
        if (!params->input) {
            cerr << "Неудалось открыть файл:" << param << endl;
            return;
        }
        param = argv[2];
    }
    if (param.find("--iterations=") == 0) {
        params->iteration = atoi(param.substr(13).c_str());
        param = argv[3];
    }
    if (param.find("--output=") == 0) {
        param = param.substr(9);
        params->output.open(param);
    }
}

void print_help() {
    cout << "Команды:" << endl;
    cout << "dump <filename>   - Сохраняет вселенную в файл" << endl;
    cout << "tick <n=1>        - Расчитывает n итераций и выводит на консоль" << endl;
    cout << "exit              - Выход из игры" << endl;
}

void game_offline(struct life_input& params) {
    Universe universe;
    universe.create_universe(params);
    universe.print_universe();
    universe.step_universe(params.iteration);
    universe.print_universe();
    universe.save_universe(params);
}

void game_online(struct life_input& params) {
    Universe universe;
    universe.create_universe(params);
    cout << "Game of Life started. Type 'help' for a list of commands." << endl;
    while (true) {
        string command;
        getline(cin, command);

        istringstream iss(command);
        string cmd;
        iss >> cmd;
        if (cmd == "help") {
            print_help();
        }
        if (cmd == "tick") {
            int n = 1;
            iss >> n;
            universe.step_universe(n);
            universe.print_universe();
        }
        if (cmd == "dump") {
            universe.save_universe(params);
        }
        if (cmd == "exit") {
            universe.save_universe(params);
            break;
        }
        else {
            cout << "Неверная команда" << endl;
        }
    }
}

void start_game(struct life_input& params, int argc) {
    if (argc == 1) {
        game_online(params);
    }
    else {
        game_offline(params);
    }

}
