#ifndef NUMBERLINE_H
#define NUMBERLINE_H

#include <QIntValidator>
#include <QLineEdit>
#include <QObject>
#include <QRegularExpressionValidator>
#include <QWidget>

class numberLine : public QLineEdit
{
    Q_OBJECT
  public:
    numberLine(QWidget *parent = nullptr);

  protected:
    void focusInEvent(QFocusEvent *) override;
    void focusOutEvent(QFocusEvent *) override;
};

#endif // NUMBERLINE_H
