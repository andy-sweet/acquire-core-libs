#ifndef H_ACQUIRE_KIT_FILTER_V0
#define H_ACQUIRE_KIT_FILTER_V0

#include "device/props/device.h"
#include "device/props/filter.h"

#ifdef __cplusplus
extern "C"
{
#endif
    struct VideoFrame;

    struct Filter
    {
        struct Device device;
        enum DeviceState state;

        enum DeviceState (*set)(struct Filter*,
                                const struct FilterProperties* settings);

        enum DeviceState (*get)(const struct Filter*,
                                struct FilterProperties* settings);

        enum DeviceState (*accumulate)(const struct Filter*,
                                        struct VideoFrame* accumulator,
                                        const struct VideoFrame* in);
    
        // TODO: unsure how this will get called by looking at storage.
        //void (*destroy)(struct Filter* self);
    };

#ifdef __cplusplus
}
#endif

#endif // H_ACQUIRE_KIT_FILTER_V0
