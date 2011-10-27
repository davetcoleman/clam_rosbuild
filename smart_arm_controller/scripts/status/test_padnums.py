#coding: UTF8
"""
Unit tests for padnums module.

Assumes use of nose
http://www.somethingaboutorange.com/mrl/projects/nose/
"""

from cStringIO import StringIO
from nose.tools import raises
from padnums import format_num as fn
from padnums import get_max_width as gmw
from padnums import pprint_table as ppt

@raises(AssertionError)
def test_module():
    """Make sure our module is getting called"""
    
    assert False

class TestFormatNum:
    
    def test_0(self):
        assert fn(0) == '0', fn(0)
        
    def test_1001(self):
        assert fn(1001) == '1,001', fn(1001)
        
    def test_spam(self):
        assert fn('spam') == 'spam', fn('spam')

class TestGetMaxWidth:
    
    def setup(self):
        
        self.data = [["", "taste", "land speed", "life"],
        ["spam", 300101, 4, 1003],
        ["eggs", 105, 13, 42],
        ["lumberjacks", 13, 105, 10]]

    def test_0(self):
        width = gmw(self.data, 0)
        assert width == len(fn("lumberjacks")), width
        
    def test_1(self):
        width = gmw(self.data, 1)
        assert width == len(fn(300101)), width

    def test_2(self):
        width = gmw(self.data, 2)
        assert width == len(fn("land speed")), width

    def test_3(self):
        width = gmw(self.data, 3)
        assert width == len(fn(1003)), width

    @raises(IndexError)
    def test_4(self):
        """Predictable errors"""
        width = gmw(self.data, 4)
        assert width == len(fn('viking')), width

class TestPprintTable:

    def test_spammy_table(self):
                
        table = [["", "taste", "land speed", "life"],
        ["spam", 300101, 4, 1003],
        ["eggs", 105, 13, 42],
        ["lumberjacks", 13, 105, 10]]

        out = StringIO()

        ppt(out, table)

        actual = out.getvalue().rstrip()
        expected = """                 taste   land speed    life
spam           300,101            4   1,003
eggs               105           13      42
lumberjacks         13          105      10"""
        
        assert actual == expected, "\n" + actual

    def test_more_rows(self):
                
                
        table = [["", "taste", "land speed"],
        ["spam", 300101, 4],
        ["eggs", 105, 13],
        ["lumberjacks", 13, 105]]

        out = StringIO()

        ppt(out, table)

        actual = out.getvalue().rstrip()
        expected = """                 taste   land speed
spam           300,101            4
eggs               105           13
lumberjacks         13          105"""
        
        assert actual == expected, "\n" + actual

    def test_more_cols(self):
                
        table = [["", "taste", "land speed", "life"],
        ["spam", 300101, 4, 1003],
        ["eggs", 105, 13, "n/a"]]

        out = StringIO()

        ppt(out, table)

        actual = out.getvalue().rstrip()
        expected = """          taste   land speed    life
spam    300,101            4   1,003
eggs        105           13     n/a"""
        
        assert actual == expected, "\n" + actual
