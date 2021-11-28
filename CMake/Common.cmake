
function(add_include relpath)

        set(INC_PATH "${PROJECT_SOURCE_DIR}/${relpath}")
        include_directories(${INC_PATH})

endfunction()

