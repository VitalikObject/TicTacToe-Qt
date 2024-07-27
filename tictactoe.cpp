#include "tictactoe.h"
#include <QtCore/qdebug.h>

TicTacToe::TicTacToe() {
    m_isPlayerTurn = true;
    m_gameField.assign(3, QVector<FieldState>(3, FieldState::Empty));
}

bool TicTacToe::isFieldEmpty(int row, int col) {
    return m_gameField[row][col] == FieldState::Empty;
}

void TicTacToe::attemptToTurn(int buttonId) {
    int row = buttonId / 3, col = buttonId % 3;
    if (m_isPlayerTurn && isFieldEmpty(row, col)) {
        m_isPlayerTurn = false;

        makeTurn(row, col, FieldState::X);
        if (findWinner() == Unfinished) {
            botTurn();
        }
    }
}

void TicTacToe::makeTurn(int row, int col, FieldState state) {
    m_gameField[row][col] = state;
    emit setButtonIcon(row * 3 + col, state);

    GameState result = findWinner();
    if (result != Unfinished) {
        emit displayResult(result);
    }
}

void TicTacToe::botTurn() {
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (isFieldEmpty(row, col)) {
                makeTurn(row, col, FieldState::O);
                m_isPlayerTurn = true;
                return;
            }
        }
    }
}

TicTacToe::GameState TicTacToe::findWinner() {
    for (int i = 0; i < 3; ++i) {
        if (m_gameField[i][0] == m_gameField[i][1] && m_gameField[i][1] == m_gameField[i][2] && m_gameField[i][0] != FieldState::Empty)
            return m_gameField[i][0] == FieldState::X ? PlayerWin : BotWin;
        if (m_gameField[0][i] == m_gameField[1][i] && m_gameField[1][i] == m_gameField[2][i] && m_gameField[0][i] != FieldState::Empty)
            return m_gameField[0][i] == FieldState::X ? PlayerWin : BotWin;
    }
    if (m_gameField[0][0] == m_gameField[1][1] && m_gameField[1][1] == m_gameField[2][2] && m_gameField[0][0] != FieldState::Empty)
        return m_gameField[0][0] == FieldState::X ? PlayerWin : BotWin;
    if (m_gameField[0][2] == m_gameField[1][1] && m_gameField[1][1] == m_gameField[2][0] && m_gameField[0][2] != FieldState::Empty)
        return m_gameField[0][2] == FieldState::X ? PlayerWin : BotWin;

    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (m_gameField[row][col] == FieldState::Empty)
                return Unfinished;
        }
    }
    return Draw;
}
