__version__ = "0.1"
__author__ = "Ryan Ginstrom"

import locale
locale.setlocale(locale.LC_NUMERIC, "")
import padnums as pp


if __name__ == "__main__":
    table = [["", "taste", "land speed", "life"],
        ["spam", 300101, 4, 1003],
        ["spam", 105, 13, 42],
        ["lumberjacks", 13, 105, 10]]
    
    import sys
    out = sys.stdout
    pp.pprint_table(out, table)
