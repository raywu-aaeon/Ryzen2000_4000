set CXFREEZE_PATH=C:\Python27\Scripts
del *.dll /Q
del *.pyd /Q
del *.exe /Q
%CXFREEZE_PATH%\cxfreeze.bat BuildPspDirectory.py  --target-dir=.