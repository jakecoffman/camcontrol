#include <utility>

/*
* VLC-Qt Simple Player
* Copyright (C) 2015 Tadej Novak <tadej@tano.si>
*/

#ifndef SIMPLEPLAYER_H_
#define SIMPLEPLAYER_H_

#include <QWidget>

namespace Ui {
    class SimplePlayer;
}

class VlcInstance;
class VlcMedia;
class VlcMediaPlayer;

class EqualizerDialog;

class SimplePlayer : public QWidget
{
    Q_OBJECT
public:
    explicit SimplePlayer(QWidget *parent = nullptr);
    ~SimplePlayer() override;

    void setVolume(int v) { _volume = v; }
    int getVolume() { return _volume; }
    void setUrl(QString);
    QString getUrl() { return _url; }

private slots:
    void openLocal();
    void openUrl();

private:
    Ui::SimplePlayer *ui;

    VlcInstance *_instance;
    VlcMedia *_media;
    VlcMediaPlayer *_player;

    EqualizerDialog *_equalizerDialog;

    int _volume;
    QString _url;
};

#endif // SIMPLEPLAYER_H_
