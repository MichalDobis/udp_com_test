//
// Created by controller on 10/9/18.
//

#ifndef PROJECT_ATI_NETFT_H
#define PROJECT_ATI_NETFT_H

#endif //PROJECT_ATI_NETFT_H

#include <stdint.h>
#include <ros/ros.h>

class AtiNetFT{
public:
    struct RDTCommand {
        uint16_t command_header_;
        uint16_t command_;
        uint32_t sample_count_;
    };

    struct RDTRecord {
        uint32_t rdt_sequence_;
        uint32_t ft_sequence_;
        uint32_t status_;
        int32_t fx_;
        int32_t fy_;
        int32_t fz_;
        int32_t tx_;
        int32_t ty_;
        int32_t tz_;
    };

    const static int RDT_COMMAND_SIZE = 8;
    const static int RDT_RECORD_SIZE = 36;

    void static pack(char *buffer, RDTCommand command);
    RDTRecord static unpack(const uint8_t *buffer);
    RDTRecord static unpack(const char *buffer);
    uint32_t static unpack32(const uint8_t *buffer);

private:

};