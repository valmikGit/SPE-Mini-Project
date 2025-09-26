FROM ubuntu:22.04

RUN apt-get update && apt-get install -y g++ make

WORKDIR /app
COPY . /app

RUN make

CMD ["./calculator"]