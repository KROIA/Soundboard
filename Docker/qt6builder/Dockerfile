# Building QT 6 on ubuntu https://www.ics.com/blog/how-build-qt-620-source-ubuntu-linux
# Dockerfile help: https://www.linode.com/docs/guides/how-to-use-dockerfiles/

FROM ubuntu:latest
MAINTAINER Alex Krieg alex.krieg@ost.ch

# update first
RUN apt-get update

# install the wget command tool
RUN apt-get install wget -y

# install the dependencies to build QT6
RUN apt install bison build-essential clang flex gperf libatspi2.0-dev libbluetooth-dev libclang-dev libcups2-dev libdrm-dev libegl1-mesa-dev libfontconfig1-dev libfreetype6-dev libgstreamer1.0-dev libhunspell-dev libnss3-dev libopengl-dev libpulse-dev libssl-dev libts-dev libx11-dev libx11-xcb-dev libxcb-glx0-dev libxcb-icccm4-dev libxcb-image0-dev libxcb-keysyms1-dev libxcb-randr0-dev libxcb-render-util0-dev libxcb-shape0-dev libxcb-shm0-dev libxcb-sync-dev libxcb-util-dev libxcb-xfixes0-dev libxcb-xinerama0-dev libxcb-xkb-dev libxcb1-dev libxcomposite-dev libxcursor-dev libxdamage-dev libxext-dev libxfixes-dev libxi-dev libxkbcommon-dev libxkbcommon-x11-dev libxkbfile-dev libxrandr-dev libxrender-dev libxshmfence-dev libxshmfence1 llvm ninja-build nodejs python-is-python3 python2 -y

# download and build Cmake
RUN wget https://github.com/Kitware/CMake/releases/download/v3.21.2/cmake-3.21.2.tar.gz
RUN tar xf cmake-3.21.2.tar.gz
# RUN cd cmake-3.21.2
RUN cd cmake-3.21.2 && ./configure
RUN cd cmake-3.21.2 && make
RUN cd cmake-3.21.2 && make install
# RUN cd ..
RUN rm -rf cmake-3.21.2

# download QT 6.3.2
RUN wget https://download.qt.io/official_releases/qt/6.3/6.3.2/single/qt-everywhere-src-6.3.2.tar.xz