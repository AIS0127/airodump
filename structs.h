#ifndef STRUCTS
#define STRUCTS

typedef struct pdata{
    long long int id;
    char BSSID[0x15];
    char PWR[0x8];
    char BEACONS[0xc];
    char *ESSID;

} __attribute__((__packed__)) pdata;

typedef struct manage_st{
    pdata * next;
    pdata * data;
} __attribute__((__packed__)) manage_st;



typedef struct tagged_parameter{
    uint8_t num;
    uint8_t len;
    u_char data[1];
} __attribute__((__packed__)) tagged_parameter;

typedef struct radiotap_header {
        u_int8_t        it_version;     /* set to 0 */
        u_int8_t        it_pad;
        u_int16_t       it_len;         /* entire length */
        u_int32_t       it_present;     /* fields present */
} __attribute__((__packed__)) radiotap_header;

typedef struct BeaconFrame{
    
    uint16_t type; 
    uint16_t duration;
    uint8_t dest_mac[6];
    uint8_t src_mac[6];
    uint8_t bssid[6];
    uint16_t seq_num; 
    
    
    uint64_t timestamp;
    uint16_t beacon_interval;
    uint16_t capabilities_info;

    tagged_parameter tag_data;
} __attribute__((__packed__)) BeaconFrame;

#endif