FROM ubuntu:18.10
RUN apt update && DEBIAN_FRONTEND=noninteractive apt install -y g++ git cmake nlohmann-json-dev libarmadillo-dev libboost-all-dev gnuplot libgtest-dev

WORKDIR /usr/local/

RUN apt install git -y
RUN git clone https://github.com/dstahlke/gnuplot-iostream.git /gnuplot-iostream
RUN cd /gnuplot-iostream && make

CMD ["sleep", "infinity"]
# docker stop mcsm | true && docker build -t mcsm . && docker run --rm -v $PWD:/usr/local/ --name mcsm -d mcsm && docker exec -it mcsm bash
