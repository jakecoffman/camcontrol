# camcontrol

I couldn't find an easy way to view multiple security cameras (Amcrest) and also control them, so I built this. 

![screenshot](screenshot.png?raw=true "screenshot")

## building

This project was forked from: https://github.com/vlc-qt/examples/tree/master/simple-player

(Commit fb69be54dd9e7ebedf56799b06e0f2a8153276be)

Quick tips on getting it to build: 

- Install qt to `/usr/local/opt/qt5` and set `CMAKE_PREFIX_PATH` to that
- Download VLC-Qt `$somewhere` and set VLCQt_DIR to `$somewhere/lib/cmake/VLCQt`
- Also set VLCQtCore_DIR to `$somewhere/lib/cmake/VLCQtCore`
