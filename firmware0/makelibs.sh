cd lib/avr-can-lib
git submodule init
git submodule update
git checkout atmega328p_setup
cd src/
make lib
cd ../../
