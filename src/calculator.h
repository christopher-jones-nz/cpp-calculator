#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <stdexcept>

class Calculator {
public:
    Calculator() = default;

    double add(double a, double b) const;
    double subtract(double a, double b) const;
    double multiply(double a, double b) const;
    double divide(double a, double b) const;

    void clear();
    void setOperand(double value);
    void setOperation(char op);
    double calculate(double secondOperand);
    double getResult() const;

private:
    double m_result = 0.0;
    double m_firstOperand = 0.0;
    char m_operation = '\0';
    bool m_hasFirstOperand = false;
};

class DivisionByZeroException : public std::runtime_error {
public:
    DivisionByZeroException() : std::runtime_error("Division by zero") {}
};

#endif // CALCULATOR_H
