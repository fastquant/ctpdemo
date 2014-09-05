find_path(CTP_INCLUDE_DIR ThostFtdcUserApiDataType.h $ENV{CTP_HOME}/include)
find_library(CTP_MD_LIBRARY thostmduserapi $ENV{CTP_HOME}/lib)
find_library(CTP_TRADER_LIBRARY thosttraderapi $ENV{CTP_HOME}/lib)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CTP DEFAULT_MSG CTP_MD_LIBRARY CTP_TRADER_LIBRARY CTP_INCLUDE_DIR)
