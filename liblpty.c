/*
	Copyright (c) 2015 Tavish Naruka <tavish@baseapp.com>
*/

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "liblpty.h"

int lpty_load_lib(lua_State *L)
{
	luaL_dostring(L, "lpty = require 'lpty'");	
	lua_getglobal(L, "lpty");

	if (lua_type(L, -1)!=LUA_TTABLE)
		return luaL_error(L, "lpty module is not loaded");
	lua_pop(L, 1);

	return 0;
}

/*
	gets new pty, sets a global, "name" to that
*/
int lpty_new(lua_State *L, const char * name)
{
	if(name == NULL)
		return -1;

	lua_getglobal(L, "lpty");

	if (lua_type(L, -1)!=LUA_TTABLE)
		return luaL_error(L, "lpty module is not loaded");
	lua_getfield(L, -1, "new");
	if (lua_type(L, -1)!=LUA_TFUNCTION)
		return luaL_error(L, "lpty module has no new method");
	
	// This removes the lpty table from the stack by replacing stack top on -2
	lua_replace(L, -2);

	// calls lpty.new
	lua_pcall(L, 0, 1, 0);

	// sets p=lpty.new(), then pops it
	lua_setglobal(L, name);

	//check if p is set(success)
	int retval = 0; // 0 error, 1 ok
	lua_getglobal(L, name);
	if(lua_isnil(L, -1))
		retval = 0;
	else
		retval = 1;

	// pop "p"
	lua_pop(L, 1);

	return retval;
}

// command is {"ls", "-alh", NULL} etc. null is end of list
int lpty_startproc(lua_State *L, const char * name, char * command[])
{
	// get lpty.startproc
	// push p to stack
	// push command to stack

	// precheck on command
	if( (command==NULL) || (command[0]==NULL))
	{
		return -1;
	}

	lua_getglobal(L, "lpty");

	if (lua_type(L, -1)!=LUA_TTABLE)
		return luaL_error(L, "lpty module is not loaded");
	lua_getfield(L, -1, "startproc");
	if (lua_type(L, -1)!=LUA_TFUNCTION)
		return luaL_error(L, "lpty module has no startproc method");
	
	// This removes the lpty table from the stack
	lua_replace(L, -2);

	lua_getglobal(L, name);

	int i = 0;
	while(command[i]!=NULL)
	{
		lua_pushstring(L, command[i]);
		i++;
	}

	int retval = lua_pcall(L, 1+i, 1, 0);
	lua_pop(L, 1);

	return retval;
}


int lpty_readok(lua_State * L, const char * name)
{
	// get readok function
	// push p
	// test lua_isboolean and 1
	lua_getglobal(L, "lpty");

	if (lua_type(L, -1)!=LUA_TTABLE)
		return luaL_error(L, "lpty module is not loaded");
	lua_getfield(L, -1, "readok");
	if (lua_type(L, -1)!=LUA_TFUNCTION)
		return luaL_error(L, "lpty module has no readok method");
	// This removes the lpty table from the stack
	lua_replace(L, -2);

	lua_getglobal(L, name);

	lua_pcall(L, 1, 1, 0);

	int retval;
	if(lua_isboolean(L, -1) && (lua_toboolean(L, -1)==1))
		retval = 1;
	else
		retval = 0;

	lua_pop(L, 1);

	return retval;
}


int lpty_sendok(lua_State *L, const char * name)
{
	lua_getglobal(L, "lpty");

	if (lua_type(L, -1)!=LUA_TTABLE)
		return luaL_error(L, "lpty module is not loaded");
	lua_getfield(L, -1, "sendok");
	if (lua_type(L, -1)!=LUA_TFUNCTION)
		return luaL_error(L, "lpty module has no sendok method");
	// This removes the lpty table from the stack
	lua_replace(L, -2);

	lua_getglobal(L, name);

	lua_pcall(L, 1, 1, 0);

	int retval;
	if(lua_isboolean(L, -1) && (lua_toboolean(L, -1)==1))
		retval = 1;
	else
		retval = 0;

	lua_pop(L, 1);

	return retval;
}

int lpty_hasproc(lua_State * L, const char * name)
{
	// get readok function
	// push p
	// test lua_isboolean and 1
	lua_getglobal(L, "lpty");

	if (lua_type(L, -1)!=LUA_TTABLE)
		return luaL_error(L, "lpty module is not loaded");
	lua_getfield(L, -1, "hasproc");
	if (lua_type(L, -1)!=LUA_TFUNCTION)
		return luaL_error(L, "lpty module has no hasproc method");
	// This removes the lpty table from the stack
	lua_replace(L, -2);

	lua_getglobal(L, name);

	lua_pcall(L, 1, 1, 0);

	int retval;
	if(lua_isboolean(L, -1) && (lua_toboolean(L, -1)==1))
		retval = 1;
	else
		retval = 0;

	lua_pop(L, 1);

	return retval;
}


/* pushes string if read to the stack, pop after use */
int lpty_read(lua_State *L, const char * name)
{
	size_t len;
	// get read function
	// push p
	// read
	lua_getglobal(L, "lpty");

	if (lua_type(L, -1)!=LUA_TTABLE)
		return luaL_error(L, "lpty module is not loaded");
	lua_getfield(L, -1, "read");
	if (lua_type(L, -1)!=LUA_TFUNCTION)
		return luaL_error(L, "lpty module has no read method");
	// This removes the lpty table from the stack
	lua_replace(L, -2);

	lua_getglobal(L, name);

	lua_pcall(L, 1, 1, 0);

	if(!lua_isnil(L, -1))
	{
		lua_tolstring(L, -1, &len);
	}
	else
	{
		len=-1;
	}

	return len;
}

/* write data to master side of pty */
int lpty_send(lua_State *L, const char * name, char * buf)
{
	int len;
	// get send function
	// push p
	// push data
	// write
	lua_getglobal(L, "lpty");

	if (lua_type(L, -1)!=LUA_TTABLE)
		return luaL_error(L, "lpty module is not loaded");
	lua_getfield(L, -1, "send");
	if (lua_type(L, -1)!=LUA_TFUNCTION)
		return luaL_error(L, "lpty module has no send method");
	// This removes the lpty table from the stack
	lua_replace(L, -2);

	lua_getglobal(L, name);

	lua_pushstring(L, buf);

	lua_pcall(L, 2, 1, 0);

	if(!lua_isnil(L, -1))
	{
		len = (int)lua_tonumber(L, -1);
	}
	else
	{
		len=-1;
	}

	lua_pop(L, 1);

	return len;
}


// pushes ttyname on stack, pop after use
int lpty_ttyname(lua_State *L, const char * name)
{
	size_t len;
	// get read function
	// push p
	// read
	lua_getglobal(L, "lpty");

	if (lua_type(L, -1)!=LUA_TTABLE)
		return luaL_error(L, "lpty module is not loaded");
	lua_getfield(L, -1, "ttyname");
	if (lua_type(L, -1)!=LUA_TFUNCTION)
		return luaL_error(L, "lpty module has no ttyname method");
	// This removes the lpty table from the stack
	lua_replace(L, -2);

	lua_getglobal(L, name);

	lua_pcall(L, 1, 1, 0);

	if(!lua_isnil(L, -1))
	{
		lua_tolstring(L, -1, &len);
	}
	else
	{
		len=-1;
	}

	return len;
}
