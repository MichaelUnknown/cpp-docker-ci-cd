# C++ Docker CI/CD example

This repository contains minimal example of a WebAPI built with C++ and complete Docker CI/CD support via GitHub actions and DockerHub.

- Multi-Platfrom support with Docker via `Buildx`/`docker/setup-buildx-action` and `docker/build-push-action`
  - In this example, we support `linux-x86_64` and `linux-arm64`, but other options are possible as well. To see the list of available platforms, look at the output of `docker/setup-buildx-action` and `docker/setup-qemu-action` in the GitHub action log. Example output:
    `linux/amd64,linux/arm64,linux/riscv64,linux/ppc64le,linux/s390x,linux/386,linux/mips64le,linux/mips64,linux/arm/v7,linux/arm/v6`
- Multi-Stage build to achieve minimal application (Docker image) size
- Automatic CI/CD pipeline with GitHub actions
  - Cache Docker builds with GitHub actions
  - Automatic upload to DockerHub

## Setup

You need to specify two GitHub Secrets in your project settings after cloning the repository:

- `DOCKERHUB_USERNAME`: your DockerHub user name
- `DOCKERHUB_TOKEN`: a DockerHub access token (to create one, go to DockerHub Account settings, Security, Access Tokens)

Adjust the `docker-ci.yml` and `docker-cd.yml` and the `Dockerfile`. Add your own code and configure/build instructions.
