#include "PlayerContainer.h"
#include "ui_PlayerContainer.h"

PlayerContainer::PlayerContainer(QWidget *parent)
        : QMainWindow(parent),
          ui(new Ui::PlayerContainer)
{
    ui->setupUi(this);

}

PlayerContainer::~PlayerContainer()
{
    delete ui;
}
