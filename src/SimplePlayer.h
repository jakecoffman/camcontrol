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

protected:
    void mouseDoubleClickEvent(QMouseEvent *e) override;

private slots:
    void openUrl();
    void leftPressed();
    void leftReleased();
    void rightPressed();
    void rightReleased();
    void upPressed();
    void upReleased();
    void downPressed();
    void downReleased();

signals:
    void toggleFull();

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
