#!/usr/bin/env python3
from datetime import datetime
from git import Repo
import os
now = datetime.now()
date = now.strftime("%b %d %Y %H:%M:%S")
r = Repo.init(os.getcwd())
reader = r.config_reader()
name = reader.get_value("user","name")
mail = reader.get_value("user","email")
header = date + "\t" + name + " " + "<"+mail+">"
print("Header {}".format(header))
exit_typing = False
with open("Changelog", 'a') as fp:
    print("List the changes (type end.) to quit:")
    fp.write(" "+header+"\n")
    while not exit_typing:
        line = input()
        line = line.strip()
        if line != "end.":
            fp.write("\t* "+line+"\n")
        else:
            exit_typing = True
