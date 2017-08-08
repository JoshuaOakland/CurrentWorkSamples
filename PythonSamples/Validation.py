valid_symbols = ['a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','1','2','3','4','5','6','7','8','9','0']
valid_symbols_bitform = [b'a',b'b',b'c',b'd',b'e',b'f',b'g',b'h',b'i',b'j',b'k',b'l',b'm',b'n',b'o',b'p',b'q',b'r',b's',b't',b'u',b'v',b'w',b'x',b'y',b'z',b'1',b'2',b'3',b'4',b'5',b'6',b'7',b'8',b'9',b'A',b'B',b'C',b'D',b'E',b'F',b'G',b'H',b'I',b'J',b'K',b'L',b'M',b'N',b'O',b'P',b'Q',b'R',b'S',b'T',b'U',b'V',b'W',b'X',b'Y',b'Z']
def validate_logon(login):#Check format, length, and content
	login = login[0].decode('utf-8')
	print("VALIDATING {0}".format(login))
	if(login.count(';') != 3):
		return(False)
	print("count passed")
	if (len(login) > 44 or len(login) < 24):#uname pass max = 15 each
		return(False)
	print("Len passed")
	for symbol in login:
		if (symbol is not ';'):
			if (symbol not in valid_symbols):
				print("SYMBOL INVALID")
				print(symbol)
				return(False)
	else:
		print("VALIDATION PASSED")
		return(True)
