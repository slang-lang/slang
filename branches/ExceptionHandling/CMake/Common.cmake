
function(add_include relpath)

        SET(INC_PATH "${PROJECT_SOURCE_DIR}/${relpath}")
        include_directories(${INC_PATH})

endfunction()

