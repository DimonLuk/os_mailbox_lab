#ifndef _LIBMAILBOX_H_
#define _LIBMAILBOX_H_
#include <stdint.h>
#include <stdlib.h>
#include "mailbox_config.h"


typedef uint8_t checksum_t;


typedef struct pages {
    uint32_t msg_id;
    size_t actual_size;
    pages *next_page = NULL;
    checksum_t check_sum;
    uint8_t is_free: 1;
    uint8_t body[MAILBOX_BODY_SIZE];
} page;

typedef page** pmsg_t; // paged messages

typedef struct mailbox_descriptions {
    uint32_t total_number_of_pages;
    uint32_t page_size;
    uint32_t occupied_pages;
    uint32_t last_id;
    checksum_t check_sum;
    pmsg_t pages;
} mailbox_description;

typedef struct messages {
    uint32_t id;
    uint8_t *message = NULL;
    size_t size;
} msg_t;


const uint8_t CRC_7_POL = 0b10010001;

mailbox_description* create_mailbox(char* path_to_mailbox, size_t mb_size);

mailbox_description* open_mailbox(char *path_to_mailbox);

msg_t* create_message(uint8_t *msg, size_t size);

uint8_t add_message(msg_t *message, mailbox_description *mb_description);

msg_t* read_message(uint32_t id, mailbox_description *mb_description);

msg_t** read_all_messages(mailbox_description* mb_description);

uint8_t remove_message(uint32_t id, mailbox_description *mb_description);

uint8_t remove_all_messages(mailbox_description *mb_description);

uint32_t get_amount_of_messages(mailbox_description *mb_description);

uint32_t get_amount_of_mailboxes(mailbox_description *mb_description);

#endif //_LIBMAILBOX_H_
