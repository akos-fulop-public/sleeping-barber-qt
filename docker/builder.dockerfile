FROM ubuntu:22.04

RUN apt update && \
DEBIAN_FRONTEND=noninteractive apt upgrade -y && \
DEBIAN_FRONTEND=noninteractive apt install -y cmake build-essential qt6-base-dev libgtest-dev

WORKDIR /app
