#pragma once
#include <iostream>
#include <string>
using namespace std;

enum { bits_in_long = sizeof(unsigned long) * 8 };
enum { left_one_bit = 1UL << (bits_in_long - 1) };


class BitArray
{
public:
    BitArray();
    ~BitArray();
    BitArray(int num_bits, unsigned long value = 0);

    BitArray(const BitArray& b);

    void swap(BitArray& b);

    BitArray& operator=(const BitArray& b);

    void resize(int num_bits, bool value);

    void clear();

    void push_back(bool bit);

    BitArray& operator&=(const BitArray& b);

    BitArray& operator|=(const BitArray& b);

    BitArray& operator^=(const BitArray& b);

    BitArray& operator<<=(int n);

    BitArray& operator>>=(int n);

    BitArray operator<<(int n);

    BitArray operator>>(int n);

    BitArray& set(int n, bool val = true);

    BitArray& set();

    BitArray& reset(int n);

    BitArray& reset();


    bool any() const;

    bool none() const;

    BitArray operator~() const;

    int count() const;

    bool operator[](int i) const;
    int size() const;

    bool empty() const;

    string to_string() const;

private:
    unsigned long* bit_array;
    int count_bits;
    int num_elements;
};

bool operator==(const BitArray& a, const BitArray& b);

bool operator!=(const BitArray& a, const BitArray& b);

BitArray operator&(const BitArray& b1, const BitArray& b2);

BitArray operator|(const BitArray& b1, const BitArray& b2);

BitArray operator^(const BitArray& b1, const BitArray& b2);
