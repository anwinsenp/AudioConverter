AudioConverter
===========
- Command line tool to convert wav audio files from a given directory to mp3 audio files.
- This application need Lame MP3 encoder libary
- Build & install lame library from source code:
```sh
$ curl -L -O http://downloads.sourceforge.net/project/lame/lame/3.99/lame-3.99.5.tar.gz
$ tar -zxvf lame-3.99.5.tar.gz
$ rm -r lame-3.99.5.tar.gz
$ cd lame-3.99.5

Installing
$ ./configure
$ make
$ sudo make install
```
- Building AudioConverter:
```sh
$ git clone https://github.com/anwinsenp/AudioConverter.git
$ cd AudioConverter
$ mkdir build
$ cd build
$ cmake -DLAME_INCLUDE_DIR=<path to lame.h> ../
$ cmake --build .
```
- AudioConverter Usage:
```sh
$./AudioConverter <path to wav files>
```
