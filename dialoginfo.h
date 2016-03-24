#ifndef DIALOGINFO_H
#define DIALOGINFO_H

#include <QDialog>
#include <QDebug>
#include <QMouseEvent>

namespace Ui {
class DialogInfo;
}

class DialogInfo : public QDialog
{
    Q_OBJECT

public:
    explicit DialogInfo(QWidget *parent = 0);
    ~DialogInfo();

private:
    Ui::DialogInfo *ui;
    QString Text_aus_Zitaten,Text_Lizenzrechte;
    QString aktPassword;



protected:
    void keyPressEvent(QKeyEvent *event);


};

#endif // DIALOGINFO_H
