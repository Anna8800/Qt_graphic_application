#pragma once


#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QIntValidator>
#include <QMessageBox>


class SettingsWidget : public QWidget
{
    Q_OBJECT
public:
    SettingsWidget(QWidget* parent = nullptr);
    ~SettingsWidget() {};
signals:
    void sizeSelected(int size);
    void figureSelected(const QString& figure);
private slots:
    void onSubmit();
private:
    QLabel* titleLabel;
    QLabel* sizeLabel;
    QLineEdit* sizeLineEdit;
    QLabel* figureLabel;
    QComboBox* figureComboBox;
    QPushButton* submitButton;
};