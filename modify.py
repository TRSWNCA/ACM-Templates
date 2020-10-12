#!/bin/python3
import os

with open("README.md", "r") as f:
    a = f.readlines();
    cnt = 0;
    for i in a:
        if (i.startswith("```")):
            cnt = cnt + 1

f.close()

with open("README.md", "w") as f:
    k = 0;
    for i in a:
        if (i.startswith("```")):
            k = k + 1;
        if (k != cnt - 1):
            f.write(i)
        if (k == cnt - 1):
            f.close()
            break

os.system("echo '```' >> README.md")
os.system("cd .. && tree ACM-Templates >> ACM-Templates/README.md")
os.system("echo '```' >> README.md")

