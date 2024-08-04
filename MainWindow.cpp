#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    stackedWidget = new QStackedWidget(this);
    settingsWidget = new SettingsWidget(this);
    ticTacToePage = new TicTacToe(this);
    selectedSize = 0;

    setCentralWidget(stackedWidget);
    stackedWidget->addWidget(settingsWidget);
    stackedWidget->addWidget(ticTacToePage);

    connect(settingsWidget, &SettingsWidget::sizeSelected, this, &MainWindow::handleSizeSelected);
    connect(settingsWidget, &SettingsWidget::figureSelected, this, &MainWindow::handleFigureSelected);
    connect(settingsWidget, &SettingsWidget::sizeSelected, this, [this](int size) {
        if (!selectedFigure.isEmpty()) {
            showTicTacToePage(size, selectedFigure);
        }
        });
    connect(settingsWidget, &SettingsWidget::figureSelected, this, [this](const QString& figure) {
        if (selectedSize > 0) {
            showTicTacToePage(selectedSize, figure);
        }
        });
}

void MainWindow::handleSizeSelected(int size){
    selectedSize = size;
}

void MainWindow::handleFigureSelected(const QString& figure){
    selectedFigure = figure;
}

void MainWindow::showTicTacToePage(int size, const QString& figure){
    ticTacToePage->setSizeAndFigure(size, figure);
    stackedWidget->setCurrentWidget(ticTacToePage);
}