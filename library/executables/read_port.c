//
// Created by guust on 5/28/23.
//

#define SERIALTERMINAL      "/dev/ttyUSB0"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <dsmr/parser.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

int set_interface_attribs(int fd, int speed)
{
    struct termios tty;

    if (tcgetattr(fd, &tty) < 0) {
        printf("Error from tcgetattr: %s\n", strerror(errno));
        return -1;
    }

    cfsetospeed(&tty, (speed_t)speed);
    cfsetispeed(&tty, (speed_t)speed);

    tty.c_cflag |= CLOCAL | CREAD;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;         /* 8-bit characters */
    tty.c_cflag &= ~PARENB;     /* no parity bit */
    tty.c_cflag &= ~CSTOPB;     /* only need 1 stop bit */
    tty.c_cflag &= ~CRTSCTS;    /* no hardware flowcontrol */

    tty.c_lflag |= ICANON | ISIG;  /* canonical input */
    tty.c_lflag &= ~(ECHO | ECHOE | ECHONL | IEXTEN);

    tty.c_iflag &= ~IGNCR;  /* preserve carriage return */
    tty.c_iflag &= ~INPCK;
    tty.c_iflag &= ~(INLCR | ICRNL | IUCLC | IMAXBEL);
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);   /* no SW flowcontrol */

    tty.c_oflag &= ~OPOST;

    tty.c_cc[VEOL] = 0;
    tty.c_cc[VEOL2] = 0;
    tty.c_cc[VEOF] = 0x04;

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        printf("Error from tcsetattr: %s\n", strerror(errno));
        return -1;
    }
    return 0;
}


int main()
{
    char *portname = SERIALTERMINAL;
    int fd;
    int wlen;

    fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0) {
        printf("Error opening %s: %s\n", portname, strerror(errno));
        return -1;
    }
    /*baudrate 115200, 8 bits, no parity, 1 stop bit */
    set_interface_attribs(fd, B115200);


    int current_bytes = 0;
    char read_buf [4096];
    int offset=0;
    memset(&read_buf, '\0', sizeof(read_buf));
    while (1){

        char single_read_buf [1024];
        int num_bytes = read(fd, &single_read_buf, sizeof(single_read_buf));
        current_bytes += num_bytes;
        for (int i = 0; i < num_bytes; ++i) {
            read_buf[offset] = single_read_buf[i];
            offset++;
        }
        int ctr =0;
        for (int i = 0; i < 4096; ++i) {
            if(read_buf[i] == '/') {
                ctr++;
            }
        }
        if(ctr > 3){
            FILE* pFile2 = fopen("frames.txt", "a");
            fputs(read_buf, pFile2);
            fputs("\n=============================================\n",pFile2);
            printf("Threshold passed parsing data:  %d bytes\n", current_bytes);
            parse_data(read_buf,num_bytes);
            current_bytes = 0;
            memset(&read_buf, '\0', sizeof(read_buf));
            offset = 0;
        }



       // char to_write [num_bytes];
       // memccpy(to_write,read_buf,0,num_bytes);
    }




}

