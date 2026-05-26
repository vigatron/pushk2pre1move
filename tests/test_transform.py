import unittest
import os
import subprocess

from origpaths import BUILD_DIR
from origpaths import FILTERS_DIR
from origpaths import EXAMPLES_DIR
from origpaths import RESULTS_DIR

from originalfiles import ORIGFILES, TOOLNAME
from origfilters import SelectFilterParam, GetRFilter
from sysfuncs import transform_file, check_file_md5


def injectsym(fname, sym):
    base, ext   = os.path.splitext(fname)
    return base + sym + ext


class Transform(unittest.TestCase):


    def test_ver(self):
        execresult = subprocess.run( [ TOOLNAME, "--version" ], capture_output=True, text=True )
        if not execresult.returncode:
            print( "Version: " + execresult.stdout)
        self.assertEqual(execresult.returncode, 0)


    def proc_transform(self, mode : int):

        print(f"Transform() mode={mode}")

        for item in ORIGFILES:

            basefile   = item[0]
            basefilea  = injectsym(basefile,  "a")
            basefileb  = injectsym(basefile,  "b")
            basefilear = injectsym(basefilea, "r")
            basefilebr = injectsym(basefileb, "r")

            fltid_a  = item[2]
            fltid_b  = item[4]
            fltid_ar = GetRFilter(fltid_a)
            fltid_br = GetRFilter(fltid_b)

            flt_param_a    = SelectFilterParam(fltid_a, mode)
            flt_param_b    = SelectFilterParam(fltid_b, mode)
            flt_param_ar   = SelectFilterParam(fltid_ar, mode)
            flt_param_br   = SelectFilterParam(fltid_br, mode)

            srcfile     = os.path.join(EXAMPLES_DIR,    basefile)
            dstfilea    = os.path.join(RESULTS_DIR,     basefilea)
            dstfilear   = os.path.join(RESULTS_DIR,     basefilear)
            dstfileb    = os.path.join(RESULTS_DIR,     basefileb)
            dstfilebr   = os.path.join(RESULTS_DIR,     basefilebr)

            md5o  = item[1]
            md5a  = item[3]
            md5b  = item[5]

            print("Transform Tests:", basefile)

            # Check original MD5
            r = check_file_md5(srcfile, md5o)
            self.assertEqual(r, True, "Source MD5 mismatch")

            # Filter A direct transform & check MD5
            r = transform_file(srcfile, flt_param_a, dstfilea)
            self.assertEqual(r, True)
            r = check_file_md5(dstfilea, md5a)
            self.assertEqual(r, True, "Transform A failed")

            # Filter A restore
            r = transform_file(dstfilea, flt_param_ar, dstfilear)
            self.assertEqual(r, True)
            r = check_file_md5(dstfilear, md5o)
            self.assertEqual(r, True, "Restore A failed")

            # Filter B direct transform & check MD5
            r = transform_file(srcfile, flt_param_b, dstfileb)
            self.assertEqual(r, True)
            r = check_file_md5(dstfileb, md5b)
            self.assertEqual(r, True, "Transform B failed")

            # Filter B restore
            r = transform_file(dstfileb, flt_param_br, dstfilebr)
            self.assertEqual(r, True)
            r = check_file_md5(dstfilebr, md5o)
            self.assertEqual(r, True, "Restore B failed")


    def test_transform(self):
        self.proc_transform(0)  # yaml
        self.proc_transform(1)  # base64


if __name__ == "__main__":
    unittest.main()
