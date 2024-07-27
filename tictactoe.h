#pragma once
#include <QVector>
#include <QObject>

class TicTacToe : public QObject {
    Q_OBJECT

public:
    TicTacToe();
    void attemptToTurn(int buttonId);
    enum FieldState { Empty, X, O };
    enum GameState { Unfinished, Draw, PlayerWin, BotWin };

signals:
    void setButtonIcon(int buttonId, TicTacToe::FieldState fieldState);
    void displayResult(TicTacToe::GameState gameState);

private:
    bool m_isPlayerTurn;
    QVector<QVector<FieldState>> m_gameField;
    GameState findWinner();
    bool isFieldEmpty(int row, int col);
    void botTurn();
    void makeTurn(int row, int col, FieldState state);
};
