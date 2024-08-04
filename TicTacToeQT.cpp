#include "TicTacToeQT.h"


TicTacToe::TicTacToe(QWidget* parent) {
    setMinimumSize(800, 800);
    setWindowTitle(title); //меняем название виджета

    tableWidget = new QTableWidget(this);
    tableWidget->horizontalHeader()->setVisible(false); //без названий столбцов и строк
    tableWidget->verticalHeader()->setVisible(false);

    startbtn = new QPushButton("Start new game", this); //кнопка старта новой игры
    exitbtn = new QPushButton("Exit", this); //кнопка выхода из приложения

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(tableWidget);
    layout->addWidget(startbtn);
    layout->addWidget(exitbtn);

    connect(startbtn, &QPushButton::clicked, this, &TicTacToe::slot_start);
    connect(exitbtn, &QPushButton::clicked, this, &TicTacToe::slot_exit);
    connect(tableWidget, &QTableWidget::cellClicked, this, &TicTacToe::slot_cell_clicked);

    updateTableSize();
    resetGame(); //перезапуск
}

void TicTacToe::setSizeAndFigure(int size, const QString& figure) { //получаем информацию из SettingsWidget о размере поля и фигуре игрока
    fieldSize = size;
    playerFigure = figure;
    compFigure = (playerFigure == "X") ? "O" : "X";
    tableWidget->setRowCount(size);
    tableWidget->setColumnCount(size);
    updateTableSize();
}

void TicTacToe::updateTableSize() { //для квадратных ячеек
    if (tableWidget->rowCount() == 0) {
        return;
    }
    int tableSize = qMin(tableWidget->width(), tableWidget->height()) - tableWidget->frameWidth() * 2;
    int cellSize = tableSize / tableWidget->rowCount();
    for (int i = 0; i < tableWidget->rowCount(); ++i){
        tableWidget->setRowHeight(i, cellSize);
        tableWidget->setColumnWidth(i, cellSize);
    }
}

void TicTacToe::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    updateTableSize();
}

void TicTacToe::slot_exit(){
    qApp->exit();
}

void TicTacToe::slot_cell_clicked(int row, int col) {
    mousePressEvent(new QMouseEvent(QEvent::MouseButtonPress, QPoint(col * tableWidget->columnWidth(0), row * tableWidget->rowHeight(0)), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier));
}

void TicTacToe::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    for (int row = 0; row < tableWidget->rowCount(); ++row) {
        for (int col = 0; col < tableWidget->columnCount(); ++col) {
            QRect rect = tableWidget->visualRect(tableWidget->model()->index(row, col));
            QTableWidgetItem* item = tableWidget->item(row, col);
            QString text = item ? item->text() : "";

            if (text == "X") {
                item->setForeground(QBrush(Qt::black));
                item->setBackground(QBrush(Qt::yellow));
            }
            else if (text == "O") {
                item->setForeground(QBrush(Qt::blue));
                item->setBackground(QBrush(Qt::green));
            }
            else { continue; }
            item->setTextAlignment(Qt::AlignCenter); //центровка
            QFont font = item->font();
            int cellHeight = tableWidget->rowHeight(row);
            int cellWidth = tableWidget->columnWidth(col);
            int fontSize = qMin(cellHeight, cellWidth) / 3;  //устанавливаем размер шрифта в зависимости от размеров ячейки
            font.setPointSize(fontSize);
            item->setFont(font);
            tableWidget->setItem(row, col, item);
        }
    }
    updateTableSize();
}

bool TicTacToe::isBoardFull() { //проверка на ничью
    for (int row = 0; row < tableWidget->rowCount(); ++row) {
        for (int col = 0; col < tableWidget->columnCount(); ++col) {
            if (tableWidget->item(row, col) == nullptr || tableWidget->item(row, col)->text().isEmpty()) {
                return false;
            }
        }
    }
    return true;
}

void TicTacToe::mousePressEvent(QMouseEvent* event) {
    if (gameOver) return;

    int row = event->pos().y() / tableWidget->rowHeight(0);
    int col = event->pos().x() / tableWidget->columnWidth(0);

    if (tableWidget->item(row, col) == nullptr || tableWidget->item(row, col)->text().isEmpty()) {
        QTableWidgetItem* item = new QTableWidgetItem(playerFigure);
        tableWidget->setItem(row, col, new QTableWidgetItem(playerFigure));
        tableWidget->update();
        if (checkWin(playerFigure)){
            QString winner = playerFigure;
            QMessageBox::information(this, "Game Over", QString("%1 wins!").arg(winner));
            gameOver = true;
            return;
        }
        if (isBoardFull()) { //после хода проверяем на заполненность поля
            QMessageBox::information(this, "Game Over", "It's a tie!");
            gameOver = true;
            return;
        }
        computerMove();
    }
    else { //если ячейка уже занята
        QMessageBox::information(this, "Error", "Cell is occupied!");
    }
}

void TicTacToe::resetGame() {
    tableWidget->clearContents();
    tableWidget->update();
    gameOver = false;
}

void TicTacToe::slot_start(){
    resetGame();
}

bool TicTacToe::checkWin(QString symbol) {
    int size = tableWidget->rowCount(); 
    std::vector<QPoint> dir = { {1, 0}, {0, 1}, {1, 1}, {1, -1} };

    for (const auto& direction : dir) {
        int dx = direction.x();
        int dy = direction.y();

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                int count = 0; 
                for (int k = 0; k < 5; ++k) {
                    int row = i + k * dx;
                    int col = j + k * dy;
                    if (row >= 0 && row < size && col >= 0 && col < size &&
                        tableWidget->item(row, col) && tableWidget->item(row, col)->text() == symbol) {
                        ++count;
                        if (count == 5) return true; 
                    }
                    else {
                        break; 
                    }
                }
            }
        }
    }
    return false;
}
void TicTacToe::computerMove() {
    if (gameOver) return;
    bool foundEmptyCell = false;
    while (!foundEmptyCell) {
        int row = qrand() % tableWidget->rowCount();
        int col = qrand() % tableWidget->columnCount();
        if (tableWidget->item(row, col) == nullptr || tableWidget->item(row, col)->text().isEmpty()) {
            QTableWidgetItem* item = new QTableWidgetItem(compFigure);
            foundEmptyCell = true;
            tableWidget->setItem(row, col, new QTableWidgetItem(compFigure));
            tableWidget->update();
            if (checkWin(compFigure)) {
                QString winner = compFigure;
                QMessageBox::information(this, "Game Over", QString("%1 wins!").arg(winner));
                gameOver = true;
                return;
            }
        }
    }
    if (isBoardFull()) { //после хода проверяем на заполненность поля
        QMessageBox::information(this, "Game Over", "It's a tie!");
        gameOver = true;
    }
}