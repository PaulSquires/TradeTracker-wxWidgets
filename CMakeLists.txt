# Windows uses only one build tree:
# cmake -S. -Bbuild
# cmake --build build -j4 --config Release

# On Mac or Linux you'll need to maintain two build trees:
# cmake -S. -Bbuild -DCMAKE_BUILD_TYPE=Debug
# cmake --build build -j4
# cmake -S. -Bbuild-rel -DCMAKE_BUILD_TYPE=Release
# cmake --build build-rel -j4


cmake_minimum_required(VERSION 3.17 FATAL_ERROR)

project(TradeTracker-wxWidgets LANGUAGES CXX C)

include(FetchContent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(wxBUILD_SHARED OFF)

message(STATUS "Fetching wxWidgets...")

FetchContent_Declare(
   wxWidgets
   GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets.git
   GIT_SHALLOW ON
)
FetchContent_MakeAvailable(wxWidgets)


if(APPLE)
    AUX_SOURCE_DIRECTORY(src/tws-api/linux TWSAPISOURCES) 
else()
    AUX_SOURCE_DIRECTORY(src/tws-api/windows TWSAPISOURCES) 
endif()
AUX_SOURCE_DIRECTORY(src/tws-api/IntelDecimal INTELDECIMALSOURCES) 

set(SRCS
    src/TradeTracker.cpp;
    src/MainWindow/MainWindow.cpp;
    src/ActiveTrades/ActiveTrades.cpp;
    src/ClosedTrades/ClosedTrades.cpp;
    src/Transactions/Transactions.cpp;
    src/TradeHistory/TradeHistory.cpp;
    src/TabPanel/TabPanel.cpp;
    src/JournalNotes/JournalNotes.cpp;
    src/TickerTotals/TickerTotals.cpp;
    src/TradePlan/TradePlan.cpp;
    src/ImageButton/ImageButton.cpp;
    src/Database/database.cpp;
    src/Database/trade.cpp;
    src/Utilities/AfxHelper.cpp;
    src/Utilities/tws-client.cpp;
    # ${INTELDECIMALSOURCES};
    ${TWSAPISOURCES};
   # src/Config/Config.cpp
)

if(APPLE)
    # create bundle on apple compiles
    add_executable(TradeTracker MACOSX_BUNDLE ${SRCS})
    target_include_directories(TradeTracker PRIVATE src)

    # Set a custom plist file for the app bundle - needed for Mac OS Retina display
    set_target_properties(TradeTracker PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/src/Resources/Info.plist)
    
    target_link_libraries(TradeTracker PRIVATE wxcore wxnet)
else()
    # the WIN32 is needed for Windows in order for it to look for WinMain
    # instead of the main function. This is ignored on other systems,
    # so it works on all platforms
    # Default manifest can be suppressed with the following:

    # Windows compiler warnings
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_definitions(-D_WINSOCK_DEPRECATED_NO_WARNINGS)

    add_executable(
        TradeTracker WIN32
        ${SRCS} ${CMAKE_CURRENT_SOURCE_DIR}/src/Resources/TradeTracker.rc
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Resources/TradeTracker.exe.manifest
        )
    target_include_directories(TradeTracker PRIVATE src)

#    get_filename_component(LIB_A_PATH ./lib/windows/bin/TwsSocketClient.lib ABSOLUTE)
#    add_library(TwsSocketClient STATIC IMPORTED)
#    set_target_properties(TwsSocketClient PROPERTIES IMPORTED_LOCATION ${LIB_A_PATH})

    get_filename_component(LIB_B_PATH ./src/tws-api/IntelDecimal/lib/libbid.lib ABSOLUTE)
    add_library(libbid STATIC IMPORTED)
    set_target_properties(libbid PROPERTIES IMPORTED_LOCATION ${LIB_B_PATH})

    target_link_libraries(TradeTracker PRIVATE wxcore wxnet libbid)
endif()


