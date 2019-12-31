function(GetDependencies)
    function(MakeDependencyDir in_Dep out_Dir)
        set(${out_Dir} "libs/${in_Dep}" PARENT_SCOPE)
    endfunction()

    function(RunGit)
        if (WIN32)
            set(EXEC_PFX cmd /c)
        endif ()

        find_package(Git)

        execute_process(
                COMMAND ${EXEC_PFX} ${GIT_EXECUTABLE} ${ARGV}
                WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
        )
    endfunction()

    file(READ "${CMAKE_SOURCE_DIR}/libs/dependencies" DynamiteDependencies)

    foreach (dep IN LISTS DynamiteDependencies)
        MakeDependencyDir(${dep} "${dep}_dir")
        message("[InfoDynamite] Setting up dependency '${dep}' with directory [${${dep}_dir}]")
    endforeach ()

    RunGit(submodule update --init --recursive)
endfunction()
