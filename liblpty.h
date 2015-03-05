#ifndef LIBLPTY_H1
#define LIBLPTY_H1

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

int lpty_load_lib(lua_State *L);
int lpty_new(lua_State *L, const char * name);
int lpty_startproc(lua_State *L, const char * name, char * command[]);
int lpty_readok(lua_State * L, const char * name);
int lpty_sendok(lua_State *L, const char * name);
int lpty_hasproc(lua_State * L, const char * name);
int lpty_read(lua_State *L, const char * name);
int lpty_send(lua_State *L, const char * name, char * buf);

#endif