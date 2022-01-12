import string
from os import system
from random import choices, randint, choice
from sys import float_info
from sys import argv
from time import sleep

CHARSET = string.ascii_letters + string.digits + string.punctuation


def fast():
    n = randint(72, 99)
    line = "".join(choices(population=CHARSET, k=n))
    print(line, end="", flush=True)


def slow():
    print(choice(CHARSET), end="", flush=True)


def main():
    system("cls")  # clear stdout first
    while True:
        try:
            if len(argv) == 1:
                fast()
            elif argv[1] in ["--slow", "-s"]:
                slow()
            elif argv[1] in ["--fast", "-f"]:
                fast()
            else:
                print("Invalid option specification.")
                raise Exception
            sleep(float_info.min)  # the slightest delay
        except:
            exit()


if __name__ == "__main__":
    main()
