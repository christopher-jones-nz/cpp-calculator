#include <gtest/gtest.h>
#include "calculator.h"

class CalculatorTest : public ::testing::Test {
protected:
    Calculator calc;
};

// Basic operation tests
TEST_F(CalculatorTest, AddTwoPositiveNumbers) {
    EXPECT_DOUBLE_EQ(calc.add(2.0, 3.0), 5.0);
}

TEST_F(CalculatorTest, AddNegativeNumbers) {
    EXPECT_DOUBLE_EQ(calc.add(-2.0, -3.0), -5.0);
}

TEST_F(CalculatorTest, AddMixedNumbers) {
    EXPECT_DOUBLE_EQ(calc.add(-2.0, 5.0), 3.0);
}

TEST_F(CalculatorTest, SubtractTwoNumbers) {
    EXPECT_DOUBLE_EQ(calc.subtract(10.0, 4.0), 6.0);
}

TEST_F(CalculatorTest, SubtractNegativeResult) {
    EXPECT_DOUBLE_EQ(calc.subtract(4.0, 10.0), -6.0);
}

TEST_F(CalculatorTest, MultiplyTwoNumbers) {
    EXPECT_DOUBLE_EQ(calc.multiply(3.0, 4.0), 12.0);
}

TEST_F(CalculatorTest, MultiplyByZero) {
    EXPECT_DOUBLE_EQ(calc.multiply(5.0, 0.0), 0.0);
}

TEST_F(CalculatorTest, MultiplyNegativeNumbers) {
    EXPECT_DOUBLE_EQ(calc.multiply(-3.0, -4.0), 12.0);
}

TEST_F(CalculatorTest, DivideTwoNumbers) {
    EXPECT_DOUBLE_EQ(calc.divide(12.0, 4.0), 3.0);
}

TEST_F(CalculatorTest, DivideWithDecimalResult) {
    EXPECT_DOUBLE_EQ(calc.divide(10.0, 4.0), 2.5);
}

TEST_F(CalculatorTest, DivideByZeroThrowsException) {
    EXPECT_THROW(calc.divide(10.0, 0.0), DivisionByZeroException);
}

// Decimal number tests
TEST_F(CalculatorTest, AddDecimalNumbers) {
    EXPECT_DOUBLE_EQ(calc.add(1.5, 2.5), 4.0);
}

TEST_F(CalculatorTest, SubtractDecimalNumbers) {
    EXPECT_DOUBLE_EQ(calc.subtract(5.5, 2.25), 3.25);
}

TEST_F(CalculatorTest, MultiplyDecimalNumbers) {
    EXPECT_DOUBLE_EQ(calc.multiply(2.5, 4.0), 10.0);
}

TEST_F(CalculatorTest, DivideDecimalNumbers) {
    EXPECT_DOUBLE_EQ(calc.divide(7.5, 2.5), 3.0);
}

// Calculator state tests
TEST_F(CalculatorTest, CalculateAddition) {
    calc.setOperand(5.0);
    calc.setOperation('+');
    EXPECT_DOUBLE_EQ(calc.calculate(3.0), 8.0);
}

TEST_F(CalculatorTest, CalculateSubtraction) {
    calc.setOperand(10.0);
    calc.setOperation('-');
    EXPECT_DOUBLE_EQ(calc.calculate(4.0), 6.0);
}

TEST_F(CalculatorTest, CalculateMultiplication) {
    calc.setOperand(6.0);
    calc.setOperation('*');
    EXPECT_DOUBLE_EQ(calc.calculate(7.0), 42.0);
}

TEST_F(CalculatorTest, CalculateDivision) {
    calc.setOperand(20.0);
    calc.setOperation('/');
    EXPECT_DOUBLE_EQ(calc.calculate(4.0), 5.0);
}

TEST_F(CalculatorTest, ClearResetsState) {
    calc.setOperand(10.0);
    calc.setOperation('+');
    calc.calculate(5.0);
    calc.clear();
    EXPECT_DOUBLE_EQ(calc.getResult(), 0.0);
}

TEST_F(CalculatorTest, GetResultReturnsLastCalculation) {
    calc.setOperand(3.0);
    calc.setOperation('*');
    calc.calculate(4.0);
    EXPECT_DOUBLE_EQ(calc.getResult(), 12.0);
}
