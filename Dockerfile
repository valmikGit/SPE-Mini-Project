FROM ubuntu:22.04 AS build

RUN apt-get update && apt-get install -y g++ make

WORKDIR /app
COPY . /app

RUN make

FROM scratch

COPY --from=build /app/calculator /bin/calc

CMD ["/bin/calc"]