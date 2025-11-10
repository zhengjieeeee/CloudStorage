FROM ubuntu:22.04

# 更换 Ubuntu 国内源（阿里云，适配 22.04 jammy）
RUN sed -i s@/archive.ubuntu.com/@/mirrors.aliyun.com/@g /etc/apt/sources.list && \
    sed -i s@/security.ubuntu.com/@/mirrors.aliyun.com/@g /etc/apt/sources.list

# 环境变量
ENV DEBIAN_FRONTEND=noninteractive
ENV PYTHON_VERSION=3.12
# 配置 pip 国内源（阿里云）
ENV PIP_INDEX_URL=https://mirrors.aliyun.com/pypi/simple/
ENV PIP_TRUSTED_HOST=mirrors.aliyun.com

# 安装依赖
RUN apt update && \
    apt install -y \
    g++ \
    cmake \
    make \
    gdb \
    build-essential \
    python3.12 \
    python3.12-dev \
    python3-pip \
    git \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /code

COPY . .

CMD ["/bin/bash"]

