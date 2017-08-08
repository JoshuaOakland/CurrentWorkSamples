"""
Pass in a string and the speaker will look up the matching audio file
if there is no audio file the speaker will generate a teaching request
"""
import sys
import pyglet
pyglet.options['audio'] = ('openal', 'directsound')
directory = "ttmAssets/"
player = pyglet.media.Player()
def target_file(target):
    return directory+target+".wav"
def say(target):
    try:
        sound = pyglet.media.load(target_file(target))
        sound.play()
    except:
        create_request(target)
    return
def say(target, player):
    try:
        sound = pyglet.media.load(target_file(target))
        player.queue(sound)
    except:
        create_request(target)
    return

def create_request(target):
    outfile = open(target_file("requests/"+target),'w')
    outfile.close()
    return
def main(arguments = 0):
    print("Testing speak_to_me_speaker main() ")
#    #target_word = sys.argv[1]
#    target_word = "hi"
#    target_words = ['hi','hello','good-bye','bye']
    target_words = ['la','la','i','am','a','file']
    for target_word in target_words:
#        say(target_word)
        say(target_word,player)
    player.play()
    return

if __name__ == "__main__":
    main()
