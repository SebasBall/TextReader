FROM ubuntu:22.04 AS builder

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    libgl-dev \
    qtbase5-dev \
    libqt5texttospeech5-dev \
    && rm -rf /var/lib/apt/lists/*


WORKDIR /app

COPY . /app

RUN qmake -makefile TextReader.pro && \
    make -j$(nproc)

FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
apt-get install -y --no-install-recommends software-properties-common && \
    add-apt-repository universe && \
    apt-get update && \
    apt-get install -y --no-install-recommends \
    libqt5core5a \
    libqt5gui5 \
    libqt5widgets5 \
    libqt5texttospeech5 \
    libpulse0 \
    libxkbcommon-x11-0 \
    libxcb-icccm4 \
    libxcb-image0 \
    libxcb-keysyms1 \
    libxcb-render-util0 \
    libxcb-shm0 \
    libxcb-sync1 \
    libxcb-xfixes0 \
    libxcb-xinerama0 \
    libxcb-xinput0 \
    libxcb-xkb1 \
    libxrender1 \
    libglx-mesa0 \
    libopengl0 \
    speech-dispatcher \
    speech-dispatcher-espeak-ng \
    espeak-ng \
    espeak-ng-data \
    pulseaudio-utils \
    qtspeech5-speechd-plugin \
    && rm -rf /var/lib/apt/lists/*

RUN apt-get update && \
    apt-get install -y xvfb x11-utils scrot \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY --from=builder /app/TextReader /app/

COPY entrypoint.sh /app/entrypoint.sh

RUN chmod +x /app/TextReader /app/entrypoint.sh

ENV QT_QPA_PLATFORM=xcb

CMD ["/app/entrypoint.sh"]
