//
// Created by guust on 5/28/23.
//

#include <stdio.h>

#ifdef _WIN32
int main(){
    printf("Port reader currently not supported for windows\n");
    return 0;
}
#endif


#ifdef linux

#define SERIALTERMINAL      "/dev/ttyUSB0"

#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <dsmr/parser.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

int set_interface_attribs(int fd, int speed) {
    struct termios tty;

    if (tcgetattr(fd, &tty) < 0) {
        printf("Error from tcgetattr: %s\n", strerror(errno));
        return -1;
    }

    cfsetospeed(&tty, (speed_t) speed);
    cfsetispeed(&tty, (speed_t) speed);

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


int main() {
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


    size_t current_bytes = 0;
    char read_buf[4096];
    int start_msg = -1;
    int end_msg = -1;
    int ctr = 0;
    memset(&read_buf, '\0', sizeof(read_buf));
    printf("Starting to listen\n");
    while (1) {
        char single_read_buf[256];
        size_t num_bytes = read(fd, &single_read_buf, sizeof(single_read_buf));
        current_bytes += num_bytes;
        for (int i = 0; i < num_bytes; ++i) {
            char new_char = single_read_buf[i];
            if (new_char == '/') {
                if (start_msg == -1) {
                    start_msg = ctr + i;
                } else {
                    end_msg = ctr + i - 1;
                }
            }
            read_buf[ctr] = new_char;
            ctr++;
        }
        if (end_msg > -1 && start_msg > -1) {
            printf("\n=====================================================\n");
            printf("Start msg: %d end msg: %d size of packet: %d\n", start_msg, end_msg, end_msg - start_msg);
            int size =  end_msg -start_msg;
            char data[size];
            memset(&data, '\0', sizeof(data));
            printf("Amount of bytes: %d\n",size);
            int idx =0;
            for (int i = start_msg; i < end_msg; ++i) {
                data[idx] = read_buf[i];
                idx++;
            }
            parse_data(data,size);
            memset(&read_buf, '\0', sizeof(read_buf));

            start_msg = -1;
            end_msg = -1;
            ctr =0;
        }


    }


}

#endif
