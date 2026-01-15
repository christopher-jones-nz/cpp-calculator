#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include "calculator.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void onDigitClicked();
    void onOperationClicked();
    void onEqualsClicked();
    void onClearClicked();
    void onDecimalClicked();

private:
    void createUI();
    QPushButton* createButton(const QString &text, const char *slot);

    QLineEdit *m_display;
    Calculator m_calculator;
    QString m_currentInput;
    bool m_waitingForOperand;
};

#endif // MAINWINDOW_H
