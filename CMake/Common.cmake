
function(add_external path)

        SET(INC_PATH "${path}")
        include_directories(${INC_PATH})

endfunction()

function(add_include relpath)

        set(INC_PATH "${PROJECT_SOURCE_DIR}/${relpath}")
        include_directories(${INC_PATH})

endfunction()

