#pragma once

#include <QLabel>
#include <QEvent>
#include <QMouseEvent>
#include <QDebug>

class ClickEventFilter : public QObject {
    Q_OBJECT

public:
    explicit ClickEventFilter(QObject *parent = nullptr) : QObject(parent) {}

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

signals:
    void labelClicked();
};
