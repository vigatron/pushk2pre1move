import subprocess
from originalfiles import TOOLNAME


def calc_file_md5(fname):
    toolname = "md5sum"
    execresult = subprocess.run( [ toolname, fname ], capture_output=True, text=True )
    if execresult.returncode:
        return False
    return execresult.stdout.split()[0].strip()


def check_file_md5(fname, srcmd5):
    realmd5 = calc_file_md5(fname)
    r = (srcmd5 == realmd5)
    print(f"Проверка файла {fname}, результат: {r}")
    return r


def SelectFilterAO(fname):
    return "zx_filter_a.yaml" if fname.endswith(".scr") else "cl_filter_a.yaml"

def SelectFilterAR(fname):
    return "zx_filter_ar.yaml" if fname.endswith(".scr") else "cl_filter_ar.yaml"

def SelectFilterBO(fname):
    return "zx_filter_b.yaml" if fname.endswith(".scr") else "cl_filter_b.yaml"

def SelectFilterBR(fname):
    return "zx_filter_br.yaml" if fname.endswith(".scr") else "cl_filter_br.yaml"


def transform_file(srcfile, filter, dstfile):
    execresult = subprocess.run( [
        TOOLNAME, srcfile, "0", filter, dstfile ], capture_output=True, text=True )
    r = not execresult.returncode 
    print(f"трансформация файла {srcfile} ftl={filter} dst={dstfile}, результат: {r}")
    return r
