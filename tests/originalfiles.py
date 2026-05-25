import os

APPNAME         = "pushk2pre1move"

BASE_DIR        = os.path.dirname(os.path.abspath(__file__))
BUILD_DIR       = os.path.join(BASE_DIR, "..", "build")
FILTERS_DIR     = os.path.join(BASE_DIR, "..", "cfg")
EXAMPLES_DIR    = os.path.join(BASE_DIR, "..", "examples")
RESULTS_DIR     = os.path.join(BASE_DIR, "..", "results")

TOOLNAME        = os.path.join(BUILD_DIR, APPNAME)

FLTZAT = 1
FLTZBT = 2
FLTCAT = 3
FLTCBT = 4

FLTZAR = 5
FLTZBR = 6
FLTCAR = 7
FLTCBR = 8


FLTFILES  = [

    "zx_filter_a.yaml",
    "zx_filter_b.yaml",
    "cl_filter_a.yaml",
    "cl_filter_b.yaml",

    "zx_filter_ar.yaml",
    "zx_filter_br.yaml",
    "cl_filter_ar.yaml",
    "cl_filter_br.yaml",
]

ORIGFILES = [

    [ "example1.scr"  , "4a9db57bd34af7c7464918f555b84c1a" , FLTZAT, "91dbd25ef94a99052b6238ff692e49a9", FLTZBT, "d5b7e410e4169eebd16723d55efbbc8e"],
    [ "example2.scr"  , "7f0979997837b47b5c2dcb48cf9f8d0b" , FLTZAT, "b4a91d46a69fe152dfbaf5d8f704655f", FLTZBT, "e712752657dee50bf4cba76d1379b417"],
    [ "example3.scr"  , "36a03fc3dc2ed1c1109171db06fcfd23" , FLTZAT, "6d18ce3d0cea1e1efe5763387a73f260", FLTZBT, "13a1aa1e0604d56b4de61e7badab9324"],
    [ "example4.scr"  , "b47bc2e1835a88154ea2d189f4161bd6" , FLTZAT, "9eb6f49fc5b5515988012cc29e11c59a", FLTZBT, "2f33ce19760e1fa17451f4d310519b8c"],
    [ "example5.scr"  , "3d281b5830f931f5d4d199a048471fe5" , FLTZAT, "487b9b4dfb51b9275b1a81554d39e365", FLTZBT, "04f7ef22c84ef775fc5c0670f60ae9ef"],
    [ "example6.scr"  , "9dd68048dc15525af9acfa6883398ddb" , FLTZAT, "d8637533063b869310ae31e283e41c47", FLTZBT, "f32f0e23ab590213af2551d97ec32102"],

    [ "example7.bin"  , "66d2c7887b401109f466de65cf83c4f5" , FLTCAT, "6ccd2be5ebc8d1456d50991c7d8281f0", FLTZBT, "37fb285e628b0c085f5581bc3d340d24"],
    [ "example8.bin"  , "dca17a92e634a3c93a458f37ea6629bb" , FLTCAT, "68d0a773d2389a46942929eabde25a65", FLTZBT, "a0175923861f338a9f35b71c0be14dad"],
    [ "example9.bin"  , "af09d0550b794b051fb0ce2f316793cc" , FLTCAT, "f9e35d3f394714c08aec7c4b6df3f822", FLTZBT, "a330ae5d3aa4ebedd31a93f2747c5b7a"],
    [ "example10.bin" , "a7637f24d09cd964b39703bd2c9bc341" , FLTCAT, "21ce2b6f6125cbbb3d051df9c70008ce", FLTZBT, "a1143482d7b07abd139c14b593164601"]
]

