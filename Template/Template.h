#pragma once
#include <iostream>
#include <tuple>
#include <utility>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <fstream>
#include <stdexcept>

using namespace std;

template <typename Tuple, size_t Index>
void print_tuple_impl(ostream& os, const Tuple& t) {
    if constexpr (Index > 0) {
        print_tuple_impl<Tuple, Index - 1>(os, t);
        os << ", ";
    }
    os << get<Index>(t);
}

template <typename... Args>
ostream& operator<<(ostream& os, const tuple<Args...>& t) {
    os << "(";
    if constexpr (sizeof...(Args) > 0) {
        print_tuple_impl<tuple<Args...>, sizeof...(Args) - 1>(os, t);
    }
    os << ")";
    return os;
}

vector<string> split(const string& line, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream stream(line);
    while (getline(stream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

template <typename... Args>
class CSVParser {
public:
    CSVParser(fstream& input, size_t skip_lines = 0, char column_delimiter = ',', char quote_char = '"')
        : input_stream(input), column_delimiter(column_delimiter), quote_char(quote_char) {
        skip_header(skip_lines);
    }

    // Итератор для CSV-парсера
    class Iteration {
    public:
        using iterator_category = input_iterator_tag;
        using value_type = tuple<Args...>;
        using difference_type = ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        Iteration(fstream* input = nullptr, char column_delimiter = ',', char quote_char = '"')
            : input_(input), column_delimiter_(column_delimiter), quote_char_(quote_char), end_(input == nullptr) {
            if (input_) ++(*this); // Чтение первой строки
        }

        Iteration& operator++() {
            if (input_ && getline(*input_, current_line_)) {
                current_tuple_ = parseLine(current_line_);
            }
            else {
                end_ = true;
            }
            return *this;
        }

        value_type operator*() const {
            return current_tuple_;
        }

        bool operator==(const Iteration& other) const {
            return end_ == other.end_;
        }

        bool operator!=(const Iteration& other) const {
            return !(*this == other);
        }

    private:
        fstream* input_;
        string current_line_;
        value_type current_tuple_;
        char column_delimiter_;
        char quote_char_;
        bool end_ = false;

        // Парсинг строки в кортеж
        value_type parseLine(const string& line) const {
            istringstream stream(line);
            return parseFields<Args...>(stream, column_delimiter_);
        }

        template <typename T, typename... Rest>
        static tuple<T, Rest...> parseFields(istream& stream, char column_delimiter_) {
            string field;
            getline(stream, field, column_delimiter_);
            T value = parseField<T>(field);
            if constexpr (sizeof...(Rest) == 0) {
                return make_tuple(value);
            }
            else {
                return tuple_cat(make_tuple(value), parseFields<Rest...>(stream, column_delimiter_));
            }
        }

        template <typename T>
        static T parseField(const string& field) {
            istringstream stream(field);
            T value;
            stream >> value;
            return value;
        }
    };

    Iteration begin() {
        return Iteration(&input_stream, column_delimiter, quote_char);
    }

    Iteration end() {
        return Iteration();
    }

private:
    fstream& input_stream;
    char column_delimiter;
    char quote_char;

    void skip_header(size_t skip_lines) {
        string line;
        for (size_t i = 0; i < skip_lines && getline(input_stream, line); ++i);
    }
};
