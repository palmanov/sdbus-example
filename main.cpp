#include <sdbus-c++/sdbus-c++.h>
#include <iostream>
#include <memory>

#include "udisks2-proxy.h"

class ManagerProxy final : public sdbus::ProxyInterfaces<org::freedesktop::UDisks2::Manager_proxy> {
 public:
  ManagerProxy(sdbus::IConnection &connection, const std::string &destination, std::string path)
      : ProxyInterfaces(connection, destination, std::move(path)),
        connection_(connection),
        destination_(destination) {
    registerProxy();
  }

  ~ManagerProxy() {
    unregisterProxy();
  }

  void GetBlockDev() {
    std::map<std::string, sdbus::Variant> options;
    auto block_devices = GetBlockDevices(options);
    for (const auto& dev : block_devices) {
      std::cout << "Dev " << dev << std::endl;
    }
  }

  void GetVer() {
    std::cout << "Version: " << Version() << std::endl;
  }

 private:
  sdbus::IConnection& connection_;
  std::string destination_;
};

int main(int argc, char *argv[]) {
  auto sys_connection = sdbus::createSystemBusConnection();

  auto udisks_manager_proxy = std::make_unique<ManagerProxy>(
      *sys_connection, "org.freedesktop.UDisks2", "/org/freedesktop/UDisks2/Manager");
  try {
    udisks_manager_proxy->GetVer();
    udisks_manager_proxy->GetBlockDev();
  } catch (const sdbus::Error &e) {
    std::cout << e.getMessage();
  }

  return 0;
}