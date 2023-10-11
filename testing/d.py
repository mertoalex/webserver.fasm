#!/usr/bin/env python

port = 8000

def main():
 hexval = str(hex(port))
 hexval_arg1 = hexval[2:4]
 hexval_arg2 = hexval[4:6]
 hexval = f"0x{hexval_arg2}{hexval_arg1}"
 print(int(hexval, 0), end='')

if __name__=='__main__':
    main()
