from argparse import ArgumentParser
from pathlib import Path
from difflib import unified_diff
from termcolor import colored
from enum import Enum

import subprocess as sp
import yaml

def run_shell(args, stdin):
    return sp.run(["timeout", "1"] + args, capture_output=True, text=True, input=stdin)

def diff(bash, sh):
    bash = bash.splitlines(keepends=True)
    sh = sh.splitlines(keepends=True)

    return ''.join(unified_diff(bash, sh, fromfile="bash", tofile="420sh"))

def test(binary, testcase, testMap):
    bash = run_shell(["bash", "--posix"], testcase["stdin"])
    sh = run_shell([binary], testcase["stdin"])

    for check in testcase.get("checks", ["stdout", "stderr", "returncode"]):
        if sh.returncode == 124:
            assert bash.returncode == 124, \
                colored(f" |--> Exited with 124 [TIMEOUT]", "magenta")
        if check == testMap[Test_Type.RETURNCODE] :
            assert bash.returncode == sh.returncode, \
                colored(f" |--> Exited with {sh.returncode} expected {bash.returncode}.", 'red')
        if check == testMap[Test_Type.STDOUT] :
            assert bash.stdout == sh.stdout, \
                colored(f" |--> stdout differs:\n", 'red')\
                +colored(f"{diff(bash.stdout, sh.stdout)}", 'yellow')
        if check == testMap[Test_Type.STDERR] :
            assert bash.stderr == sh.stderr, \
                colored(f" |--> stderr differs:\n", 'red')\
                +colored(f"{diff(bash.stderr, sh.stderr)}", 'yellow')
        if check == testMap[Test_Type.HAS_STDERR] :
            assert sh.stderr != "", \
                colored(f" |--> Expected something on stderr", 'red')

if __name__ == "__main__":
    parser = ArgumentParser(description = "420sh test suite")
    parser.add_argument('bin', metavar="BIN")
    args = parser.parse_args()

#### ASCII ART LOGO

    color1 = 'green'
    color2 = 'white'
    print("                     ")
    print(f"{colored(' ___ ___ ___     _   ', f'{color1}')}", end="")
    print(f"{colored('  _           _       ', f'{color2}')}",)
    print(f"{colored('| | |_  |   |___| |_ ', f'{color1}')}", end="")
    print(f"{colored(' | |_ ___ ___| |_ ___ ', f'{color2}')}",)
    print(f"{colored('|_  |  _| | |_ -|   |', f'{color1}')}", end="")
    print(f"{colored(' |  _| -_|_ -|  _|_ -|', f'{color2}')}",)
    print(f"{colored('  |_|___|___|___|_|_|', f'{color1}')}", end="")
    print(f"{colored(' |_| |___|___|_| |___|', f'{color2}')}",)
    print("                     ")
    print("                     ")


#### OPENING TEST FILES

    #test_dir = os.path.dirname(os.path.realpath(__file__))
    #if_test_file = os.path.join(test_dir, 'if_tests.yml')

    test_dir = Path(__file__).resolve().parents[0]

    sections = ["IF TESTS"]
    if_test_file = str(test_dir) + "/if_tests.yml"
    with open(if_test_file, "r") as tests_files :
        test_list = [yaml.safe_load(tests_files)]

    sections += ["LOOPS TESTS"]
    loops_test_file = str(test_dir) + "/loops_tests.yml"
    with open(loops_test_file, "r") as tests_files :
        test_list += [yaml.safe_load(tests_files)]

    sections += ["FUNCTIONS TESTS "]
    funcdec_test_file = str(test_dir) + "/funcdec_tests.yml"
    with open(funcdec_test_file, "r") as tests_files :
        test_list += [yaml.safe_load(tests_files)]

    sections += ["CASE TESTS"]
    case_test_file = str(test_dir) + "/case_tests.yml"
    with open(case_test_file, "r") as tests_files :
        test_list += [yaml.safe_load(tests_files)]

    sections += ["BUILT-IN TESTS"]
    command_test_file = str(test_dir) + "/builtins_tests.yml"
    with open(command_test_file, "r") as tests_files :
        test_list += [yaml.safe_load(tests_files)]

    sections += ["REDIRECTION TESTS"]
    redirections_test_file = str(test_dir) + "/redirections_tests.yml"
    with open(redirections_test_file, "r") as tests_files :
        test_list += [yaml.safe_load(tests_files)]

    sections += ["PIPE TESTS"]
    redirections_test_file = str(test_dir) + "/pipe_tests.yml"
    with open(redirections_test_file, "r") as tests_files :
        test_list += [yaml.safe_load(tests_files)]

    sections += ["EXPANSION TESTS"]
    expand_test_file = str(test_dir) + "/expand_tests.yml"
    with open(expand_test_file, "r") as tests_files :
        test_list += [yaml.safe_load(tests_files)]

    sections += ["OTHER TESTS"]
    tests_file = str(test_dir) + "/tests.yml"
    with open(tests_file, "r") as tests_files :
        test_list += [yaml.safe_load(tests_files)]

    class Test_Type(Enum):
        RETURNCODE = 0
        STDOUT = 1
        STDERR = 2
        HAS_STDERR = 3

    testMap = {Test_Type.RETURNCODE: "returncode",\
               Test_Type.STDOUT: "stdout", Test_Type.STDERR: "stderr",\
               Test_Type.HAS_STDERR: "has_stderr"}

    binary = Path(args.bin).absolute()
    j = 0
    i = 0
    success = 0
    failure = 0
    for tests in test_list:
        print(f"{colored('#', 'blue')} {sections[j]}\n")
        for testcase in tests:
            i += 1
            try:
                test(binary, testcase, testMap)
            except AssertionError as err :
                print(f"{colored('#', 'blue')}" + colored(f"{i}", "cyan")
                        + f"\t[{colored('KO', 'red')}]", testcase["name"],\
                      end = "")
                print(err)
                failure += 1
            else:
                print(f"{colored('#', 'blue')}" + colored(f"{i}", "cyan")
                        + f"\t[{colored('OK', 'green')}]", testcase["name"])
                success += 1
        print()
        j += 1
    print("TOTAL: " + colored(f"{i}", 'cyan'))
    print("PASSED: " + colored(f"{success}", "green"))
    print("FAILED: " + colored(f"{failure}", 'red'))
