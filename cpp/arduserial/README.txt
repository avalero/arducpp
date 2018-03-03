Treats the serial port as a stream. It is configured to work straight forward with arduino

You need the libserial-dev on your system

To build link with libserial and libpthread, for example

$> g++ *.cpp -lserial -lpthread
