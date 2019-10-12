include(ExternalProject)
ExternalProject_Add(ansi-escape
    GIT_REPOSITORY  https://github.com/HsuanTingLu/ansi-escape.git
    GIT_TAG         v1.1.1-rc1
    GIT_PROGRESS ON
    INSTALL_COMMAND ""  # No install steps planned    
)
