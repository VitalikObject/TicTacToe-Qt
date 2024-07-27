#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "clickeventfilter.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
    , m_ticTacToe(new TicTacToe())
{
    m_ui->setupUi(this);
    this->setWindowTitle("TicTacToe created by Vitalii Strashnov & Mariia Bulhak");
    this->setFixedSize(this->size());

    findAndStoreAllButtons();

    setupIcons();
    setupEventFilters();

    connectSignalsAndSlots();
    m_ui->label->hide();
}

MainWindow::~MainWindow() {
    delete m_ui;
    delete m_ticTacToe;
}

void MainWindow::setupIcons() {
    QPixmap pixmap(":/Icons/reset.png");
    m_ui->label_2->setPixmap(pixmap);
    m_ui->label_2->setScaledContents(true);
}

void MainWindow::setupEventFilters() {
    ClickEventFilter *eventFilter = new ClickEventFilter(this);
    m_ui->label_2->installEventFilter(eventFilter);
    connect(eventFilter, &ClickEventFilter::labelClicked, this, &MainWindow::onResetClicked);
}

void MainWindow::connectSignalsAndSlots() {
    connect(m_ticTacToe, &TicTacToe::setButtonIcon, this, &MainWindow::setButtonIcon);
    connect(m_ticTacToe, &TicTacToe::displayResult, this, &MainWindow::displayResult);
}

void MainWindow::onResetClicked() {
    delete m_ticTacToe;
    m_ticTacToe = new TicTacToe();

    for (QPushButton* button : m_allButtons) {
        button->setIcon(QIcon());
    }

    connectSignalsAndSlots();
    m_ui->label->hide();
}

void MainWindow::displayResult(TicTacToe::GameState gameState) {
    QString resultText;

    switch (gameState) {
    case TicTacToe::GameState::Draw:
        resultText = "Draw";
        break;
    case TicTacToe::GameState::PlayerWin:
        resultText = "You win!";
        break;
    case TicTacToe::GameState::BotWin:
        resultText = "Bot wins!";
        break;
    default:
        resultText = "";
        break;
    }

    m_ui->label->setText(resultText);
    if (!resultText.isEmpty()) {
        m_ui->label->show();
    }
}

void MainWindow::setButtonIcon(int buttonId, TicTacToe::FieldState field) {
    QIcon icon;

    switch (field) {
    case TicTacToe::FieldState::O:
        icon = m_iconO;
        break;
    case TicTacToe::FieldState::X:
        icon = m_iconX;
        break;
    default:
        icon = QIcon();
        break;
    }

    if (!icon.isNull()) {
        m_allButtons[buttonId]->setIcon(icon);
        m_allButtons[buttonId]->setIconSize(QSize(90, 90));
    }
}

void MainWindow::onButtonClicked() {
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
    if (clickedButton) {
        qDebug() << "Button clicked:" << clickedButton->text() << ", Id: " << m_allButtons.indexOf(clickedButton);
        m_ticTacToe->attemptToTurn(m_allButtons.indexOf(clickedButton));
    } else {
        qDebug() << "Error: sender is not a QPushButton";
    }
}

void MainWindow::findAndStoreAllButtons() {
    findButtonsRecursive(this, m_allButtons);

    for (QPushButton* button : m_allButtons) {
        qDebug() << "Found button:" << button->text();
        connect(button, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
    }
}

void MainWindow::findButtonsRecursive(QObject* parent, QList<QPushButton*>& buttons) {
    for (QObject* child : parent->children()) {
        if (QPushButton* button = qobject_cast<QPushButton*>(child)) {
            buttons.append(button);
        }

        findButtonsRecursive(child, buttons);
    }
}
