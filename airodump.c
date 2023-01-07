#include "airodump.h"
#include "structs.h"

void airodump(const uint8_t * packet){
 radiotap_header *rdt_headr = (radiotap_header *)packet;
 BeaconFrame *BF = (BeaconFrame *)(packet + rdt_headr->it_len);
 printf("1\n");   
 if(BF->type != 0x80) return ; // packet filter
 //pdata *temp = (pdata *)malloc(sizeof(pdata));
 //sprintf(temp->BSSID,"%x:%x:%x:%x:%x:%x  ",BF->dest_mac[0],BF->dest_mac[1],BF->dest_mac[2],BF->dest_mac[3],BF->dest_mac[4],BF->dest_mac[5]);
 //printf("%19s\n", temp->BSSID);
 //free(temp);
 
}