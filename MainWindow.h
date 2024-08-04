#pragma once
#include <QMainWindow>
#include <QStackedWidget>
#include "SettingsWidget.h"
#include "TicTacToeQT.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow() {};
private:
    QStackedWidget* stackedWidget;
    SettingsWidget* settingsWidget;
    TicTacToe* ticTacToePage;
    int selectedSize;
    QString selectedFigure;
private slots:
    void showTicTacToePage(int size, const QString& figure);
    void handleSizeSelected(int size);
    void handleFigureSelected(const QString& figure);
};

