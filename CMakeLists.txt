cmake_minimum_required(VERSION 3.17 FATAL_ERROR)

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
)

if(APPLE)
    # create bundle on apple compiles
    add_executable(TradeTracker MACOSX_BUNDLE ${SRCS})
    target_include_directories(TradeTracker PRIVATE src)

    # Set a custom plist file for the app bundle - needed for Mac OS Retina display
    set_target_properties(TradeTracker PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/src/Resources/Info.plist)
else()
    # the WIN32 is needed for Windows in order for it to look for WinMain
    # instead of the main function. This is ignored on other systems,
    # so it works on all platforms
    # Default manifest can be suppressed with the following:
    add_executable(
        TradeTracker WIN32
        ${SRCS} ${CMAKE_CURRENT_SOURCE_DIR}/src/Resources/TradeTracker.rc
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Resources/TradeTracker.exe.manifest
        )
    target_include_directories(TradeTracker PRIVATE src)
endif()

target_link_libraries(TradeTracker PRIVATE wxcore wxnet)

