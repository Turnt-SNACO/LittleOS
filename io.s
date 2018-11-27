global SendDataToPort
global GetDataFromPort
SendDataToPort:
    mov al, [esp + 8]
    mov dx, [esp + 4]
    out dx, al
    ret
GetDataFromPort:
    mov dx, [esp + 4]
    in al, dx
    ret