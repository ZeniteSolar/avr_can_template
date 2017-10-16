#ifndef _CAN_FILTERS_H_
#define _CAN_FILTERS_H_

// -----------------------------------------------------------------------------
/** Set filters and masks.
 *
 * The filters are divided in two groups:
 *
 * Group 0: Filter 0 and 1 with corresponding mask 0.
 * Group 1: Filter 2, 3, 4 and 5 with corresponding mask 1.
 *
 * If a group mask is set to 0, the group will receive all messages.
 *
 * If you want to receive ONLY 11 bit identifiers, set your filters
 * and masks as follows:
 *
 *  uint8_t can_filter[] PROGMEM = {
 *      // Group 0
 *      MCP2515_FILTER(0),              // Filter 0
 *      MCP2515_FILTER(0),              // Filter 1
 *
 *      // Group 1
 *      MCP2515_FILTER(0),              // Filter 2
 *      MCP2515_FILTER(0),              // Filter 3
 *      MCP2515_FILTER(0),              // Filter 4
 *      MCP2515_FILTER(0),              // Filter 5
 *
 *      MCP2515_FILTER(0),              // Mask 0 (for group 0)
 *      MCP2515_FILTER(0),              // Mask 1 (for group 1)
 *  };
 *
 *
 * If you want to receive ONLY 29 bit identifiers, set your filters
 * and masks as follows:
 *
 * \code
 *  uint8_t can_filter[] PROGMEM = {
 *      // Group 0
 *      MCP2515_FILTER_EXTENDED(0),     // Filter 0
 *      MCP2515_FILTER_EXTENDED(0),     // Filter 1
 *
 *      // Group 1
 *      MCP2515_FILTER_EXTENDED(0),     // Filter 2
 *      MCP2515_FILTER_EXTENDED(0),     // Filter 3
 *      MCP2515_FILTER_EXTENDED(0),     // Filter 4
 *      MCP2515_FILTER_EXTENDED(0),     // Filter 5
 *
 *      MCP2515_FILTER_EXTENDED(0),     // Mask 0 (for group 0)
 *      MCP2515_FILTER_EXTENDED(0),     // Mask 1 (for group 1)
 *  };
 * \endcode
 *
 * If you want to receive both 11 and 29 bit identifiers, set your filters
 * and masks as follows:
 */
const uint8_t can_filter[] PROGMEM =
{
    // Group 0
    MCP2515_FILTER(0),              // Filter 0
    MCP2515_FILTER(0),              // Filter 1

    // Group 1
    MCP2515_FILTER_EXTENDED(0),     // Filter 2
    MCP2515_FILTER_EXTENDED(0),     // Filter 3
    MCP2515_FILTER_EXTENDED(0),     // Filter 4
    MCP2515_FILTER_EXTENDED(0),     // Filter 5

    MCP2515_FILTER(0),              // Mask 0 (for group 0)
    MCP2515_FILTER_EXTENDED(0),     // Mask 1 (for group 1)
};
// You can receive 11 bit identifiers with either group 0 or 1.


#endif /* ifndef _CAN_FILTERS_H_ */
