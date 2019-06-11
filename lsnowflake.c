#include <lua.h>
#include <lauxlib.h>
#include <stdlib.h>
#include <stdint.h>
#include "snowflake.h"

/**
 * 根据UUID获得其包含的节点ID
 * @function snowflake.getNodeIdByUUID
 * @param uuid string 分布式唯一ID
 * @return nodeId int 节点ID
 */
static int
lgetNodeIdByUUID(lua_State *L) {
    const char *str = luaL_checkstring(L,1);
    uint64_t i = (uint64_t)atol(str);
    int nodeId = getNodeIdByUUID(i);
    lua_pushinteger(L,nodeId);
    return 1;
}

/**
 * 传递节点ID,生成分布式唯一ID
 * @function snowflake.uuid
 * @param nodeId int 节点ID
 * @return uuid uint64 分布式唯一ID
 */
static int
luuid(lua_State *L) {
    int nodeId = luaL_checkinteger(L,1);
    uint64_t id = uuid(nodeId);
	lua_pushinteger(L, id);
    return 1;
}


LUAMOD_API int
luaopen_snowflake_core(lua_State *L) {
    luaL_checkversion(L);
    luaL_Reg l[] = {
        {"getNodeIdByUUID",lgetNodeIdByUUID},
        {"uuid",luuid},
        {NULL,NULL},
    };

    luaL_newlib(L,l);
    return 1;
}
