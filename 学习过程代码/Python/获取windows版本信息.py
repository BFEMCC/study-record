import sys
from platform import platform
print(platform())

version_info = sys.getwindowsversion()
print("Major Version:", version_info.major)
print("Minor Version:", version_info.minor)
print("Build Number:", version_info.build)
print("Platform ID:", version_info.platform)
print("Service Pack:", version_info.service_pack)
