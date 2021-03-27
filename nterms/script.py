import os
name = input()
os.system("mkdir " + name)
os.system("touch " + name + "/" + name + ".hpp")
os.system("touch " + name + "/" + name + ".cpp")