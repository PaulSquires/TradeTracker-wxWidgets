cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(TradeTracker-wxWidgets LANGUAGES CXX)

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

set(SRCS
    src/TradeTracker.cpp;
    src/TradeTracker.h;
    src/MainWindow.cpp;
    src/MainWindow.h;
    src/ActiveTrades.cpp;
    src/ActiveTrades.h;
    src/ClosedTrades.cpp;
    src/ClosedTrades.h;
    src/Transactions.cpp;
    src/Transactions.h;
    src/TradeHistory.cpp;
    src/TradeHistory.h;
    src/TabPanel.cpp;
    src/TabPanel.h;
    src/JournalNotes.cpp;
    src/JournalNotes.h;
    src/TickerTotals.cpp;
    src/TickerTotals.h;
    src/TradePlan.cpp;
    src/TradePlan.h
        src/Colors.h
)

if(APPLE)
    # create bundle on apple compiles
    add_executable(TradeTracker MACOSX_BUNDLE ${SRCS})

    # Set a custom plist file for the app bundle - needed for Mac OS Retina display
    set_target_properties(TradeTracker PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/src/resource/Info.plist)
else()
    # the WIN32 is needed for Windows in order for it to look for WinMain
    # instead of the main function. This is ignored on other systems,
    # so it works on all platforms
    add_executable(
        TradeTracker WIN32
        ${SRCS} ${CMAKE_CURRENT_SOURCE_DIR}/src/resource/TradeTracker.rc
        ${CMAKE_CURRENT_SOURCE_DIR}/src/resource/TradeTracker.exe.manifest
        )
endif()

target_link_libraries(TradeTracker PRIVATE wxcore wxnet)
