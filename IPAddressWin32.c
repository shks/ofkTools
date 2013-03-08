//
//  IPAddress.c
//  oscSenderExample
//
//  Created by Shunichi Kasahara on 12/02/21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

/*
 *  IPAddress.c
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <tchar.h>
#include <stdio.h>
#include <winsock.h>

#include "IPAddress.h"

#define	min(a,b)	((a) < (b) ? (a) : (b))
#define	max(a,b)	((a) > (b) ? (a) : (b))

#define BUFFERSIZE	4000

char *if_names[MAXADDRS];
char *ip_names[MAXADDRS];
char *hw_addrs[MAXADDRS];
unsigned long ip_addrs[MAXADDRS];

static int   nextAddr = 0;

void InitAddresses()
{
	int i;
	for (i=0; i<MAXADDRS; ++i)
	{
		if_names[i] = ip_names[i] = hw_addrs[i] = NULL;
		ip_addrs[i] = 0;
	}
}

void FreeAddresses()
{
	int i;
	for (i=0; i<MAXADDRS; ++i)
	{
		if (if_names[i] != 0) free(if_names[i]);
		if (ip_names[i] != 0) free(ip_names[i]);
		if (hw_addrs[i] != 0) free(hw_addrs[i]);
		ip_addrs[i] = 0;
	}
	InitAddresses();
}


void GetIPAddresses()
{
	/*
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(1, 1), &wsadata) != 0) {
//		return ;
	}

	char hostname[256];
	if (gethostname(hostname, sizeof(hostname)) != 0) {
		puts("error");
//		return ;
	}
	puts(hostname);

	HOSTENT* hostend = gethostbyname(hostname);
	if (hostend == NULL) {
//		puts("error");
		return ;
	}

	IN_ADDR inaddr;
	memcpy(&inaddr, hostend->h_addr_list[0], 4);
	char ip[256];
	strcpy(ip, inet_ntoa(inaddr));
	
	strcpy(ip_names[0], ip);
	
	WSACleanup();
	*/
//	ip_names[0] = "localhost"

	return ;
}

void GetHWAddresses()
{

}
