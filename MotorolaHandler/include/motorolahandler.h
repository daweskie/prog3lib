#ifndef MOTOROLAHANDLER_H_INCLUDED
#define MOTOROLAHANDLER_H_INCLUDED

#include "serialPackets.h"
#include "serial_driver.h"

/*
Motorola protocol driver library
*/

typedef struct {
    int stNone,
    int stSync,
    uint8_t st1,
    uint8_t stAddress,
    uint8_t stCmd,
    uint16_t stDatalen,
    uint16_t stData,
    int stCrc,
   } State;


/*
get packets from pool
*/
typedef struct {
    const ....                //callback?
} MotorolaProtocolDriver;

/*
initialize a new object for analyzing
*/
void InitMotorolaObj(MotorolaProtocolDriver *driver, int max_packet_size, int mtu, ...?? );
/*
Sending packets to COM port
*/

int SendMotorolaPacket(MotorolaProtocolDriver *driver, uint8_t address, uint8_t command, uint16_t dlen, uint16_t data);


#endif // MOTOROLAHANDLER_H_INCLUDED
