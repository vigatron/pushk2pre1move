import os
from origpaths import FILTERS_DIR

FLT_ZX_A = 1
FLT_ZX_B = 2
FLT_CL_A = 3
FLT_CL_B = 4

FLT_ZX_AR = 5
FLT_ZX_BR = 6
FLT_CL_AR = 7
FLT_CL_BR = 8


FLTFILES  = [

    ["zx_filter_a.yaml"  , "Y291bnRlcjoKICBpbml0OiAwCiAgc3RlcDogMQogIHZvbHVtZTogMTkyCiAgdW5pdHN6OiAzMgoKdHJhbnNmb3JtOgogIHNyYzoKICAgIC0gZm9ybWF0OiAyCiAgICAgIHNjYWxlcjogMjA0OAogICAgLSBmb3JtYXQ6IDMKICAgICAgc2NhbGVyOiAzMgogICAgLSBmb3JtYXQ6IDMKICAgICAgc2NhbGVyOiAyNTYKICBkc3Q6CiAgICAtIGZvcm1hdDogOAogICAgICBzY2FsZXI6IDMy" ],
    ["zx_filter_b.yaml"  , "Y291bnRlcjoKICBpbml0OiAwCiAgc3RlcDogMQogIHZvbHVtZTogNjE0NAogIHVuaXRzejogMQoKdHJhbnNmb3JtOgogIHNyYzoKICAgIC0gZm9ybWF0OiAyCiAgICAgIHNjYWxlcjogMjA0OAogICAgLSBmb3JtYXQ6IDMKICAgICAgc2NhbGVyOiAzMgogICAgLSBmb3JtYXQ6IDUKICAgICAgc2NhbGVyOiAxCiAgICAtIGZvcm1hdDogMwogICAgICBzY2FsZXI6IDI1NgogIGRzdDoKICAgIC0gZm9ybWF0OiAxNAogICAgICBzY2FsZXI6IDE=" ],
    ["cl_filter_a.yaml"  , "Y291bnRlcjoKICBpbml0OiAwCiAgc3RlcDogMQogIHZvbHVtZTogMTYKICB1bml0c3o6IDEwMjQKCnRyYW5zZm9ybToKICBzcmM6CiAgICAtIGZvcm1hdDogMQogICAgICBzY2FsZXI6IDEwMjQKICAgIC0gZm9ybWF0OiAzCiAgICAgIHNjYWxlcjogMjA0OAogIGRzdDoKICAgIC0gZm9ybWF0OiA0CiAgICAgIHNjYWxlcjogMTAyNA==" ],
    ["cl_filter_b.yaml"  , "Y291bnRlcjoKICBpbml0OiAwCiAgc3RlcDogMQogIHZvbHVtZTogMjA0OAogIHVuaXRzejogOAoKdHJhbnNmb3JtOgogIHNyYzoKICAgIC0gZm9ybWF0OiA4CiAgICAgIHNjYWxlcjogOAogICAgLSBmb3JtYXQ6IDMKICAgICAgc2NhbGVyOiAyMDQ4CiAgZHN0OgogICAgLSBmb3JtYXQ6IDExCiAgICAgIHNjYWxlcjogOA==" ],

    ["zx_filter_ar.yaml" , "Y291bnRlcjoKICBpbml0OiAwCiAgc3RlcDogMQogIHZvbHVtZTogMTkyCiAgdW5pdHN6OiAzMgoKdHJhbnNmb3JtOgogIHNyYzoKICAgIC0gZm9ybWF0OiA4CiAgICAgIHNjYWxlcjogMzIKICBkc3Q6CiAgICAtIGZvcm1hdDogMgogICAgICBzY2FsZXI6IDIwNDgKICAgIC0gZm9ybWF0OiAzCiAgICAgIHNjYWxlcjogMzIKICAgIC0gZm9ybWF0OiAzCiAgICAgIHNjYWxlcjogMjU2"],
    ["zx_filter_br.yaml" , "Y291bnRlcjoKICBpbml0OiAwCiAgc3RlcDogMQogIHZvbHVtZTogNjE0NAogIHVuaXRzejogMQoKdHJhbnNmb3JtOgogIHNyYzoKICAgIC0gZm9ybWF0OiAxNAogICAgICBzY2FsZXI6IDEKICBkc3Q6CiAgICAtIGZvcm1hdDogMgogICAgICBzY2FsZXI6IDIwNDgKICAgIC0gZm9ybWF0OiAzCiAgICAgIHNjYWxlcjogMzIKICAgIC0gZm9ybWF0OiA1CiAgICAgIHNjYWxlcjogMQogICAgLSBmb3JtYXQ6IDMKICAgICAgc2NhbGVyOiAyNTY="],
    ["cl_filter_ar.yaml" , "Y291bnRlcjoKICBpbml0OiAwCiAgc3RlcDogMQogIHZvbHVtZTogMTYKICB1bml0c3o6IDEwMjQKCnRyYW5zZm9ybToKICBzcmM6CiAgICAtIGZvcm1hdDogNAogICAgICBzY2FsZXI6IDEwMjQKICBkc3Q6CiAgICAtIGZvcm1hdDogMQogICAgICBzY2FsZXI6IDEwMjQKICAgIC0gZm9ybWF0OiAzCiAgICAgIHNjYWxlcjogMjA0OA=="],
    ["cl_filter_br.yaml" , "Y291bnRlcjoKICBpbml0OiAwCiAgc3RlcDogMQogIHZvbHVtZTogMjA0OAogIHVuaXRzejogOAoKdHJhbnNmb3JtOgogIHNyYzoKICAgIC0gZm9ybWF0OiAxMQogICAgICBzY2FsZXI6IDgKICBkc3Q6CiAgICAtIGZvcm1hdDogOAogICAgICBzY2FsZXI6IDgKICAgIC0gZm9ybWF0OiAzCiAgICAgIHNjYWxlcjogMjA0OA=="]
]

def GetRFilter(fltid):
    if fltid == FLT_ZX_A:
          return FLT_ZX_AR
    if fltid == FLT_ZX_B:
          return FLT_ZX_BR
    if fltid == FLT_CL_A:
          return FLT_CL_AR
    if fltid == FLT_CL_B:
          return FLT_CL_BR
    print("Invalid Filter")
    exit(1)


def GetFilterName(fltid):

    if fltid == FLT_ZX_A:
            return FLTFILES[0][0]
    elif fltid == FLT_ZX_B:
            return FLTFILES[1][0]
    elif fltid == FLT_CL_A:
            return FLTFILES[2][0]
    elif fltid == FLT_CL_B:
            return FLTFILES[3][0]
    elif fltid == FLT_ZX_AR:
            return FLTFILES[4][0]
    elif fltid == FLT_ZX_BR:
            return FLTFILES[5][0]
    elif fltid == FLT_CL_AR:
            return FLTFILES[6][0]
    elif fltid == FLT_CL_BR:
            return FLTFILES[7][0]

    print("Invalid Filter")
    exit(1)


def SelectBase64(fname):
    for item in FLTFILES:
        if fname == item[0]:
            return item[1]
    return ""

def SelectFilterParam(fltid, mode):
    fltname = GetFilterName(fltid)
    if mode == 1:
        return SelectBase64(fltname)
    r = os.path.join(FILTERS_DIR, fltname)
    return r
