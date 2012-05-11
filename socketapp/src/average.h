#ifndef AVERAGE_H
#define AVERAGE_H

#include<stdio.h>

struct ewma {
        unsigned long internal;
        unsigned long factor;
        unsigned long weight;
};

extern void ewma_init(struct ewma *avg, unsigned long factor,
                      unsigned long weight);

extern struct ewma *ewma_add(struct ewma *avg, unsigned long val);

/**
 * ewma_read() - Get average value
 * @avg: Average structure
 *
 * Returns the average value held in @avg.
 */
static inline unsigned long ewma_read(const struct ewma *avg)
{
        return avg->internal >> avg->factor;
}
#endif