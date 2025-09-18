#ifndef NUMBERLINE_H
#define NUMBERLINE_H

#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QIntValidator>
#include <QRegularExpressionValidator>

class numberLine : public QLineEdit
{
    Q_OBJECT
public:
    numberLine(QWidget* parent = nullptr);
protected:
    void focusInEvent(QFocusEvent*) override;
    void focusOutEvent(QFocusEvent*) override;
};

#endif // NUMBERLINE_H
