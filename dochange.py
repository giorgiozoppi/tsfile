#!/usr/bin/env python3
"""
* Copyright (c) 2021 Giorgio Zoppi <giorgio.zoppi@iotdbe.com>
 * All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
"""

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
