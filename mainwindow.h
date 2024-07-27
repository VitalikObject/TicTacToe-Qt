#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPushButton>
#include "tictactoe.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *m_ui;
    QList<QPushButton*> m_allButtons;
    TicTacToe *m_ticTacToe;
    QIcon m_iconX = QIcon(":/Icons/tic.png");
    QIcon m_iconO = QIcon(":/Icons/tac.png");
    void onButtonClicked();
    void findAndStoreAllButtons();
    void findButtonsRecursive(QObject* parent, QList<QPushButton*>& buttons);
    void onResetClicked();
    void setupIcons();
    void setupEventFilters();
    void connectSignalsAndSlots();

private slots:
    void setButtonIcon(int buttonId, TicTacToe::FieldState fieldState);
    void displayResult(TicTacToe::GameState gameState);
};
#endif // MAINWINDOW_H
