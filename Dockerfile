# Dockerfile
FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y \
    build-essential \
    g++ \
    make \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Create app dir
WORKDIR /opt/scientific-calculator

# Copy sources
COPY src ./src
COPY tests ./tests
COPY Makefile .
COPY .gitignore .

# Build the app
RUN make build

# Default command: run calculator shell
CMD ["/opt/scientific-calculator/bin/calculator"]