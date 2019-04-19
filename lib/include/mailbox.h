#ifndef _LIBMAILBOX_H_
#define _LIBMAILBOX_H_
#include <stdint.h>
#include <stdlib.h>
#include "mailbox_config.h"


typedef uint8_t checksum_t;


typedef struct pages {
    uint32_t id;
    size_t actual_size;
    pages *next_page;
    checksum_t check_sum;
    uint8_t body[MAILBOX_BODY_SIZE];
} page;


typedef struct mailbox_descriptions {
    uint32_t total_number_of_pages;
    uint32_t page_size;
    uint32_t occupied_pages;
    checksum_t check_sum;
    page **pages;
} mailbox_description;


const uint8_t CRC_7_POL = 0b10010001;

mailbox_description* create_mailbox(char* path_to_mailbox, size_t mb_size);
mailbox_description* open_mailbox(char *path_to_mailbox);
page **create_message(void *message, size_t size);
uint8_t add_message(page **message, mailbox_description *mb_description);
uint8_t read_message(uint32_t id, mailbox_description *mb_description);
uint8_t remove_message(uint32_t id, mailbox_description *mb_description);
uint8_t remove_all(mailbox_description *mb_description);
uint32_t get_amount_of_messages(mailbox_description *mb_description);
uint32_t get_amount_of_mailboxes(mailbox_description *mb_description);
#endif
