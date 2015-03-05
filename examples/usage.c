#include <stdio.h>
#include <string.h>
#include <time.h>
#include "liblpty.h"


int main (int argc, char **argv) 
{
	//initialize
	lua_State *L = luaL_newstate();
	
	//load libraries
	luaL_openlibs(L);

	// load lpty module
	lpty_load_lib(L);
	
	// create new pty
	if(lpty_new(L, "p")==1)
	{
		printf("new pty opened\n");
	}
	else
	{
		printf("error in lpty.new\n");
	}

	// start process in pty
	char * command[]={"sh", NULL};
	lpty_startproc(L, "p", command);

	int done = 0;
	while(1)
	{

		while(lpty_readok(L, "p"))
		{
			if(lpty_read(L, "p") > 0)
			{
				// todo, handle partial writes and nulls in string
				printf("%s", lua_tostring(L, -1));
				// pop string
				lua_pop(L, 1);
			}

		}
		
		struct timespec sleep_time = {0, 20000000};
		nanosleep(&sleep_time, NULL);

		if(lpty_sendok(L, "p") && (done==1))
		{	
			lpty_send(L, "p", "\x04");
		}

		if(lpty_sendok(L, "p") && !done)
		{
			if(lpty_send(L, "p", "ls -alh\n") > 0)
			{
				done = 1;
			}
		}

		if(!lpty_hasproc(L, "p") && !lpty_readok(L, "p"))
			break;
	}

	lua_close(L);
	
	return 0;
}