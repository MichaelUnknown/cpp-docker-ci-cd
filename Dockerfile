# build
FROM buildpack-deps:stable as webapi-build
RUN set -eux; \
    apt-get update; \
    apt-get install -y --no-install-recommends \
    cmake \
    libboost-all-dev \
    ninja-build \
    ; \
    rm -rf /var/lib/apt/lists/*
COPY . .
RUN cmake -S . -B build -G Ninja -D CMAKE_BUILD_TYPE=Release
RUN cmake --build build

# deploy
FROM debian:stable-slim as webapi-run
WORKDIR /app
COPY --from=webapi-build /build/WebAPI .
CMD ["./WebAPI"]
