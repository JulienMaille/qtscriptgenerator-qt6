cmake_minimum_required(VERSION 3.22)

project(qtscriptgenerator_qt6_bindings LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC OFF)
set(CMAKE_AUTORCC OFF)

find_package(Qt6 6.9.2 REQUIRED COMPONENTS
    Core
    Concurrent
    Gui
    Network
    Sql
    Widgets
    PrintSupport
    UiTools
    Svg
    SvgWidgets
    Script
    ScriptTools
)

set(QT_BINDINGS_OUTPUT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}" CACHE PATH
    "Root directory for plugins/script and the qs_eval outputs")
set(QT_BINDINGS_PLUGIN_OUTPUT_DIR "${QT_BINDINGS_OUTPUT_ROOT}/plugins/script")
set(QT_BINDINGS_EVALUATOR_OUTPUT_DIR "${QT_BINDINGS_OUTPUT_ROOT}/qtbindings/qs_eval")
set(QT_BINDINGS_SHARED_HEADER
    "${CMAKE_CURRENT_SOURCE_DIR}/qtbindings/include/__package_shared.h")

function(qt_bindings_sources_from_pri generated_module output_var)
    set(generated_dir "${CMAKE_CURRENT_SOURCE_DIR}/generated_cpp/${generated_module}")
    set(pri_file "${generated_dir}/${generated_module}.pri")
    if(NOT EXISTS "${pri_file}")
        message(FATAL_ERROR "Generated binding project file does not exist: ${pri_file}")
    endif()

    file(STRINGS "${pri_file}" pri_lines)
    set(generated_sources)
    foreach(pri_line IN LISTS pri_lines)
        string(REGEX REPLACE "# *\\$\\$PWD/" "" active_line "${pri_line}")
        string(REGEX MATCHALL "\\$\\$PWD/[^ ]+\\.(cpp|h)" pri_entries "${active_line}")
        foreach(pri_entry IN LISTS pri_entries)
            string(REGEX REPLACE "^\\$\\$PWD/" "" relative_file "${pri_entry}")
            set(source_file "${generated_dir}/${relative_file}")
            if(NOT EXISTS "${source_file}")
                message(FATAL_ERROR "Generated source listed by ${pri_file} does not exist: ${source_file}")
            endif()
            list(APPEND generated_sources "${source_file}")
        endforeach()
    endforeach()
    set(${output_var} "${generated_sources}" PARENT_SCOPE)
endfunction()

function(qt6_set_output_directories target output_dir)
    set_target_properties(${target} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${output_dir}"
        LIBRARY_OUTPUT_DIRECTORY "${output_dir}"
        ARCHIVE_OUTPUT_DIRECTORY "${output_dir}"
    )

    foreach(configuration IN ITEMS Debug Release RelWithDebInfo MinSizeRel)
        string(TOUPPER "${configuration}" configuration_upper)
        set_target_properties(${target} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY_${configuration_upper} "${output_dir}"
            LIBRARY_OUTPUT_DIRECTORY_${configuration_upper} "${output_dir}"
            ARCHIVE_OUTPUT_DIRECTORY_${configuration_upper} "${output_dir}"
        )
    endforeach()
endfunction()

function(qt6_add_binding target generated_module)
    set(qt_modules ${ARGN})
    set(module_dir "${CMAKE_CURRENT_SOURCE_DIR}/qtbindings/${target}")

    qt_bindings_sources_from_pri("${generated_module}" generated_sources)
    file(GLOB module_headers CONFIGURE_DEPENDS
        "${module_dir}/*.h"
        "${module_dir}/include/*"
    )

    add_library(${target} SHARED
        "${module_dir}/plugin.cpp"
        ${module_headers}
        "${QT_BINDINGS_SHARED_HEADER}"
        ${generated_sources}
    )

    set(binding_include_dirs
        "${CMAKE_CURRENT_SOURCE_DIR}/qtbindings/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/generated_cpp/${generated_module}"
    )
    if(EXISTS "${module_dir}/include")
        list(APPEND binding_include_dirs "${module_dir}/include")
    endif()
    target_include_directories(${target} PRIVATE ${binding_include_dirs})
    target_link_libraries(${target} PRIVATE Qt6::Script ${qt_modules})
    qt6_set_output_directories(${target} "${QT_BINDINGS_PLUGIN_OUTPUT_DIR}")
    set_target_properties(${target} PROPERTIES
        PREFIX ""
        DEBUG_POSTFIX "d"
    )

    if(target STREQUAL "qtscript_network")
        target_compile_definitions(${target} PRIVATE QTSCRIPT_NETWORK_PACKAGE)
    endif()
endfunction()

qt6_add_binding(qtscript_core com_trolltech_qt_core
    Qt6::Core Qt6::Concurrent Qt6::Widgets)
qt6_add_binding(qtscript_gui com_trolltech_qt_gui
    Qt6::Gui Qt6::Widgets)
qt6_add_binding(qtscript_network com_trolltech_qt_network
    Qt6::Network)
qt6_add_binding(qtscript_sql com_trolltech_qt_sql
    Qt6::Sql)
qt6_add_binding(qtscript_widgets com_trolltech_qt_widgets
    Qt6::Gui Qt6::Widgets)
qt6_add_binding(qtscript_printsupport com_trolltech_qt_printsupport
    Qt6::Core Qt6::Gui Qt6::Widgets Qt6::PrintSupport)
qt6_add_binding(qtscript_uitools com_trolltech_qt_uitools
    Qt6::UiTools Qt6::Widgets)
qt6_add_binding(qtscript_svg com_trolltech_qt_svg
    Qt6::Gui Qt6::Widgets Qt6::Svg Qt6::SvgWidgets)

add_dependencies(qtscript_gui qtscript_core)
add_dependencies(qtscript_network qtscript_core)
add_dependencies(qtscript_sql qtscript_core)
add_dependencies(qtscript_widgets qtscript_core)
add_dependencies(qtscript_printsupport qtscript_core qtscript_gui qtscript_widgets)
add_dependencies(qtscript_uitools qtscript_core qtscript_widgets)
add_dependencies(qtscript_svg qtscript_core qtscript_gui qtscript_widgets)

add_executable(qs_eval "${CMAKE_CURRENT_SOURCE_DIR}/qtbindings/qs_eval/main.cpp")
target_link_libraries(qs_eval PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Network
    Qt6::Script
    Qt6::ScriptTools
    Qt6::Sql
    Qt6::UiTools
    Qt6::Widgets
)
qt6_set_output_directories(qs_eval "${QT_BINDINGS_EVALUATOR_OUTPUT_DIR}")
set_target_properties(qs_eval PROPERTIES
    DEBUG_POSTFIX ""
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${QT_BINDINGS_EVALUATOR_OUTPUT_DIR}/debug"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${QT_BINDINGS_EVALUATOR_OUTPUT_DIR}/release"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${QT_BINDINGS_EVALUATOR_OUTPUT_DIR}/relwithdebinfo"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${QT_BINDINGS_EVALUATOR_OUTPUT_DIR}/minsizerel"
)
add_dependencies(qs_eval
    qtscript_core
    qtscript_gui
    qtscript_network
    qtscript_sql
    qtscript_widgets
    qtscript_printsupport
    qtscript_uitools
    qtscript_svg
)
