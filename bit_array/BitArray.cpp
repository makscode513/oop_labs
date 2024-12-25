#include "BitArray.h"

BitArray::BitArray() {
    bit_array = nullptr;
    count_bits = 0;
    num_elements = 0;
}

BitArray::~BitArray() { // pab test
    delete[] bit_array;
}

BitArray::BitArray(int num_bits, unsigned long value) { // pab test
    int num_elements = num_bits / bits_in_long + ((num_bits % bits_in_long == 0) ? 0 : 1);
    bit_array = new unsigned long[num_elements];
    count_bits = num_bits;
    this->num_elements = num_elements;
    for (int i = 0; i < num_elements; i++) {
        bit_array[i] = value;
    }
}

BitArray::BitArray(const BitArray& b) { // pab test
    int num_elements = b.num_elements;
    this->bit_array = new unsigned long[num_elements];
    for (int i = 0; i < num_elements; i++) {
        this->bit_array[i] = b.bit_array[i];
    }
    this->count_bits = b.count_bits;
    this->num_elements = num_elements;
}

void BitArray::swap(BitArray& b) { // pab test
    BitArray second_array = *this;
    *this = b;
    b = second_array;
}

BitArray& BitArray::operator=(const BitArray& b) { // pab test
    if (this->bit_array != nullptr) {
        delete[] this->bit_array;
    }
    int num_elements = b.num_elements;
    this->bit_array = new unsigned long[num_elements];
    for (int i = 0; i < num_elements; i++) {
        this->bit_array[i] = b.bit_array[i];
    }
    this->count_bits = b.count_bits;
    this->num_elements = num_elements;
    return *this;
}

void BitArray::resize(int num_bits, bool value = false) { // pab test
    int num_elements = num_bits / bits_in_long + ((num_bits % bits_in_long == 0) ? 0 : 1);
    unsigned long* array = new unsigned long[num_elements];
    if (num_bits > count_bits) {
        int i = 0;
        for (; i < this->num_elements; i++) {
            array[i] = this->bit_array[i];
        }
        if (count_bits % bits_in_long != 0) {
            unsigned long mask = 1UL;
            int count_shifts = bits_in_long - (count_bits % bits_in_long) - 1;
            for (int i = 0; i < count_shifts; i++) {
                mask <<= 1;
                mask |= 1UL;
            }
            if (value) {
                array[this->num_elements - 1] |= mask;
            }
            else {
                mask = ~mask;
                array[this->num_elements - 1] &= mask;
            }
        }
        if (value) {
            for (; i < num_elements; i++) {
                array[i] = ~0;
            }
        }
    }
    else {
        int last_index = 0;
        for (int i = 0; i < num_elements; i++) {
            array[i] = this->bit_array[i];
            last_index = i;
        }
        if (num_bits % bits_in_long != 0) {
            unsigned long mask = 1UL;
            int count_shifts = bits_in_long - (num_bits % bits_in_long) - 1;
            for (int i = 0; i < count_shifts; i++) {
                mask <<= 1;
                mask |= 1UL;
            }
            mask = ~mask;
            array[last_index] &= mask;
        }
    }
    delete[] this->bit_array;
    this->bit_array = array;
    this->count_bits = num_bits;
    this->num_elements = num_elements;
}

void BitArray::clear() { // pab test
    for (int i = 0; i < num_elements; i++) {
        bit_array[i] = 0;
    }
    num_elements = 0;
    count_bits = 0;
}

void BitArray::push_back(bool bit) { // pab test
    if ((count_bits + 1) % bits_in_long == 1) {
        resize(count_bits + 1, false);
        set(count_bits - 1, bit);
    }
    else {
        set(count_bits, bit);
        count_bits++;
    }
}

BitArray& BitArray::operator&=(const BitArray& b) { // pab test
        //if (this->num_elements != b.num_elements) {
        //    return;
        //}
    for (int i = 0; i < num_elements; i++) {
        this->bit_array[i] &= b.bit_array[i];
    }
    return *this;
}

BitArray& BitArray::operator|=(const BitArray& b) { // pab test
        //if (this->num_elements != b.num_elements) {
        //    return;
        //}
    for (int i = 0; i < num_elements; i++) {
        this->bit_array[i] |= b.bit_array[i];
    }
    return *this;
}

BitArray& BitArray::operator^=(const BitArray& b) { // pab test
        //if (this->num_elements != b.num_elements) {
        //    return;
        //}
    for (int i = 0; i < num_elements; i++) {
        this->bit_array[i] ^= b.bit_array[i];
    }
    return *this;
}

BitArray& BitArray::operator<<=(int n) { // pab test
    int count_last_bits = 0;
    int second_num_elements = this->num_elements, second_count_bits = this->count_bits;
    for (int i = 0; i < n; i++) {
        int b = second_count_bits % bits_in_long;
        count_last_bits = (b == 0) ? bits_in_long : b;

        for (int j = 0; j < count_last_bits && j < n; j++) {
            for (int z = 0; z < second_num_elements - 1; z++) {
                bit_array[z] <<= 1;
                bool bit = (left_one_bit & bit_array[z + 1]) > 0 ? true : false;
                if (bit) {
                    bit_array[z] |= 1UL;
                }
                else {
                    bit_array[z] &= ~1UL;
                }
            }
            bit_array[second_num_elements - 1] <<= 1;
        }
        i += count_last_bits;
        second_count_bits -= count_last_bits;
        second_num_elements--;

    }
    return *this;
}

BitArray& BitArray::operator>>=(int n) { // pab test
    int count_last_bits = 0;
    int second_count_bits = this->count_bits;
    int b = second_count_bits % bits_in_long;
    count_last_bits = (b == 0) ? bits_in_long : b;
    unsigned long mask = 1UL;
    for (int i = 0; i < count_last_bits; i++) {
        mask <<= 1;
        mask |= 1UL;
    }
    mask <<= (bits_in_long - count_last_bits);
    for (int i = 0; i < n; i++) {
        bit_array[num_elements - 1] >>= 1;
        bit_array[num_elements - 1] &= mask;
        if (num_elements > 1) {
            bool bit = (1UL & bit_array[num_elements - 2]) > 0 ? true : false;
            if (bit) {
                bit_array[num_elements - 1] |= left_one_bit;
            }
            for (int i = num_elements - 2; i >= 0; i--) {
                bit_array[i] >>= 1;
                if (i - 1 >= 0) {
                    bool bit = (1UL & bit_array[i - 1]) > 0 ? true : false;
                    if (bit) {
                        bit_array[i] |= left_one_bit;
                    }
                }
            }
        }
    }
    return *this;
}

BitArray BitArray::operator<<(int n) { // pab test
    BitArray result = *this;
    result <<= n;
    return result;
}

BitArray BitArray::operator>>(int n) { // pab test
    BitArray result = *this;
    result >>= n;
    return result;
}

BitArray& BitArray::set(int n, bool val) { // pab test
    int index = n / bits_in_long;
    if (index >= num_elements) {
        return *this;
    }
    if (val) {
        bit_array[index] |= 1UL << (bits_in_long - 1 - (n % bits_in_long));
    }
    else {
        bit_array[index] &= ~(1UL << (bits_in_long - 1 - (n % bits_in_long)));
    }
    return *this;
}

BitArray& BitArray::set() { // pab test
    for (int i = 0; i < num_elements; i++) {
        bit_array[i] = ~0;
    }
    return *this;
}

BitArray& BitArray::reset(int n) { // pab test
    return set(n, false);
}

BitArray& BitArray::reset() { // pab test
    for (int i = 0; i < num_elements; i++) {
        bit_array[i] = 0;
    }
    return *this;
}


bool BitArray::any() const { // pab test
    for (int i = 0; i < num_elements; i++) {
        if (bit_array[i] > 0) {
            return true;
        }
    }
    return false;
}

bool BitArray::none() const { //pab test
    return !any();
}


BitArray BitArray::operator~() const { // pab test
    for (int i = 0; i < num_elements; i++) {
        bit_array[i] = ~(bit_array[i]);
    }
    return *this;
}

int BitArray::count() const { // pab test
    int count = 0, index_bit = 0;
    unsigned long element = 0;
    for (int i = 0; i < num_elements; i++) {
        element = bit_array[i];
        while (element) {
            count += (element & left_one_bit) > 0 ? 1 : 0;
            element <<= 1;
            index_bit++;
            if (index_bit >= count_bits) {
                break;
            }
        }
    }
    return count;
}

bool BitArray::operator[](int i) const { // pab test
    int index = i / bits_in_long;
    return (bit_array[index] >> (bits_in_long - 1 - (i % bits_in_long))) & 1UL;
}

int BitArray::size() const { // pab test
    return count_bits;
}

bool BitArray::empty() const { // pab test
    return !(count_bits > 0);
}

string BitArray::to_string() const { // pab test
    string string_bits;
    string_bits.reserve(this->count_bits);
    int bits = 0;
    for (int i = 0; i < num_elements; i++) {
        unsigned long element = bit_array[i];
        for (int i = 0; i < bits_in_long; i++) {
            string_bits += (left_one_bit & element) > 0 ? '1' : '0';
            element <<= 1;
            bits++;
            if (bits >= this->count_bits) {
                return string_bits;
            }
        }
    }
}

bool operator==(const BitArray& a, const BitArray& b) { // pab test
    if (a.size() != b.size()) {
        return false;
    }
    for (int i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

bool operator!=(const BitArray& a, const BitArray& b) { // pab test
    return !(a == b);
}

BitArray operator&(const BitArray& b1, const BitArray& b2) { // pab test
    BitArray result = b1;
    result &= b2;
    return result;
}

BitArray operator|(const BitArray& b1, const BitArray& b2) { // pab test
    BitArray result = b1;
    result |= b2;
    return result;
}

BitArray operator^(const BitArray& b1, const BitArray& b2) { // pab test
    BitArray result = b1;
    result ^= b2;
    return result;
}
