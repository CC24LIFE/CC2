# CC2
anonymous repo for CC2 

## Installation Instructions for Docker:
```bash
docker build --build-arg NO_CACHE=$(date +%s) -t cc2/cc2 .
docker run -v `pwd`:/host -it cc2/cc2
```

## Manual Installation Instructions for Ubuntu 16.04
### Prerequisites:
0. Install Python3.5

1. Install Seahorn: https://github.com/seahorn/seahorn/tree/deep-dev-5.0 (possible package decencies are listed in 
the bottom of page)

2.  Installing Klee:
```
sudo apt-get install build-essential curl libcap-dev git cmake libncurses5-dev python-minimal python-pip unzip libtcmalloc-minimal4 libgoogle-perftools-dev libsqlite3-dev
sudo apt-get install clang-6.0 llvm-6.0 llvm-6.0-dev llvm-6.0-tools
sudo pip install lit
git clone https://github.com/FedericoAureliano/klee
cd klee
git checkout Nick
mkdir build
cd build
cmake -DLLVM_CONFIG_BINARY=/usr/bin/llvm-config-6.0 .. -DENABLE_SOLVER_Z3=ON ..
sudo make install
```

3. Install CBMC 5.11: https://www.cprover.org/cbmc/

4. Install OCaml:
```
apt-get install perl ocaml ocaml-findlib
```

5. Install Cil: 
```
git clone https://github.com/kerneis/cil
cd cil
./configure
make
make install
```

6. Install pycparser: 
```
pip install pycparser
```

#### Reve-based Examples:
7. Install Reve through Docker: https://github.com/mattulbrich/llreve/tree/master/reve/reve#docker

8. Install Z3 4.5.0 release (w/ Duality engine):  https://github.com/Z3Prover/z3/releases/tag/z3-4.5.0

9. Record absolute paths, and replace lines 4, 5 in check_reve.py with absolute paths to Reve, Z3 4.5.0 binaries, respectively:  https://github.com/CC24LIFE/CC2/blob/master/CC2/check_reve.py#L4

<!-- 10. Clone pycparser (https://github.com/eliben/pycparser/) and replace lines 1837, 1840 with absolute local path to "pycparser/utils/fake_libc_include": https://github.com/CC24LIFE/CC2/blob/master/CC2/checker_simple.py#L1837 --!>

### Install CC2:
```
git clone https://github.com/CC24LIFE/CC2
cd CC2
cd deps/mlscript
make 
cd ../..
sudo python3 setup.py install
```

## Usage:
```bash
CC2 --old={V1_file} --new={V2_file} --lib={library_name} --client={client_name}
```
optional argument:
- `--engine`: Choose a verification engine from CBMC, KLEE and SEAHORN (default: CBMC).
- `--unwind`: The number of loop unwinding for CBMC, and the number of paths to be explored for KLEE (default: 100). 
- `--BMC-incremental`: Enable BMC to incrementally detect program bound until reaching unwind limit (default True).
- `--hybrid-solving`Use a combination of verification engines(default False).
- `--concurrent`: Enable concurrent verification(default False).

## Examples:
```bash
CC2 --new=instances/eq/ultra_prime_sum/new.c --old=/instances/eq/ultra_prime_sum/old.c --lib=lib --client=client --engine=CBMC --unwind=20 --concurrent=True --hybrid-solving=True 
```
