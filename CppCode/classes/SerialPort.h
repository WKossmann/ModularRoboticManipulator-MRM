/* 
 * File:   SerialPort.h
 * Author: Daniel Filgueiras 
 *
 * Created on April 15, 2014, 11:54 PM
 */

#ifndef SERIALPORT_H
#define	SERIALPORT_H

#include <string.h>
#include <errno.h>
#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/signal.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <sys/io.h>
#include <string>
#include <assert.h>

//Ver ajuda em: http://en.wikibooks.org/wiki/Serial_Programming/termios
#define DEFAULT_DEVICE "/dev/ttyUSB0"
#define _POSIX_SOURCE 1 /* POSIX compliant source */

//int wait_flag = true; //TRUE while no signal received

//void signal_handler_IO(int status)//definition of signal handler
//{
//    printf("received SIGIO signal.\n");
//    wait_flag = false;
//}

class SerialPort {
private:
    int fd, res;
    struct termios oldtio, newtio;
    struct sigaction saio; /* definition of signal action */
    char buf[255];
    bool asyncmode;
public:

    SerialPort() {
        fd = 0;
        asyncmode = false;
    }

    ~SerialPort() {
        closePort();
    }

    SerialPort& set(int baudrate = B19200, int mode = 0) {
        int rc;

        if ((rc = tcgetattr(fd, &oldtio)) < 0) {
            fprintf(stderr, "failed to get attr: %d, %s\n", fd, strerror(errno));
        }
        
        tcflush(fd, TCIFLUSH);

        
        switch (mode) {
            case 0:
   
                cfsetispeed(&newtio, baudrate);
                cfsetospeed(&newtio, baudrate);

                /* set new port settings for canonical input processing */
                cfmakeraw(&newtio);
                newtio.c_cflag = baudrate;
                newtio.c_cflag |= (CLOCAL | CREAD);   // Enable the receiver and set local mode
                newtio.c_cflag &= ~PARENB;            //No parity
                newtio.c_cflag &= ~CSTOPB;            // 1 stop bit
                newtio.c_cflag &= ~CSIZE;
                newtio.c_cflag |=  CS8; 
                newtio.c_cflag &= ~CRTSCTS;           //Disable hardware control
                newtio.c_lflag &= ~(ICANON | ECHO | ISIG); //Raw modo
                newtio.c_cc[VMIN] = 0; 
                newtio.c_cc[VTIME] = 0;

                break;
            case 1:

                break;
        }


        if((rc = tcsetattr(fd, TCSANOW, &newtio)) < 0){
        fprintf(stderr, "failed to set attr: %d, %s\n", fd, strerror(errno));
        assert(0);
    }
        

        return *this;
    }

    bool openPort(std::string port = "") {

        if (port == "")
            port = DEFAULT_DEVICE;

        /* open the device to be non-blocking (read will return immediatly) */
        fd = open(port.c_str(), O_RDWR | O_NOCTTY | O_NDELAY | O_NONBLOCK);
        
        if (fd == -1) {
            fprintf(stderr, "openPort: Unable to open %s %s\n", port.c_str(),strerror(errno));
            //assert(0);
        }

        fcntl(fd, F_SETFL, FNDELAY);
        if (fd < 0)
            return false;

        return true;
    }
    
    bool isOpen() { 
        if(fd>0) return true;
        
        return false;
    }
    

    SerialPort& raw(bool v,bool asyncmodeIn=false) {
#if 0        
        asyncmode=asyncmodeIn;
        if (v == true) {
            if (fd > 0) {
                if (asyncmode) {
                    //install the serial handler before making the device asynchronous
                    saio.sa_handler = signal_handler_IO;
                    sigemptyset(&saio.sa_mask); //saio.sa_mask = 0;
                    saio.sa_flags = 0;
                    saio.sa_restorer = NULL;
                    sigaction(SIGIO, &saio, NULL);

                    // allow the process to receive SIGIO
                    fcntl(fd, F_SETOWN, getpid());
                    // Make the file descriptor asynchronous (the manual page says only
                    // O_APPEND and O_NONBLOCK, will work with F_SETFL...)
                    fcntl(fd, F_SETFL, FASYNC);
                } else
                    fcntl(fd, F_SETFL, FNDELAY);
            }

        } else {
            if (fd > 0)
                fcntl(fd, F_SETFL, 0);
        }
#endif
        return *this;
    }

    void closePort() {
        if (fd != 0) {
            tcsetattr(fd, TCSANOW, &oldtio);
            close(fd);
        }
    };

    void readPort(unsigned char *buf, int Nmax, int &res) {
        res = read(fd, buf, Nmax);
    }

    int writePort(unsigned char *buf, int N) {

        return write(fd, buf, N);
    }
};


#endif	/* SERIALPORT_H */

