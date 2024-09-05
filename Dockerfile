# Usare un'immagine base con supporto grafico
FROM ubuntu:22.04

# Installare le dipendenze necessarie
RUN apt-get update && apt-get install -y \
    build-essential \
    libqt5charts5-dev \
    libqt5core5a \
    libqt5gui5 \
    libqt5widgets5 \
    libqt5network5 \
    libqt5xml5 \
    libqt5dbus5 \
    libqt5sql5 \
    libx11-dev \
    libxext-dev \
    libxrandr-dev \
    libxrender-dev \
    libxfixes-dev \
    libxcursor-dev \
    libxinerama-dev \
    qtbase5-dev \
    qtchooser \
    qt5-qmake \
    qtbase5-dev-tools \
    && apt-get clean

# Copiare il repository nell'immagine Docker, e spostarsi nella directory dei sorgenti
COPY . .
WORKDIR /AeroSimulator/src

# Compilare l'applicazione
RUN qmake .
RUN make

# Eseguire l'applicazione
CMD ["./AeroSimulator"]
