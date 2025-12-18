import time
mystring = input("enter matrix string: ")
temp = ''
for ch in mystring:
    if ch == ' ':
        time.sleep(0.002)
        temp+=' '
        print(temp)
        continue
    for i in "`1234567890-=qwertyuiop[]\asdfghjkl;'zxcvbnm,./!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>?`~`":
        if ch != i:
            time.sleep(0.002)
            print(temp+i)
        else:
            time.sleep(0.002)
            temp+=ch
            print(temp)
            break
while 1:
    for i in "`1234567890-=qwertyuiop[]\asdfghjkl;'zxcvbnm,./!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>?`~`":
        print(temp+i)