#include "xdp_quadrum_kern.h"

SEC("xdp")
int xdp_quadrum_prog(struct xdp_md *ctx) {

    // pointer of the start of the packet data
    void *data = (void *)(long)ctx->data;

    // pointer of the end of the packet data
    void *data_end = (void *)(long)ctx->data_end;

    // ethernet header size: 14 bytes
    // ip header size: 20 bytes
    // tcp/udp header size: 20 bytes

    struct ethhdr *eth = data;
    if ((void *)(eth + 1) > data_end) return XDP_ABORTED;

    struct iphdr *iph = (void *)(eth + 1);
    if ((void *)(iph + 1) > data_end) return XDP_ABORTED;

    int pkg_size = data_end - data;
    bpf_printk("[quadrum] packet size: %d bytes\n", pkg_size);
    
    return XDP_PASS;
}
