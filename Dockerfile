FROM ubuntu:18.04

RUN apt update && DEBIAN_FRONTEND=noninteractive apt install -y g++ git cmake nlohmann-json-dev libarmadillo-dev libboost-all-dev gnuplot qt5-default libgtest-dev qtbase5-dev qtdeclarative5-dev

RUN git clone https://github.com/dstahlke/gnuplot-iostream.git /usr/local/include/gnuplot-iostream
RUN cd /usr/local/include/gnuplot-iostream && make

# docker stop mcsm | true && docker build -t mcsm . && docker run --rm -v $PWD:/root/ --name mcsm --entrypoint sleep -d mcsm infinity && docker exec -it mcsm bash
