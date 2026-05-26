import subprocess
from originalfiles import TOOLNAME


def calc_file_md5(fname):
    toolname = "md5sum"
    execresult = subprocess.run( [ toolname, fname ], capture_output=True, text=True )
    if execresult.returncode:
        print( "cant execute tool " + toolname)
        return False
    return execresult.stdout.split()[0].strip()


def check_file_md5(fname, srcmd5):
    realmd5 = calc_file_md5(fname)
    r = (srcmd5 == realmd5)
    print(f"Проверка файла {fname}, результат: {r}")
    return r


def transform_file(srcfile, filter, dstfile):
    execresult = subprocess.run( [
        TOOLNAME, srcfile, "0", filter, dstfile ], capture_output=True, text=True )
    r = not execresult.returncode
    print(f"трансформация файла {srcfile} ftl={filter} dst={dstfile}, rcode: {execresult.returncode} результат: {r}")
    if execresult.returncode:
        print("STDOUT:", execresult.stdout)
        print("STDERR:", execresult.stderr)
    return r
