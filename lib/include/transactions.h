#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include <stdint.h>

// Constants
// 1024*1024; used during buffer allocation
#define MAX_TX_SIZE 1048576

/**********
 * HEADER *
 **********/

// Positions
#define POS_TX_HEADER_VERSION 0
#define POS_TX_HEADER_IN_COUNT 2
#define POS_TX_HEADER_OUT_COUNT 4
#define POS_TX_HEADER_LOCK_TIME 6


typedef struct
{
    uint16_t version;
    uint16_t in_count;
    uint16_t out_count;
    uint32_t lock_time;
} tx_header_t;

void tx_header_serialize(tx_header_t *src, uint8_t *dst);


void tx_header_deserialize(uint8_t *src, tx_header_t *dst);


/*********
 * INPUT *
 *********/

// Positions
#define POS_TX_INPUT_OUT_INDEX 0
#define POS_TX_INPUT_REF_TX 2
#define POS_TX_INPUT_PUBKEY 34
#define POS_TX_INPUT_SIG 162

typedef struct
{
    uint16_t out_index;
    uint8_t ref_tx[32];
    uint8_t pubkey[128];
    uint8_t sig[128];
} tx_input_t;

void tx_input_serialize(tx_input_t *src, uint8_t *dst);

void tx_input_deserialize(uint8_t *src, tx_input_t *dst);

/**********
 * OUTPUT *
 **********/

// Positions
#define POS_TX_OUTPUT_OUT_ADDR 0
#define POS_TX_OUTPUT_AMOUNT 32

typedef struct
{
    uint8_t out_addr[32];
    uint32_t amount;
} tx_output_t;


void tx_output_serialize(tx_output_t *src, uint8_t *dst);

void tx_output_deserialize(uint8_t *src, tx_output_t *dst);

/********
 * FULL *
 ********/

// Positions
#define POS_TX_HEADER 0
#define POS_TX_BODY sizeof(tx_header_t)


typedef struct
{
    tx_header_t tx_header;
    tx_input_t **tx_ins;
    tx_output_t **tx_outs;
} tx_t;

uint32_t tx_compute_size(tx_t *tx)
{
    return sizeof(tx_header_t) + (tx->tx_header.in_count)*sizeof(tx_input_t) + (tx->tx_header.out_count)*sizeof(tx_output_t);
}

void tx_serialize(tx_t *src, uint8_t *dst);
void tx_deserialize(uint8_t *src, tx_t *dst);


/*********
 * OTHER *
 *********/

void compute_merkle_root(tx_t **txs, uint32_t tx_count, uint8_t *out);


#endif /* TRANSACTIONS_H */

