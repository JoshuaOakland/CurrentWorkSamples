"""
A python text to speech self educating program
if an unknown word is encountered, the program prompts user to say it.
Eventually the program will readily digest any known language and translate it
to the user's own speech.
"""
import sys
import speak_to_me_speaker
import speak_to_me_parser
def main(system_arguments):
    print("Main is executing")
    target_file = input("\n Please type the name of the file you want to read.\n")
    with open(target_file,'r') as infile:
        lines = infile.readlines()
        for line in lines:
            print(line)
            for word in speak_to_me_parser.filter(line).split():
                speak_to_me_speaker.say(word,speak_to_me_speaker.player)
                print(word)
            speak_to_me_speaker.player.play()
#            for word in line:
#                speak_to_me_speaker.say(word,speak_to_me_speaker.player)
#        for line in infile.read():
#            print(line)
        infile.close()
    print(system_arguments[0])
    return
if __name__=="__main__":
    main(sys.argv)
