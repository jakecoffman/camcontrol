#include <QFileDialog>
#include <QInputDialog>
#include <QCloseEvent>
#include <QtDebug>

#include <VLCQtCore/Common.h>
#include <VLCQtCore/Instance.h>
#include <VLCQtCore/Media.h>
#include <VLCQtCore/MediaPlayer.h>

#include <curl/curl.h>

#include "EqualizerDialog.h"
#include "SimplePlayer.h"
#include "ui_SimplePlayer.h"

SimplePlayer::SimplePlayer(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::SimplePlayer),
      _media(nullptr),
      _equalizerDialog(new EqualizerDialog(this)),
      _volume(0),
      _url("")
{
    ui->setupUi(this);

    _instance = new VlcInstance(VlcCommon::args(), this);
    _player = new VlcMediaPlayer(_instance);
    _player->setVideoWidget(ui->video);
    _equalizerDialog->setMediaPlayer(_player);

    ui->video->setMediaPlayer(_player);
    ui->volume->setMediaPlayer(_player);
    ui->volume->setVolume(_volume);

    connect(ui->actionOpenUrl, &QAction::triggered, this, &SimplePlayer::openUrl);
    connect(ui->actionPause, &QAction::toggled, _player, &VlcMediaPlayer::togglePause);
    connect(ui->actionStop, &QAction::triggered, _player, &VlcMediaPlayer::stop);
    connect(ui->openUrl, &QPushButton::clicked, this, &SimplePlayer::openUrl);
    connect(ui->stop, &QPushButton::clicked, _player, &VlcMediaPlayer::stop);

    connect(ui->left, &QPushButton::pressed, this, &SimplePlayer::leftPressed);
    connect(ui->left, &QPushButton::released, this, &SimplePlayer::leftReleased);
    connect(ui->right, &QPushButton::pressed, this, &SimplePlayer::rightPressed);
    connect(ui->right, &QPushButton::released, this, &SimplePlayer::rightReleased);
    connect(ui->up, &QPushButton::pressed, this, &SimplePlayer::upPressed);
    connect(ui->up, &QPushButton::released, this, &SimplePlayer::upReleased);
    connect(ui->down, &QPushButton::pressed, this, &SimplePlayer::downPressed);
    connect(ui->down, &QPushButton::released, this, &SimplePlayer::downReleased);

    if (_url.isEmpty()) {
        return;
    }

    _media = new VlcMedia(_url, _instance);
    _player->open(_media);
}

SimplePlayer::~SimplePlayer()
{
    delete _player;
    delete _media;
    delete _instance;
    delete ui;
}

void SimplePlayer::openUrl()
{
    QString url = QInputDialog::getText(this, tr("Open Url"), tr("Enter the URL you want to play"), QLineEdit::Normal, _url);

    if (url.isEmpty())
        return;
    _url = url;
    _media = new VlcMedia(url, _instance);

    _player->open(_media);
}

void SimplePlayer::setUrl(QString s) {
    _url = std::move(s);
    if (_url.isEmpty()) {
        return;
    }
    _media = new VlcMedia(_url, _instance);
    _player->open(_media);
}

static void control(const QString& base, const QString& cmd, const QString& dir) {
    CURL *curl;
    CURLcode res;

    QString url = "http" + base.split("rtsp").at(1) + "/cgi-bin/ptz.cgi?action=" + cmd + "&channel=0&code=" + dir + "&arg1=0&arg2=5&arg3=0";

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.toStdString().c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_DIGEST);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            qDebug() << "curl_easy_perform() failed: " << curl_easy_strerror(res);
        }
        long http_code = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

        curl_easy_cleanup(curl);
    }
}

void SimplePlayer::leftPressed() {
    if (_url.isEmpty()) {
        return;
    }
    control(_url, "start", "Left");
}

void SimplePlayer::leftReleased() {
    if (_url.isEmpty()) {
        return;
    }
    control(_url, "stop", "Left");
}

void SimplePlayer::rightPressed() {
    if (_url.isEmpty()) {
        return;
    }
    control(_url, "start", "Right");
}

void SimplePlayer::rightReleased() {
    if (_url.isEmpty()) {
        return;
    }
    control(_url, "stop", "Right");
}

void SimplePlayer::upPressed() {
    if (_url.isEmpty()) {
        return;
    }
    control(_url, "start", "Up");
}

void SimplePlayer::upReleased() {
    if (_url.isEmpty()) {
        return;
    }
    control(_url, "stop", "Up");
}

void SimplePlayer::downPressed() {
    if (_url.isEmpty()) {
        return;
    }
    control(_url, "start", "Down");
}

void SimplePlayer::downReleased() {
    if (_url.isEmpty()) {
        return;
    }
    control(_url, "stop", "Down");
}

void SimplePlayer::mouseDoubleClickEvent(QMouseEvent *e) {
    e->accept();
    emit toggleFull();
}
