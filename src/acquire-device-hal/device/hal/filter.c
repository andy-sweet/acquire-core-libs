#include "filter.h"
#include "logger.h"
#include "driver.h"

#define countof(e) (sizeof(e) / sizeof(*(e)))
#define containerof(P, T, F) ((T*)(((char*)(P)) - offsetof(T, F)))

#define LOG(...) aq_logger(0, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
#define LOGE(...) aq_logger(1, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
#define CHECK(e)                                                               \
    do {                                                                       \
        if (!(e)) {                                                            \
            LOGE("Expression evaluated as false:\n\t%s", #e);                  \
            goto Error;                                                        \
        }                                                                      \
    } while (0)
#define CHECK_NOJUMP(e)                                                        \
    do {                                                                       \
        if (!(e)) {                                                            \
            LOGE("Expression evaluated as false:\n\t%s", #e);                  \
        }                                                                      \
    } while (0)

struct Filter*
filter_open(const struct DeviceManager* system,
            const struct DeviceIdentifier* identifier)
{
    struct Filter* self = 0;

    CHECK(identifier);
    CHECK(identifier->kind == DeviceKind_Filter);

    {
        struct Device* device = 0;
        CHECK(Device_Ok ==
              driver_open_device(device_manager_get_driver(system, identifier),
                                 identifier->device_id,
                                 &device));

        self = containerof(device, struct Filter, device);
    }

    // Check the required interface functions are non-null
    CHECK(self->set != NULL);
    CHECK(self->get != NULL);

    return self;
Error:
    return 0;
}

void
filter_close(struct Filter* self)
{
    CHECK(self);
    struct Driver* const d = self->device.driver;
    CHECK_NOJUMP(Device_Ok == d->close(d, &self->device));
Error:;
}

// Validates and sets any properties.
// The set function returns the new state that the self is in.
// This may depend on how validation went.
enum DeviceStatusCode
filter_set(struct Filter* self, struct FilterProperties* settings)
{
    enum DeviceStatusCode ecode;
    // Neither can be NULL
    CHECK(self);
    CHECK(settings);
    switch (ecode = self->set(self, settings)) {
        case Device_Ok:
            if (self->state != DeviceState_Running)
                self->state = DeviceState_Armed;
            break;
        case Device_Err:
            self->state = DeviceState_AwaitingConfiguration;
            break;
    }
    return ecode;
Error:
    return Device_Err;
}

enum DeviceStatusCode
filter_get(const struct Filter* self, struct FilterProperties* settings)
{
    // Neither can be NULL
    CHECK(self);
    CHECK(settings);
    return self->get(self, settings);
Error:
    return Device_Err;
}

enum DeviceState
filter_get_state(const struct Filter* const filter)
{
    CHECK(filter);
    return filter->state;
Error:
    return DeviceState_Closed;
}
