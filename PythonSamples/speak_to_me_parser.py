"""
parsing module accepts a string of characters and filters out things
that are not in english words
"""

legal_characters = ['a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',' ']

def filter(inString):
    returnString = []
    for character in inString.lower():
        if character in legal_characters:
            returnString.append(character)
    return "".join(returnString)
        
def main():
    crapLine = "1231231klajsxlkfjasfa askldzxcz .c.s a.sd as.d as. das.d"
    filtLine = filter(crapLine)
    print(filtLine)
    print("".join(filtLine))
if __name__ == "__main__":
    main()
