#ifndef H_ACQUIRE_HAL_FILTER_V0
#define H_ACQUIRE_HAL_FILTER_V0

#include "device/kit/filter.h"
#include "device.manager.h"

#ifdef __cplusplus
extern "C"
{
#endif

    struct Filter* filter_open(const struct DeviceManager* system,
                               const struct DeviceIdentifier* identifier);

    void filter_close(struct Filter* filter);

    enum DeviceStatusCode filter_set(struct Filter* filter,
                                     struct FilterProperties* settings);

    enum DeviceStatusCode filter_get(const struct Filter* filter,
                                     struct FilterProperties* settings);

    enum DeviceState filter_get_state(const struct Filter* filter);

#ifdef __cplusplus
}
#endif

#endif // H_ACQUIRE_HAL_FILTER_V0
