#include "pch.h"
#include "Head.h"
//#include "C:\Users\макс\source\repos\bitarray\bitarray\bitarray_solution.cpp"

TEST(BitArrayTest, IndexOperator) {
    BitArray bitArray(5, 0b10101000000000000000000000000000);
    EXPECT_TRUE(bitArray[0]);
    EXPECT_FALSE(bitArray[1]);
    EXPECT_TRUE(bitArray[2]);
}

TEST(BitArrayTest, ConstructorAndSize) {
    BitArray bitArray(10, ~0);
    EXPECT_EQ(bitArray.size(), 10);
    EXPECT_TRUE(bitArray[2]);
}

TEST(BitArrayTest, Constructor) {
    BitArray bitArray;
    EXPECT_EQ(bitArray.size(), 0);
}

TEST(BitArrayTest, CopyConstructor) {
    BitArray bitArray(10, 1UL);
    BitArray copy(bitArray);
    EXPECT_EQ(copy.size(), bitArray.size());
    EXPECT_EQ(copy[0], bitArray[0]);
}

TEST(BitArrayTest, AssignmentOperator) {
    BitArray bitArray(10, 1UL);
    BitArray copyArray = bitArray;
    EXPECT_EQ(copyArray.size(), bitArray.size());
    EXPECT_EQ(copyArray[0], bitArray[0]);
}

TEST(BitArrayTest, SwapMethod) {
    BitArray array1(10, ~0);
    BitArray array2(10);
    array1.swap(array2);
    EXPECT_FALSE(array1[0]);
    EXPECT_TRUE(array2[0]);
}

TEST(BitArrayTest, EmptyMethod) {
    BitArray bitArray(5, 0b10101);
    EXPECT_FALSE(bitArray.empty());
}

TEST(BitArrayTest, ClearMethod) {
    BitArray bitArray(10, 1UL);
    bitArray.clear();
    EXPECT_EQ(bitArray.size(), 0);
    EXPECT_TRUE(bitArray.empty());
}

TEST(BitArrayTest, PushBackMethod) {
    BitArray bitArray(3);
    bitArray.push_back(true);
    EXPECT_EQ(bitArray.size(), 4);
    EXPECT_TRUE(bitArray[3]);
    BitArray bitArray1(sizeof(unsigned long) * 8);
    bitArray1.push_back(true);
    EXPECT_EQ(bitArray1.size(), 33);
    EXPECT_TRUE(bitArray1[32]);
}

TEST(BitArrayTest, CountMethod) {
    BitArray bitArray(5, 0b10111000000000000000000000000000);
    EXPECT_EQ(bitArray.count(), 4);
}

TEST(BitArrayTest, SetMethods) {
    BitArray bitArray(5, 0);
    bitArray.set(2);
    EXPECT_TRUE(bitArray[2]);
    bitArray.set();
    EXPECT_EQ(bitArray.count(), 5);
}

TEST(BitArrayTest, AnyMethod) {
    BitArray bitArray(5);
    EXPECT_FALSE(bitArray.any());
    bitArray.set(3);
    EXPECT_TRUE(bitArray.any());
    bitArray.set(2345);
    EXPECT_TRUE(bitArray.any());
}

TEST(BitArrayTest, NoneMethod) {
    BitArray bitArray(5);
    EXPECT_TRUE(bitArray.none());
    bitArray.set(3);
    EXPECT_FALSE(bitArray.none());
}

TEST(BitArrayTest, ResetMethods) {
    BitArray bitArray(5);
    bitArray.set();
    bitArray.reset(0);
    EXPECT_FALSE(bitArray[0]);
    bitArray.reset();
    EXPECT_FALSE(bitArray.any());
}

TEST(BitArrayTest, ToStringMethod) {
    BitArray bitArray(5, 0b10101000000000000000000000000000);
    EXPECT_EQ(bitArray.to_string(), "10101");
}

TEST(BitArrayTest, BitwiseAnd) {
    BitArray array1(5, 0b01010);
    BitArray array2(5, 0b10101);
    array1 &= array2;
    EXPECT_EQ(array1.to_string(), "00000");
}

TEST(BitArrayTest, BitwiseOr) {
    BitArray array1(5, 0b10101000000000000000000000000000);
    BitArray array2(5, 0b01010000000000000000000000000000);
    array1 |= array2;
    EXPECT_EQ(array1.to_string(), "11111");
}

TEST(BitArrayTest, BitwiseXor) {
    BitArray array1(5, 0b11011000000000000000000000000000);
    BitArray array2(5, 0b10101000000000000000000000000000);
    array1 ^= array2;
    EXPECT_EQ(array1.to_string(), "01110");
}

TEST(BitArrayTest, BitwiseNot) {
    BitArray bitArray(5, 0b10101000000000000000000000000000);
    ~bitArray;
    EXPECT_EQ(bitArray.to_string(), "01010");
}

TEST(BitArrayTest, EqualityOperator) {
    BitArray array1(5, 0b10101000000000000000000000000000);
    BitArray array2(5, 0b10101000000000000000000000000000);
    BitArray array3(5, 0b11000000000000000000000000000000);
    BitArray array4(6, 0b11000000000000000000000000000000);
    EXPECT_TRUE(array1 == array2);
    EXPECT_FALSE(array1 == array3);
    EXPECT_TRUE(array1 != array3);
    EXPECT_FALSE(array1 == array4);
}

TEST(BitArrayTest, BitwiseAndOp) {
    BitArray array1(5, 0b01010);
    BitArray array2(5, 0b10101);
    BitArray array3 = array1 & array2;
    EXPECT_EQ(array3.to_string(), "00000");
}

TEST(BitArrayTest, BitwiseOrOp) {
    BitArray array1(5, 0b01010000000000000000000000000000);
    BitArray array2(5, 0b10101000000000000000000000000000);
    BitArray array3 = array1 | array2;
    EXPECT_EQ(array3.to_string(), "11111");
}

TEST(BitArrayTest, BitwiseXorOp) {
    BitArray array1(5, 0b11011000000000000000000000000000);
    BitArray array2(5, 0b10101000000000000000000000000000);
    BitArray array3 = array1 ^ array2;
    EXPECT_EQ(array3.to_string(), "01110");
}

TEST(BitArrayTest, LeftShift) {
    BitArray bitArray(40, 0b10111110000000000000000000000000);
    bitArray <<= 1;
    EXPECT_EQ(bitArray.to_string(), "0111110000000000000000000000000101111100");
    BitArray array = bitArray << 1;
    EXPECT_EQ(array.to_string(), "1111100000000000000000000000001011111000");
}

TEST(BitArrayTest, RightShift) {
    BitArray bitArray(40, 0b00000000000000000000000000001111);
    bitArray >>= 1;
    EXPECT_EQ(bitArray.to_string(), "0000000000000000000000000000011110000000");
    BitArray array = bitArray >> 1;
    EXPECT_EQ(array.to_string(), "0000000000000000000000000000001111000000");

    BitArray bitArray2(200, ~0);
    bitArray2 >>= 1;
    EXPECT_EQ(bitArray2.count(), 199);

    BitArray bitArray1(5, 0b00001);
    bitArray1 >>= 2;
    EXPECT_EQ(bitArray1.to_string(), "00000");
    BitArray array1(5);
    EXPECT_TRUE(array1 == bitArray1);
}

TEST(BitArrayTest, ResizeMethod) {
    BitArray bitArray(5, ~0);
    bitArray.resize(10, false);
    EXPECT_EQ(bitArray.size(), 10);
    EXPECT_EQ(bitArray.to_string(), "1111100000");
    EXPECT_FALSE(bitArray[6]);
    bitArray.resize(2, false);
    EXPECT_EQ(bitArray.size(), 2);
    bitArray.resize(10, true);
    EXPECT_EQ(bitArray.count(), 10);
    bitArray.resize(100, true);
    EXPECT_EQ(bitArray.count(), 100);
}

int main(int argc, char** argv) {

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
