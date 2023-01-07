#ifndef AIRODUMP
#define AIRODUMP
#include<stdio.h>
#include<stdlib.h>
#include <pcap.h>
#include <pcap/pcap.h>
#include <stdbool.h>

#include "structs.h"

extern manage_st head;
void airodump(const uint8_t * packet);

#endif