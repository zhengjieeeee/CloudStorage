FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

# 安装 C++ 编译工具链
RUN apt update && \
    apt install -y \
    g++ \
    cmake \
    make \
    gdb \
    build-essential && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /code

COPY . .

CMD ["/bin/bash"]