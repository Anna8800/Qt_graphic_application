#pragma once


#include <QtWidgets/QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QMouseEvent>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QDebug>
#include <QApplication>
#include <QResizeEvent>
#include <QRandomGenerator>
#include <QMessageBox>
#include <QFont>
#include "SettingsWidget.h"


class TicTacToe : public QWidget
{
    Q_OBJECT

public:
    TicTacToe(QWidget* parent = nullptr);
    ~TicTacToe() {};
    void setSizeAndFigure(int size, const QString& figure);
    void resizeEvent(QResizeEvent* event) override;
    void paintEvent(QPaintEvent* event);
	void mousePressEvent(QMouseEvent* event);
    void resetGame();
private:
    const QString title = "Tic-Tac-Toe";
    QTableWidget* tableWidget;
    int fieldSize;
    QString playerFigure;
    QString compFigure;
    QPushButton* startbtn;
	QPushButton* exitbtn;

    void updateTableSize();
    bool gameOver = false;
    void computerMove();
    bool checkWin(QString symbol);
    bool isBoardFull();
public slots:
    void slot_start();
    void slot_exit();
    void slot_cell_clicked(int row, int col);
};