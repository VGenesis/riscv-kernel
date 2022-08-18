FROM ubuntu

RUN apt-get update -y
RUN apt-get upgrade -y

RUN apt-get install -y \
    make \
    binutils \
    gcc-riscv64-linux-gnu
                
VOLUME /root/env
WORKDIR /root/env
