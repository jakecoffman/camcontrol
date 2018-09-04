#ifndef SIMPLE_PLAYER_MAIN_H
#define SIMPLE_PLAYER_MAIN_H

#include <QMainWindow>

namespace Ui {
    class PlayerContainer;
}

class SimplePlayer;

class PlayerContainer : public QMainWindow
{
Q_OBJECT
public:
    explicit PlayerContainer(QWidget *parent = nullptr);
    ~PlayerContainer() override;

private slots:
    void handleFull0();
    void handleFull1();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    void writeSettings();
    void readSettings();

private:
    Ui::PlayerContainer *ui;
};


#endif //SIMPLE_PLAYER_MAIN_H
