#include "airodump.h"
#include<signal.h>

pdata *head;
pcap_t* pcap;
void sig_handler(int signum){

  pcap_close(pcap);
  cleanup();
  exit(-1);
}
int main(int argc, char* argv[]){
  signal(SIGINT,sig_handler);
    uint8_t *interface_;
    uint8_t errbuf[PCAP_ERRBUF_SIZE];
	

    if(argc != 2 ){
        printf("usage : airodump <interface>\n");
        exit(-1);
    }
    interface_ = argv[1];
    pcap = pcap_open_live(interface_, BUFSIZ, 1, 1000, errbuf);

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
    
		airodump(packet);
        
    }
    pcap_close(pcap);
}