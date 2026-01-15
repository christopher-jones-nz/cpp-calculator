#include "calculator.h"

double Calculator::add(double a, double b) const {
    return a + b;
}

double Calculator::subtract(double a, double b) const {
    return a - b;
}

double Calculator::multiply(double a, double b) const {
    return a * b;
}

double Calculator::divide(double a, double b) const {
    if (b == 0.0) {
        throw DivisionByZeroException();
    }
    return a / b;
}

void Calculator::clear() {
    m_result = 0.0;
    m_firstOperand = 0.0;
    m_operation = '\0';
    m_hasFirstOperand = false;
}

void Calculator::setOperand(double value) {
    m_firstOperand = value;
    m_hasFirstOperand = true;
}

void Calculator::setOperation(char op) {
    m_operation = op;
}

double Calculator::calculate(double secondOperand) {
    if (!m_hasFirstOperand) {
        m_result = secondOperand;
        return m_result;
    }

    switch (m_operation) {
        case '+':
            m_result = add(m_firstOperand, secondOperand);
            break;
        case '-':
            m_result = subtract(m_firstOperand, secondOperand);
            break;
        case '*':
            m_result = multiply(m_firstOperand, secondOperand);
            break;
        case '/':
            m_result = divide(m_firstOperand, secondOperand);
            break;
        default:
            m_result = secondOperand;
            break;
    }

    return m_result;
}

double Calculator::getResult() const {
    return m_result;
}
