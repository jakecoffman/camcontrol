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

//private slots:
//    void openLocal();
//    void openUrl();

private:
    Ui::PlayerContainer *ui;

    SimplePlayer *_player0;
    SimplePlayer *_player1;
};


#endif //SIMPLE_PLAYER_MAIN_H
