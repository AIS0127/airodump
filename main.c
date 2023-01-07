#include "airodump.h"

int main(int argc, char* argv[]){
    uint8_t *interface_;
    uint8_t errbuf[PCAP_ERRBUF_SIZE];
	

    if(argc != 2 ){
        printf("usage : airodump <interface>\n");
        exit(-1);
    }
    interface_ = argv[1];
    pcap_t* pcap = pcap_open_live(interface_, BUFSIZ, 1, 1000, errbuf);

    if (pcap == NULL) {
		fprintf(stderr, "pcap_open_live(%s) return null - %s\n", interface_, errbuf);
		return -1;
	}
    while(true){
    struct pcap_pkthdr* header;
		const uint8_t* packet;
		int res = pcap_next_ex(pcap, &header, &packet);
		if (res == PCAP_ERROR || res == PCAP_ERROR_BREAK) {
			printf("pcap_next_ex return %d(%s)\n", res, pcap_geterr(pcap));
		}
    printf("hello\n");
		airodump(packet);
        
    }
    pcap_close(pcap);
}