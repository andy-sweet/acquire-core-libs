#ifndef H_ACQUIRE_KIT_FILTER_V0
#define H_ACQUIRE_KIT_FILTER_V0

#include "device/props/device.h"
#include "device/props/filter.h"

#ifdef __cplusplus
extern "C"
{
#endif

    struct Filter
    {
        struct Device device;
        enum DeviceState state;

        enum DeviceStatusCode (*set)(struct Filter*,
                                     struct FilterProperties* settings);

        enum DeviceStatusCode (*get)(const struct Filter*,
                                     struct FilterProperties* settings);
    };

#ifdef __cplusplus
}
#endif

#endif // H_ACQUIRE_KIT_FILTER_V0
