#include "BitArray.h"


int main() {

    BitArray bit_array(10);

    bit_array.set(2);
    string str = bit_array.to_string();
    cout << str << endl;
    return 0;
}
