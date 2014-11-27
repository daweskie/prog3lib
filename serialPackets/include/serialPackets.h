#ifndef SERIALPACKETS_H_INCLUDED
#define SERIALPACKETS_H_INCLUDED

/**  -----Structures------ */

/**	Structure of Packets
  address: the destination of the Packet
  data: what the Packet contains
  n: the size of data */

struct Packet{
char *address;
char *data;
int n;
}

/**Structure of Unused */

struct Unused{
    /** Tail queue un_head. */
    struct un_tailhead *un_headp;

    /** TAILQ declaration */
    TAILQ_HEAD(un_tailhead, Packet) un_head;

    /**  Mutex for multithread using  */
    pthread_mutex_t mutex;

    /** Current size of pool */
    int un_size;

    /** Max number of element in the pool */
    int max_size;

    /** Size of a pool item */
    int packet_size;

    /** number of underflow for statistics. Means of underflow is try to get an element from an empty pool*/
    int un_underflow;

    /** number of overflow for statistics. Means of overflow is try to put back an element to a full pool */
    int un_overflow;
};

/**Structure of Unused */

struct Valid{
    /** Tail queue val_head. */
    struct val_tailhead *val_headp;

    /** TAILQ declaration */
    TAILQ_HEAD(val_tailhead, Packet) val_head;

   /**  Mutex for multithread using */
    pthread_mutex_t mutex;

    /** Current size of pool */
    int val_size;

    /** Max number of element in the pool */
    int max_size;

    /** Size of a pool item */
    int packet_size;

    /** number of underflow for statistics. Means of underflow is try to get an element from an empty pool*/
    int val_underflow;

    /** number of overflow for statistics. Means of overflow is try to put back an element to a full pool */
    int val_overflow;
};

/**  ------Initializes and sizes------- */

/** Initialize an "unused pool" */
struct Unused *un_pool_init(int un_size, int packet_size);

/** Initialize an "valid pool" */
struct Valid *val_pool_init(int val_size, int packet_size);

/** Current size of Unused */
int un_size(struct Unused *unused);

/** Current size of Valid */
int val_size(struct Valid *valid);

/** Max size of pools */
int pool_max_size(struct Unused *unused);
int pool_max_size(struct Valid *valid);

/**  -----Errors------ */

/** Unused is empty (part of underflow check)*/
int un_is_empty(struct Unused *unused);

/** Valid is empty (part of underflow check)*/
int val_is_empty(struct Valid *valid);

/** Underflow in Unused */
int un_underflow(struct Unused *unused);

/** Underflow in Valid */
int val_underflow(struct Valid *valid);

/** Overflow in Unused */
int un_overflow(struct Unused *unused);

/** Overflow in Valid */
int val_overflow(struct Valid *valid);


/** --------------------Actual beadando--------------------- */

/** Gets packet to Unused
    @param the pool.  It can be NULL
    @return the element or NULL if pool is NULL or pool is empty

*/
struct Packet *unused_get(struct Unused *unused);

/**Put back packet to Unused
    @param the pool.  It can be NULL
    @param the item to put back. It can be NULL.

*/
void unused_give(struct Unused *unused, struct Packet *packet);

/** Gets packet to Valid
    @param the pool.  It can be NULL
    @return the element or NULL if pool is NULL or pool is empty

*/
struct Packet *valid_get(struct Valid *valid);

/**Gives packet from Unused
    @param the pool.  It can be NULL
    @return the element or NULL if pool is NULL or pool is empty
*/
void valid_give(struct Valid *valid, struct Packet *packet);

#endif // SERIALPACKETS_H_INCLUDED






struct PacketFifo *spInit(unsigned int maxPackets, u_int16_t mtu);
int spClose(struct PacketFifo *fifo);
u_int16_t spGetMtu(struct PacketFifo *fifo);
int spGetMaxPackets(struct PacketFifo *fifo);
struct Packet *spGetPacketFromPool(struct PacketFifo *fifo);
void spRecycle(struct PacketFifo *fifo, struct Packet *packet);
bool spIsValidPackets(struct PacketFifo *fifo);
struct Packet *spGetPacket(struct PacketFifo *fifo);
int spPutPacket(struct PacketFifo *fifo, struct Packet *packet);
long spGetAllPacketCounts(struct PacketFifo *fifo);
long spGetErrorPacketCounts(struct PacketFifo *fifo);
long spGetOverrunCounts(struct PacketFifo *fifo);
void spIncErrorCounts(struct PacketFifo *fifo);
void spIncOverrunCounts(struct PacketFifo *fifo);
