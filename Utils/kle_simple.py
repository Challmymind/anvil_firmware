import sys
import json

scancodes_dict = {

    # LETTERS
    "A" : "0x04", #/ Keyboard a and A
    "B" : "0x05", #/ Keyboard b and B
    "C" : "0x06", #/ Keyboard c and C
    "D" : "0x07", #/ Keyboard d and D
    "E" : "0x08", #/ Keyboard e and E
    "F" : "0x09", #/ Keyboard f and F
    "G" : "0x0a", #/ Keyboard g and G
    "H" : "0x0b", #/ Keyboard h and H
    "I" : "0x0c", #/ Keyboard i and I
    "J" : "0x0d", #/ Keyboard j and J
    "K" : "0x0e", #/ Keyboard k and K
    "L" : "0x0f", #/ Keyboard l and L
    "M" : "0x10", #/ Keyboard m and M
    "N" : "0x11", #/ Keyboard n and N
    "O" : "0x12", #/ Keyboard o and O
    "P" : "0x13", #/ Keyboard p and P
    "Q" : "0x14", #/ Keyboard q and Q
    "R" : "0x15", #/ Keyboard r and R
    "S" : "0x16", #/ Keyboard s and S
    "T" : "0x17", #/ Keyboard t and T
    "U" : "0x18", #/ Keyboard u and U
    "V" : "0x19", #/ Keyboard v and V
    "W" : "0x1a", #/ Keyboard w and W
    "X" : "0x1b", #/ Keyboard x and X
    "Y" : "0x1c", #/ Keyboard y and Y
    "Z" : "0x1d",  #/ Keyboard z and Z

    # NUMBERS (mostly)
    "1" : "0x1e", #/ Keyboard 1 and !
    "2" : "0x1f", #/ Keyboard 2 and @
    "3" : "0x20", #/ Keyboard 3 and #
    "4" : "0x21", #/ Keyboard 4 and $
    "5" : "0x22", #/ Keyboard 5 and %
    "6" : "0x23", #/ Keyboard 6 and ^
    "7" : "0x24", #/ Keyboard 7 and &
    "8" : "0x25", #/ Keyboard 8 and *
    "9" : "0x26", #/ Keyboard 9 and (
    "0" : "0x27",#/ Keyboard 0 and )

    # SPECIAL
    "ENTER" : "0x28",   #/ Keyboard Return (ENTER)
    "ESC" : "0x29",      #/ Keyboard ESCAPE
    "BACKSPACE" : "0x2a",    #/ Keyboard DELETE (Backspace)
    "TAB" : "0x2b",          #/ Keyboard Tab
    "SPACE" : "0x2c",        #/ Keyboard Spacebar
    "MINUS" : "0x2d",        #/ Keyboard - and _
    "EQUAL" : "0x2e",        #/ Keyboard = and +
    "LEFTBRACE" : "0x2f",    #/ Keyboard [ and {
    "RIGHTBRACE" : "0x30",   #/ Keyboard ] and }
    "BACKSLASH" : "0x31",    #/ Keyboard \ and |
    "HASHTILDE" : "0x32",    #/ Keyboard Non-US # and ~
    "SEMICOLON" : "0x33",    #/ Keyboard ; and :
    "APOSTROPHE" :"0x34",  #/ Keyboard ' and "
    "GRAVE" : "0x35",       #/ Keyboard ` and ~
    "COMMA" : "0x36",        #/ Keyboard , and <
    "DOT" : "0x37",          #/ Keyboard . and >
    "SLASH" : "0x38",        #/ Keyboard / and ?
    "CAPSLOCK" : "0x39"     #/ Keyboard Caps Lock

}

def translate(letter : str):
    letter = letter.upper()
    return scancodes_dict.get(letter, "0x00")

def main(filename):
    struct = str("{");
    with open(filename, "r") as f:
        content = f.read()

    if len(content) == 0:
        print("No such file or nothing in the file")
        exit(-1)

    content = json.loads(content)
    lines = len(content)

    for i, row in enumerate(content):
        size = len(row)
        struct += "\n\t{"
        for x, code in enumerate(row):
            if not isinstance(code, str):
                continue
            struct += translate(code)
            if x < (size - 1):
                 struct += ", "
        struct += "}"
        if i < (lines - 1):
            struct += ","


    struct += "\n}"

    print(struct)

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Not enough arguments")
        exit(-1)

    filename = sys.argv[1]
    main(filename)
