/* Copyright (c) 2021, SWITCH */
/* See LICENSE for licensing information. */

#ifndef _DNS_H
#define _DNS_H

#include <stdlib.h>
#include <arpa/nameser.h>

/* maximum character string length in a DNS response, including null-terminator */
#define MAXCHARSTRLEN 256

struct naptr_record {
    uint32_t ttl;
    uint16_t order;
    uint16_t preference;
    char flags[MAXCHARSTRLEN];
    char services[MAXCHARSTRLEN];
    char regexp[MAXCHARSTRLEN];
    char replacement[NS_MAXDNAME];
};

struct srv_record {
    uint32_t ttl;
    uint16_t priority;
    uint16_t weight;
    uint16_t port;
    char host[NS_MAXDNAME];
    /* TODO add A and AAAA records from additional section */
};

/**
 * query DNS NAPTR record for name
 * caller must free memory by calling free_naptr_response
 * 
 * @param name the name to query
 * @param timeout query timeout
 * @return null terminated array of struct naptr_record*
 */
struct naptr_record **query_naptr(const char *name, int timeout);

/**
 * free memory allocated by query_naptr
 * 
 * @param response the response to free
 */
void free_naptr_response(struct naptr_record **response);

/** 
 * query a DNS SRV record for name.
 * caller must free memory by calling free_srv_response.
 * 
 * @param name the name to query
 * @param timeout query timeout
 * @return null terminated array of struct srv_record*
 */
struct srv_record **query_srv(const char *name, int timeout);

/**
 * free memory allocated by query_srv
 * 
 * @param response the response to free
 */
void free_srv_response(struct srv_record **response);

#endif /*_DNS_H*/
