#include "mainwindow.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_display(nullptr)
    , m_waitingForOperand(true)
{
    createUI();
    setWindowTitle("Calculator");
    setFixedSize(280, 350);
}

void MainWindow::createUI() {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Display
    m_display = new QLineEdit("0");
    m_display->setReadOnly(true);
    m_display->setAlignment(Qt::AlignRight);
    m_display->setStyleSheet("QLineEdit { font-size: 24px; padding: 10px; }");
    mainLayout->addWidget(m_display);

    // Button grid
    QGridLayout *gridLayout = new QGridLayout();

    // Number buttons
    for (int i = 1; i <= 9; ++i) {
        int row = (9 - i) / 3;
        int col = (i - 1) % 3;
        QPushButton *btn = createButton(QString::number(i), SLOT(onDigitClicked()));
        gridLayout->addWidget(btn, row + 1, col);
    }

    // Zero button
    QPushButton *zeroBtn = createButton("0", SLOT(onDigitClicked()));
    gridLayout->addWidget(zeroBtn, 4, 0);

    // Decimal button
    QPushButton *decimalBtn = createButton(".", SLOT(onDecimalClicked()));
    gridLayout->addWidget(decimalBtn, 4, 1);

    // Equals button
    QPushButton *equalsBtn = createButton("=", SLOT(onEqualsClicked()));
    gridLayout->addWidget(equalsBtn, 4, 2);

    // Operation buttons
    QPushButton *addBtn = createButton("+", SLOT(onOperationClicked()));
    gridLayout->addWidget(addBtn, 1, 3);

    QPushButton *subBtn = createButton("-", SLOT(onOperationClicked()));
    gridLayout->addWidget(subBtn, 2, 3);

    QPushButton *mulBtn = createButton("*", SLOT(onOperationClicked()));
    gridLayout->addWidget(mulBtn, 3, 3);

    QPushButton *divBtn = createButton("/", SLOT(onOperationClicked()));
    gridLayout->addWidget(divBtn, 4, 3);

    // Clear button
    QPushButton *clearBtn = createButton("C", SLOT(onClearClicked()));
    clearBtn->setStyleSheet("QPushButton { background-color: #ff6b6b; color: white; font-size: 18px; padding: 15px; }");
    gridLayout->addWidget(clearBtn, 0, 3);

    mainLayout->addLayout(gridLayout);
}

QPushButton* MainWindow::createButton(const QString &text, const char *slot) {
    QPushButton *button = new QPushButton(text);
    button->setStyleSheet("QPushButton { font-size: 18px; padding: 15px; }");
    connect(button, SIGNAL(clicked()), this, slot);
    return button;
}

void MainWindow::onDigitClicked() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    QString digit = button->text();

    if (m_waitingForOperand) {
        m_currentInput = digit;
        m_waitingForOperand = false;
    } else {
        if (m_currentInput == "0") {
            m_currentInput = digit;
        } else {
            m_currentInput += digit;
        }
    }

    m_display->setText(m_currentInput);
}

void MainWindow::onOperationClicked() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    QString op = button->text();
    double operand = m_currentInput.toDouble();

    if (!m_waitingForOperand) {
        try {
            double result = m_calculator.calculate(operand);
            m_display->setText(QString::number(result, 'g', 15));
        } catch (const DivisionByZeroException &) {
            m_display->setText("Error");
            m_calculator.clear();
            m_waitingForOperand = true;
            return;
        }
    }

    m_calculator.setOperand(m_currentInput.toDouble());
    m_calculator.setOperation(op.at(0).toLatin1());
    m_waitingForOperand = true;
}

void MainWindow::onEqualsClicked() {
    double operand = m_currentInput.toDouble();

    try {
        double result = m_calculator.calculate(operand);
        m_display->setText(QString::number(result, 'g', 15));
        m_currentInput = QString::number(result, 'g', 15);
    } catch (const DivisionByZeroException &) {
        m_display->setText("Error");
        m_calculator.clear();
    }

    m_calculator.clear();
    m_waitingForOperand = true;
}

void MainWindow::onClearClicked() {
    m_calculator.clear();
    m_currentInput = "0";
    m_display->setText("0");
    m_waitingForOperand = true;
}

void MainWindow::onDecimalClicked() {
    if (m_waitingForOperand) {
        m_currentInput = "0.";
        m_waitingForOperand = false;
    } else if (!m_currentInput.contains('.')) {
        m_currentInput += '.';
    }

    m_display->setText(m_currentInput);
}
