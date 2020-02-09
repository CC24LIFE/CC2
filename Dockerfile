FROM ubuntu:16.04
#for KLEE
RUN apt-get update -y && \
    apt-get install build-essential curl libcap-dev git cmake libncurses5-dev python-minimal python-pip unzip libtcmalloc-minimal4 libgoogle-perftools-dev libsqlite3-dev -y && \
    apt-get install clang-6.0 llvm-6.0 llvm-6.0-dev llvm-6.0-tools -y && \
    apt-get install python3 -y && \
    git clone https://github.com/Z3Prover/z3 && \
    cd /z3 && \
    python3 scripts/mk_make.py --python && \
    cd /z3/build  && \
    make && make install  

WORKDIR /
RUN git clone https://github.com/FedericoAureliano/klee  && \
    cd /klee  && \
    git checkout Nick  && \
    mkdir build  && \
    cd /klee/build  && \
    pip install lit && apt-get install doxygen zlib1g-dev -y  && \
    cmake -DLLVM_CONFIG_BINARY=/usr/bin/llvm-config-6.0 .. -DENABLE_SOLVER_Z3=ON ..  && \
    make install
WORKDIR /bin
#For CBMC V11
ADD https://www.cprover.org/cbmc/download/cbmc-5-11-linux-64.tgz .
RUN tar xfz cbmc-5-11-linux-64.tgz && rm cbmc-5-11-linux-64.tgz
#For SeaHORN
WORKDIR /
RUN git clone https://github.com/seahorn/seahorn && \
    cd /seahorn && \
    git checkout deep-dev-5.0 && mkdir build && \
    cd /seahorn/build && \
    mkdir /clang-5.0 && \
    curl -s http://releases.llvm.org/5.0.0/clang+llvm-5.0.0-linux-x86_64-ubuntu16.04.tar.xz \ 
    | tar -xJf - -C /clang-5.0 --strip-components=1 && \
    apt install ninja-build libgmp-dev libgraphviz-dev -y && \
    apt-get install libboost-all-dev subversion -y && \
    cmake -DCMAKE_INSTALL_PREFIX=run -DCMAKE_BUILD_TYPE="Release" -GNinja ../ && \
    cmake --build . && \
    cmake --build . --target extra && cmake .. && \
    cmake --build . --target crab && cmake .. && \
    cmake --build . --target install && \ 
    cmake --build . --target package && \ 
    # symlink clang (from base image)
    ln -s /clang-5.0/bin/clang run/bin/clang && \
    ln -s /clang-5.0/bin/clang++ run/bin/clang++
ENV PATH "/seahorn/build/run/bin:$PATH"



#CIL
WORKDIR /
RUN apt-get install perl ocaml ocaml-findlib opam -y && \
    opam init && \
    opam update && \
    opam depext conf-m4.1 && \
    opam install cil -y && \
    git clone https://github.com/cil-project/cil && \
    cd /cil && \
    ./configure && make && make install && \
    cd / 

#CC2 direct deps
RUN apt-get install python3-pip -y && \
    pip3 install setuptools  && \
    pip3 install pycparser  && \

ARG TIMING=1
RUN apt-get install time runlim -y

#CC2
ARG NO_CACHE=1
RUN git clone https://github.com/CC24LIFE/CC2 && \
    cd /CC2 && \
    cd /CC2/deps/mlscript && \
    make && \
    cd /CC2  && \
    python3 setup.py install

#RUN useradd -ms /bin/bash ccuser && echo ccuser:CC | chpasswd 
WORKDIR /CC2
USER root