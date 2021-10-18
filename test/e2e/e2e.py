#!/usr/bin/env python3
import os
import os.path
import argparse
from autolib.gradle import Gradle

parser = argparse.ArgumentParser()
parser.parse_args()
def test_file_executor():
    print("Execute Java Files Creation")
    current = os.getcwd()
    source = os.path.join(current, "java/src")
    os.chdir(current)
    g = Gradle()
    g.build_all()
    g.run_all()
    
