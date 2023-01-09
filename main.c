#include "airodump.h"


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
    uint8_t channel = 0;
    char *channel_cmd = "sudo iwconfig %s channel %u";
    char cmd[100] = {0,};

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
    sprintf(cmd,channel_cmd,interface_,channel);
    system(cmd);
    sleep(0.1);
    channel = (channel +1) % 14 + 1;
		airodump(packet,channel);
        
    }
    pcap_close(pcap);
}