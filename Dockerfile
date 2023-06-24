# Устанавливаем базовый образ
FROM ubuntu:latest

ENV TZ=Europe/Moscow
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

# Устанавливаем зависимости
RUN apt-get update && apt-get install -y \
    build-essential \
    qtbase5-dev \
    qtchooser \
    qt5-qmake \
    qtbase5-dev-tools \
    libqt5sql5-mysql \
    mysql-server \
    && rm -rf /var/lib/apt/lists/*

# Копируем файлы проекта в контейнер
WORKDIR /root/server/
COPY *.cpp /root/server/
COPY *.h /root/server/
COPY *.pro /root/server/

# Устанавливаем и собираем проект
RUN qmake echoServer.pro
RUN make

# Запускаем MySQL сервер
RUN service mysql start

# Задаем точку входа
ENTRYPOINT ["./echoServer"]
