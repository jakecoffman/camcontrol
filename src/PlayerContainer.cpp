#include <QSettings>
#include <QCloseEvent>
#include <QDebug>
#include "PlayerContainer.h"
#include "ui_PlayerContainer.h"

PlayerContainer::PlayerContainer(QWidget *parent)
        : QMainWindow(parent),
          ui(new Ui::PlayerContainer)
{
    ui->setupUi(this);
    readSettings();

    connect(ui->player0, &SimplePlayer::toggleFull, this, &PlayerContainer::handleFull0);
    connect(ui->player1, &SimplePlayer::toggleFull, this, &PlayerContainer::handleFull1);
}

PlayerContainer::~PlayerContainer()
{
    delete ui;
}

void PlayerContainer::closeEvent(QCloseEvent *event) {
    writeSettings();
    event->accept();
}

void PlayerContainer::readSettings() {
    QSettings settings("jakecoffman.com", "camcontrol");
    settings.beginGroup("PlayerContainer");
    resize(settings.value("size", QSize(400, 400)).toSize());
    move(settings.value("pos", QPoint(200, 200)).toPoint());
    ui->player0->setVolume(settings.value("vol0", 0).toInt());
    ui->player1->setVolume(settings.value("vol1", 0).toInt());
    ui->player0->setUrl(settings.value("url0", "").toString());
    ui->player1->setUrl(settings.value("url1", "").toString());
    settings.endGroup();
}

void PlayerContainer::writeSettings() {
    QSettings settings("jakecoffman.com", "camcontrol");
    settings.beginGroup("PlayerContainer");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.setValue("vol0", ui->player0->getVolume());
    settings.setValue("vol1", ui->player1->getVolume());
    settings.setValue("url0", ui->player0->getUrl());
    settings.setValue("url1", ui->player1->getUrl());
    settings.endGroup();
}

void PlayerContainer::handleFull0() {
    if (ui->player1->isHidden()) {
        ui->player1->show();
    } else {
        ui->player1->hide();
    }
}

void PlayerContainer::handleFull1() {
    if (ui->player0->isHidden()) {
        ui->player0->show();
    } else {
        ui->player0->hide();
    }
}
