#include "tictactoe.h"
#include <QtCore/qdebug.h>

TicTacToe::TicTacToe() {
    m_isPlayerTurn = true;
    m_gameField.assign(3, QVector<PlayerFieldState>(3, PlayerFieldState::Empty));
    m_playerFighter = Empty;
    m_botFighter = Empty;
    m_isGameStarted = false;
}

bool TicTacToe::isFieldEmpty(int row, int col) {
    return m_gameField[row][col] == PlayerFieldState::Empty;
}

bool TicTacToe::getIsGameStarted() {
    return m_isGameStarted;
}

void TicTacToe::setIsGameStarted(bool isGameStarted) {
    m_isGameStarted = isGameStarted;
}

void TicTacToe::setisPlayerTurn(bool isPlayerTurn) {
    m_isPlayerTurn = isPlayerTurn;
}

void TicTacToe::setPlayerFighter(PlayerFieldState playerFieldState) {
    m_playerFighter = playerFieldState;
}

void TicTacToe::setBotFighter(PlayerFieldState playerFieldState) {
    m_botFighter = playerFieldState;
}

void TicTacToe::attemptToTurn(int buttonId) {
    int row = buttonId / 3, col = buttonId % 3;
    if (m_isGameStarted && m_isPlayerTurn && isFieldEmpty(row, col)) {
        makeTurn(row, col, m_playerFighter);
        if (findWinner() == Unfinished) {
            botTurn();
        }
    }
}

void TicTacToe::makeTurn(int row, int col, PlayerFieldState state) {
    m_gameField[row][col] = state;
    emit setButtonIcon(row * 3 + col, state);

    m_isPlayerTurn = !m_isPlayerTurn;

    GameState result = findWinner();
    if (result != Unfinished) {
        m_isPlayerTurn = false;
        emit displayResult(result);
    }
}

void TicTacToe::botTurn() {
    int bestScore = std::numeric_limits<int>::min();
    int bestRow = -1, bestCol = -1;

    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (isFieldEmpty(row, col)) {
                m_gameField[row][col] = m_botFighter;
                int score = minimax(m_gameField, 0, false);
                m_gameField[row][col] = PlayerFieldState::Empty;

                if (score > bestScore) {
                    bestScore = score;
                    bestRow = row;
                    bestCol = col;
                }
            }
        }
    }

    if (bestRow != -1 && bestCol != -1) {
        makeTurn(bestRow, bestCol, m_botFighter);
    }
}

int TicTacToe::minimax(QVector<QVector<PlayerFieldState>> &field, int depth, bool isMaximizing) {
    GameState result = findWinner();
    if (result != Unfinished) {
        if (result == BotWin) return 10 - depth;
        if (result == PlayerWin) return depth - 10;
        return 0;
    }

    if (isMaximizing) {
        int bestScore = std::numeric_limits<int>::min();
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                if (field[row][col] == PlayerFieldState::Empty) {
                    field[row][col] = m_botFighter;
                    int score = minimax(field, depth + 1, false);
                    field[row][col] = PlayerFieldState::Empty;
                    bestScore = std::max(score, bestScore);
                }
            }
        }
        return bestScore;
    } else {
        int worstScore = std::numeric_limits<int>::max();
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                if (field[row][col] == PlayerFieldState::Empty) {
                    field[row][col] = m_playerFighter;
                    int score = minimax(field, depth + 1, true);
                    field[row][col] = PlayerFieldState::Empty;
                    worstScore = std::min(score, worstScore);
                }
            }
        }
        return worstScore;
    }
}

TicTacToe::GameState TicTacToe::findWinner() {
    for (int i = 0; i < 3; ++i) {
        if (m_gameField[i][0] == m_gameField[i][1] && m_gameField[i][1] == m_gameField[i][2] && m_gameField[i][0] != PlayerFieldState::Empty)
            return m_gameField[i][0] == m_playerFighter ? PlayerWin : BotWin;
        if (m_gameField[0][i] == m_gameField[1][i] && m_gameField[1][i] == m_gameField[2][i] && m_gameField[0][i] != PlayerFieldState::Empty)
            return m_gameField[0][i] == m_playerFighter ? PlayerWin : BotWin;
    }
    if (m_gameField[0][0] == m_gameField[1][1] && m_gameField[1][1] == m_gameField[2][2] && m_gameField[0][0] != PlayerFieldState::Empty)
        return m_gameField[0][0] == m_playerFighter ? PlayerWin : BotWin;
    if (m_gameField[0][2] == m_gameField[1][1] && m_gameField[1][1] == m_gameField[2][0] && m_gameField[0][2] != PlayerFieldState::Empty)
        return m_gameField[0][2] == m_playerFighter ? PlayerWin : BotWin;

    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (m_gameField[row][col] == PlayerFieldState::Empty)
                return Unfinished;
        }
    }
    return Draw;
}
