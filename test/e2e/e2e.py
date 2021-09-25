#!/usr/bin/env python3
import os
import os.path
from autolib.gradle import Gradle
def test_file_executor():
    print("Execute Java Files Creation")
    current = os.getcwd()
    source = os.path.join(current, "java/src")
    os.chdir(current)
    g = Gradle()
    g.build_all()
    g.run_all()
    
