//
// Created by controller on 10/9/18.
//

#include "udp_com_test/ati_netft.h"
//
//AtiNetFT::AtiNetFT(){
//
//}

void AtiNetFT::pack(char *buffer, AtiNetFT::RDTCommand command) {
    // Data is big-endian
    buffer[0] = (command.command_header_ >> 8) & 0xFF;
    buffer[1] = (command.command_header_ >> 0) & 0xFF;
    buffer[2] = (command.command_ >> 8) & 0xFF;
    buffer[3] = (command.command_ >> 0) & 0xFF;
    buffer[4] = (command.sample_count_ >> 8) & 0xFF;
    buffer[5] = (command.sample_count_ >> 0) & 0xFF;
    buffer[6] = (command.sample_count_ >> 8) & 0xFF;
    buffer[7] = (command.sample_count_ >> 0) & 0xFF;
}


AtiNetFT::RDTRecord AtiNetFT::unpack(const uint8_t *buffer)
{
    RDTRecord record;
    record.rdt_sequence_ = unpack32(buffer + 0);
    record.ft_sequence_  = unpack32(buffer + 4);
    record.status_       = unpack32(buffer + 8);
    record.fx_ = unpack32(buffer + 12);
    record.fy_ = unpack32(buffer + 16);
    record.fz_ = unpack32(buffer + 20);
    record.tx_ = unpack32(buffer + 24);
    record.ty_ = unpack32(buffer + 28);
    record.tz_ = unpack32(buffer + 32);
}

AtiNetFT::RDTRecord AtiNetFT::unpack(const char *buffer){
    uint8_t buffer_t[RDT_COMMAND_SIZE+1];
    memcpy(buffer_t, buffer,RDT_COMMAND_SIZE+1);
    return unpack(buffer_t);
}

uint32_t AtiNetFT::unpack32(const uint8_t *buffer)
{
    return
            ( uint32_t(buffer[0]) << 24) |
            ( uint32_t(buffer[1]) << 16) |
            ( uint32_t(buffer[2]) << 8 ) |
            ( uint32_t(buffer[3]) << 0 ) ;
}