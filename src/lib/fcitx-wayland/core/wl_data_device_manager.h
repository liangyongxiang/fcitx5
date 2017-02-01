#ifndef WL_DATA_DEVICE_MANAGER
#define WL_DATA_DEVICE_MANAGER
#include <wayland-client.h>
#include <memory>
#include "fcitx-utils/signals.h"
namespace fcitx {
namespace wayland {
class WlDataDevice;
class WlDataSource;
class WlSeat;
class WlDataDeviceManager {
public:
    static constexpr const char *interface = "wl_data_device_manager";
    static constexpr const wl_interface *const wlInterface = &wl_data_device_manager_interface;
    static constexpr const uint32_t version = 3;
    typedef wl_data_device_manager wlType;
    operator wl_data_device_manager *() { return data_.get(); }
    WlDataDeviceManager(wlType *data);
    WlDataDeviceManager(WlDataDeviceManager &&other) : data_(std::move(other.data_)) {}
    WlDataDeviceManager &operator=(WlDataDeviceManager &&other) {
        data_ = std::move(other.data_);
        return *this;
    }
    auto actualVersion() const { return version_; }
    WlDataSource *createDataSource();
    WlDataDevice *getDataDevice(WlSeat *seat);
private:
    static void destructor(wl_data_device_manager *);
    uint32_t version_;
    std::unique_ptr<wl_data_device_manager, decltype(&destructor)> data_;
};
}
}
#endif
