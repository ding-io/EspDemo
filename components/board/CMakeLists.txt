idf_component_register(SRCS "board.c"
                            "strip/board_strip.c"
                       INCLUDE_DIRS "."
                                    "strip"
                       REQUIRES led_strip)