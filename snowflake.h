#ifndef snowflake_h
#define snowflake_h

#include <stdint.h>
extern uint64_t getTimestampByUUID(uint64_t uuid);
extern int getNodeIdByUUID(uint64_t uuid);
extern int getSequenceByUUID(uint64_t uuid);
extern uint64_t composeUUID(uint64_t a,uint64_t b,uint64_t c);
extern uint64_t uuid(int nodeId,int* sequence);
#endif