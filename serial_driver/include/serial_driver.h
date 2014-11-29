/*
 * Copyright (C) Bittner Péter, Horváth Péter
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include<termios.h>
#include<errno.h>
#include<unistd.h>
#include "default.h"

int portStatus; //port

/** serial port setups
    @variable: port: name of the device. (exp.: "COM2/TTYS2") //def. is COM0
    @variable: baud_rate: Bits of seconds number. (exp.: B115200) //def. is B9600
    @variable: databits: Bits of the data packet's lenght. (exp.: 7) // def. is 8
    @variable: stopbits: Packet's end signature bit. (exp.: 2) //def. is 1
    @variable: parity: Error detecting bit at the end of the packet. (exp. odd) // def. is noparity
*/
struct port_setups{
    char port[50];
    int baud_rate;
    int databits;
    int stopbits; // def stopbits=1 other:CSTOPB
    char parity //def noparity others: PARENB, PARODD
}port_setup;

/** Serial port standard setups from termios.h: exp: no read, no write
*/
struct termios oldtio;

/** Serial port configure from the config file, or if !config use default.h setups
*/
struct termios newtio{
    newtio.c_cflag = baud_rate | databits | stopbits | parity | CREAD;
    newtio.c.lfalg &= ~(ICANON | ECHO | ECHOE | ISIG);
    newtio.c_iflag = IGNPAR;

};

/** Serial port initialization from config
 @param: port: (device on the port)
 @return: 0 if no port with this name, 1 if the port is available
*/
int serialInit(char *port){}

/** Open serial port with the configured setups
    @param: port: The port name form the config, def: "COM0"
    @param: termios newtio: The new port setups from config, or def values.
*/
int open_port(char *port, struct termios newtio){}

/** Close serial port with the configured setups
    @param: port: The port name form the config, def: "COM0"
    @param: termios oldtio: The port setups to the standard values. //no read, no writes to the port
*/
void close_port(char *port, struct termios oldtio){}

/** Read data from port
    @param: portStatus: The serial port configs.
    @buffer: Pointer to the buffer where datas can write.
    @datalenght: The lenght of the buffer's size.
*/
int readfromPort(int portStatus, char *buffer, int datalenght){}

/** Write data to port
    @param: portStatus: The serial port configs.
    @buffer: Pointer to the buffer where datas can write.
    @datalenght: The lenght of the buffer's size.
*/
int writetoPort(int portStatus, char *buffer, int datalenght){}

/*
serial_driver library

*/

