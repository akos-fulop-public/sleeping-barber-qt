FROM ubuntu:22.04 AS build

RUN apt update && \
DEBIAN_FRONTEND=noninteractive apt update -y && \
DEBIAN_FRONTEND=noninteractive apt install -y cmake build-essential qt6-base-dev libgtest-dev

WORKDIR /build

COPY . /app
RUN cmake /app
RUN cmake --build .
WORKDIR /artifact
RUN cmake --install /build --prefix /artifact

FROM ubuntu:22.04
RUN apt update && \
DEBIAN_FRONTEND=noninteractive apt update -y && \
DEBIAN_FRONTEND=noninteractive apt install -y qt6-base-dev && \
rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY --from=build /artifact /sleeping-barber

ENTRYPOINT ["/sleeping-barber/app"]
