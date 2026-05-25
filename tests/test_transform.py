import unittest
import os
import subprocess

from originalfiles import ORIGFILES
from originalfiles import BUILD_DIR
from originalfiles import FILTERS_DIR
from originalfiles import EXAMPLES_DIR
from originalfiles import RESULTS_DIR

from sysfuncs import SelectFilterAO, SelectFilterAR, SelectFilterBO, SelectFilterBR
from sysfuncs import transform_file, check_file_md5


def injectsym(fname, sym):
    base, ext   = os.path.splitext(fname)
    return base + sym + ext


class Transform(unittest.TestCase):

    def test_transform(self):
        
        for item in ORIGFILES:

            basefile   = item[0]
            basefilea  = injectsym(basefile,  "a")
            basefileb  = injectsym(basefile,  "b")
            basefilear = injectsym(basefilea, "r")
            basefilebr = injectsym(basefileb, "r")

            fltfilea    = os.path.join(FILTERS_DIR, SelectFilterAO(basefile))
            fltfilear   = os.path.join(FILTERS_DIR, SelectFilterAR(basefile))
            fltfileb    = os.path.join(FILTERS_DIR, SelectFilterBO(basefile))
            fltfilebr   = os.path.join(FILTERS_DIR, SelectFilterBR(basefile))

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
            r = transform_file(srcfile, fltfilea, dstfilea)
            self.assertEqual(r, True)
            r = check_file_md5(dstfilea, md5a)
            self.assertEqual(r, True, "Transform A failed")

            # Filter A restore
            r = transform_file(dstfilea, fltfilear, dstfilear)
            self.assertEqual(r, True)
            r = check_file_md5(dstfilear, md5o)
            self.assertEqual(r, True, "Restore A failed")

            # Filter B direct transform & check MD5
            r = transform_file(srcfile, fltfileb, dstfileb)
            self.assertEqual(r, True)
            r = check_file_md5(dstfileb, md5b)
            self.assertEqual(r, True, "Transform B failed")

            # Filter B restore
            r = transform_file(dstfileb, fltfilebr, dstfilebr)
            self.assertEqual(r, True)
            r = check_file_md5(dstfilebr, md5o)
            self.assertEqual(r, True, "Restore B failed")


if __name__ == "__main__":
    unittest.main()
