#include"average.h"
// #include <linux/compat.h>
// #include <linux/module.h>
// #include <linux/bug.h>

/**
 * ewma_init() - Initialize EWMA parameters
 * @avg: Average structure
 * @factor: Factor to use for the scaled up internal value. The maximum value
 *      of averages can be ULONG_MAX/(factor*weight).
 * @weight: Exponential weight, or decay rate. This defines how fast the
 *      influence of older values decreases. Has to be bigger than 1.
 *
 * Initialize the EWMA parameters for a given struct ewma @avg.
 */
void ewma_init(struct ewma *avg, unsigned long factor, unsigned long weight)
{
//         WARN_ON(!is_power_of_2(weight) || !is_power_of_2(factor));
 
//         avg->weight = ilog2(weight);
//         avg->factor = ilog2(factor);
        
        avg->weight = weight;
        avg->factor = factor;
        avg->internal = 0;
}
// EXPORT_SYMBOL(ewma_init);

/**
 * ewma_add() - Exponentially weighted moving average (EWMA)
 * @avg: Average structure
 * @val: Current value
 *
 * Add a sample to the average.
 */
struct ewma *ewma_add(struct ewma *avg, unsigned long val)
{
    avg->internal = avg->internal  ?
        (((avg->internal << avg->weight) - avg->internal) +
            (val << avg->factor)) >> avg->weight :
                (val << avg->factor);
    return avg;
 }
// EXPORT_SYMBOL(ewma_add);