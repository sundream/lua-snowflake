/*
 * 64位分布式id生成,由snowflake算法实现,构成如下
 *1bit  41bit     10bit     12bit
 *+--+---------+---------+--------+
 *|0 |timestamp|nodeId   |sequence|
 *+--+---------+---------+--------+
 */

#include <stdio.h>
#include <stdint.h>
#include <sys/time.h>
#include "snowflake.h"

#define TIMESTAMP_BIT (41)
#define NODEID_BIT (10)
#define SEQUENCE_BIT (12)
#define TIMESTAMP_MASK ((1ul<<TIMESTAMP_BIT)-1)
#define NODEID_MASK ((1<<NODEID_BIT)-1)
#define SEQUENCE_MASK ((1<<SEQUENCE_BIT)-1)

static uint64_t genTimestamp() {
    struct timeval tv;
    gettimeofday(&tv, 0);

    return (uint64_t)tv.tv_sec * 1000 + (uint64_t)tv.tv_usec / 1000;
}

static uint64_t genNodeId(int nodeId) {
    return (uint64_t) (nodeId % (1 << NODEID_BIT));
}

static uint64_t genIncrement(int* sequence) {
    *sequence = (*sequence + 1) & ~(1 << SEQUENCE_BIT);
    return *sequence;
}

uint64_t getTimestampByUUID(uint64_t uuid) {
    return (uuid >> (NODEID_BIT+SEQUENCE_BIT)) & TIMESTAMP_MASK;
}

int getNodeIdByUUID(uint64_t uuid) {
    return (uuid >> SEQUENCE_BIT) & NODEID_MASK;
}

int getSequenceByUUID(uint64_t uuid) {
    return uuid & SEQUENCE_MASK;
}

uint64_t composeUUID(uint64_t a,uint64_t b,uint64_t c) {
    return (a << (NODEID_BIT + SEQUENCE_BIT))
         | (b << SEQUENCE_BIT)
         | c;
}

uint64_t uuid(int nodeId,int* sequence) {
    uint64_t a = genTimestamp();
    uint64_t b = genNodeId(nodeId);
    uint64_t c = genIncrement(sequence);
    return composeUUID(a,b,c);
}
