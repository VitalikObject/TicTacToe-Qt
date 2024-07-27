#include "clickeventfilter.h"

bool ClickEventFilter::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            qDebug() << "Label clicked!";
            emit labelClicked();
        }
    }
    return QObject::eventFilter(obj, event);
}
