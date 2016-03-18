cmake_minimum_required (VERSION 2.6)
project (FakeASM)
file(GLOB FakeASM_SRC
    "*.h"
    "*.c"
)

add_executable(fakeASM ${FakeASM_SRC})
