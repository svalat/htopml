FROM qnib/uplain-init:14.04 AS hwloc

RUN apt-get update \
 && apt-get install -y cmake wget patch automake libcairo-dev

## hwloc
ARG HWLOC_URL=https://www.open-mpi.org/software/hwloc
ARG HWLOC_VER=1.9
ARG HWLOC_VER_PATCH=1
RUN echo ${HWLOC_URL}/v${HWLOC_VER}/downloads/hwloc-${HWLOC_VER}.${HWLOC_VER_PATCH}.tar.gz \
 && wget -qO- ${HWLOC_URL}/v${HWLOC_VER}/downloads/hwloc-${HWLOC_VER}.${HWLOC_VER_PATCH}.tar.gz \
    |tar xfz - -C /usr/local/src/
COPY ./extern-deps /usr/local/extern-deps
RUN cd /usr/local/src/hwloc-${HWLOC_VER}.${HWLOC_VER_PATCH} \
 && patch -p1 < /usr/local/extern-deps/hwloc-${HWLOC_VER}.${HWLOC_VER_PATCH}-0001-Add-native-svg-support.patch
RUN cd /usr/local/src/hwloc-${HWLOC_VER}.${HWLOC_VER_PATCH} \
 && ./configure --prefix=/usr/local/hwloc \
 && make \
 && make install

FROM qnib/uplain-init:14.04 AS htopml
COPY --from=hwloc /usr/local/hwloc/ /usr/
RUN apt-get update \
 && apt-get install -y cmake wget patch build-essential automake
COPY . /usr/local/htopml/
WORKDIR /usr/local/htopml/build/
RUN ../configure --prefix=/usr/local/htopml --with-hwloc=/usr \
 && make \
 && make install

FROM qnib/uplain-init:14.04
ENV SKIP_ENTRYPOINTS=true
COPY --from=hwloc /usr/local/hwloc/ /usr/
COPY --from=htopml /usr/local/htopml/bin/ /usr/bin/
COPY --from=htopml /usr/local/htopml/lib /usr/local/htopml/lib

CMD ["htopmld"]
