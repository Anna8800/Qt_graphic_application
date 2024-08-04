#include "SettingsWidget.h"

SettingsWidget::SettingsWidget(QWidget* parent) :QWidget(parent)
{
	titleLabel = new QLabel("Welcome to Tic-Tac-Toe");
	titleLabel->setAlignment(Qt::AlignCenter);

	sizeLabel = new QLabel("Field Size:");
	sizeLineEdit = new QLineEdit;
	sizeLineEdit->setPlaceholderText("Enter size");
	sizeLineEdit->setValidator(new QIntValidator(5, 100, this));

	figureLabel = new QLabel("Player Figure:");
	figureComboBox = new QComboBox;
	figureComboBox->addItem("X");
	figureComboBox->addItem("O");

	submitButton = new QPushButton("Start game");

	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->addWidget(titleLabel);
	layout->addWidget(sizeLabel);
	layout->addWidget(sizeLineEdit);
	layout->addWidget(figureLabel);
	layout->addWidget(figureComboBox);
	layout->addWidget(submitButton);
	layout->addStretch();

    connect(submitButton, &QPushButton::clicked, this, &SettingsWidget::onSubmit);
}

void SettingsWidget::onSubmit()
{
	bool ok;
	int size = sizeLineEdit->text().toInt(&ok);
	if (!ok || size < 5) {
		QMessageBox::critical(this, "Invalid Size", "Field size must be at least 5.");
		return;
	}
	QString figure = figureComboBox->currentText();
	emit sizeSelected(size);
	emit figureSelected(figure); 
}