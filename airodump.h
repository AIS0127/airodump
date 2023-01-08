#ifndef AIRODUMP
#define AIRODUMP
#include <stdio.h>
#include <stdlib.h>
#include <pcap.h>
#include <pcap/pcap.h>
#include <stdbool.h>
#include <string.h>
#include "structs.h"

extern pdata *head;
void airodump(const uint8_t * packet);
void add(pdata *new_node,char flag);
void cleanup();
void print();
pdata* find(long long int id);
pdata * sfind(pdata* target);

#endif