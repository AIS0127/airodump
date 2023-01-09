#include "airodump.h"
#include "structs.h"

void airodump(const uint8_t * packet){
 radiotap_header *rdt_headr = (radiotap_header *)packet;
 BeaconFrame *BF = (BeaconFrame *)(packet + rdt_headr->it_len);
 
 if(BF->type != 0x80) return ; // packet filter
 //if((BF->type>>4) != 0x8) return ; // packet filter
 pdata *temp = find((*(unsigned long long int*)(BF->bssid)) & 0xffffffffffff);
 
 if(temp){
    temp->BEACONS += 1;
    temp->PWR = *(packet+rdt_headr->it_len-2) > 127 ? *(packet+rdt_headr->it_len-2) - 255 : *(packet+rdt_headr->it_len-2);
    add(temp,1);
 }else{
 temp = (pdata *)malloc(sizeof(pdata));
 sprintf(temp->BSSID,"%02X:%02X:%02X:%02X:%02X:%02X",BF->bssid[0],BF->bssid[1],BF->bssid[2],BF->bssid[3],BF->bssid[4],BF->bssid[5]);
 temp->id = (*(unsigned long long int*)(BF->bssid)) & 0xffffffffffff;
 temp->PWR = *(packet+rdt_headr->it_len-2) > 127 ? *(packet+rdt_headr->it_len-2) - 255 : *(packet+rdt_headr->it_len-2);
 temp->BEACONS = 1;
 temp->ESSID = (char *)malloc(BF->tag_data.len+1);
 memcpy(temp->ESSID,BF->tag_data.data,BF->tag_data.len);


 add(temp,0);
 }

 print();
}

pdata* find(long long int id){
    pdata * temp;
    if(!head){
        return 0;
    }else{
        temp = head;
        while(temp != 0){
        if(id == temp->id){
            return temp;
        }
        temp = temp->next;
        }
        return 0;
    }

}
void add(pdata *new_node,char flag){
    if(!head){
        head = new_node;
    }else if (flag && new_node->flag > 20){
        if (new_node == head) return;
        
        new_node->prev->next = new_node->next;
        if(new_node->next)
            new_node->next->prev = new_node->prev;

        new_node->next = head;
        new_node->prev = head->prev;
        head->prev = new_node;
        head = new_node;
        new_node->flag=0;
    }else if (flag == 0){
        pdata * temp = head;
        while(temp->next){
            temp = temp->next;
        }
        new_node->next = temp->next;
        temp->next = new_node;
        new_node->prev = temp;
    }
    new_node->flag ++;
}

void print(){
    pdata * temp;
    char cnt=0;
    
    system("clear");
    if(!head){
        return;
    }else{
        temp = head;
        printf("%-19s%-5s%-11s%s\n","BSSID","PWR","Beacons","ESSID");
        while(temp != 0 && cnt < 15){
          printf("%-19s%-5d%-11d%s\n",temp->BSSID,temp->PWR,temp->BEACONS,temp->ESSID);
          temp = temp->next;
          cnt ++;
        }
        return;
    }

}

void cleanup(pdata *new_node){
    pdata * temp;
    if(!head){
        return;
    }else{
        
        while(head != 0){
            temp = head;
            if(!temp->ESSID){
                free(temp->ESSID);
            }
        head = temp->next;
        free(temp);
        
        }
    }
}
