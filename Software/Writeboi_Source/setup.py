import sys
from cx_Freeze import setup, Executable


#Use this file if you have cx_freeze and would like to make an executable out of the writeboi GUI
#Usage: python setup.py build

build_exe_options = { }

# base="Win32GUI" should be used only for Windows GUI app
base = None
if sys.platform == "win32":
    base = "Win32GUI"

setup(
    name="WriteboiGUI",
    version="0.1",
    description="Writeboi GUI executable",
    options={"build_exe": build_exe_options},
    executables=[Executable("WriteboiGUI.pyw", base=base)],
)
