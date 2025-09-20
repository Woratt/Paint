#include "numberline.h"

numberLine::numberLine(QWidget *parent) : QLineEdit(parent)
{
    setText("0");
    QRegularExpression rx("\\d+");
    QValidator *validator = new QRegularExpressionValidator(rx, this);
    setValidator(validator);
}

void numberLine::focusInEvent(QFocusEvent *event)
{
    if (text() == "0")
        clear();
    QLineEdit::focusInEvent(event);
}

void numberLine::focusOutEvent(QFocusEvent *event)
{
    if (text().isEmpty())
        setText("0");
    QLineEdit::focusOutEvent(event);
}
