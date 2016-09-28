import os, subprocess, json

EXE_FILE = "x64\Debug\ParameterList.exe" # should be replaced with the path to the actual executable file
CONFIG_FILE = "testcase.json"

def run():
    with open(CONFIG_FILE, 'r') as fin:
        myList = json.load(fin)

    for myDict in myList:
        operation = myDict["operation"]
        input = myDict["input"]
        output = "output"  # just to be there in command line
        inputPath = os.path.join("x64\Debug", input)
        id = str(myDict["id"])
        type = myDict["type"]

        if operation == "read":
            if type == "Int":
                compare_to = str(myDict["compare_to"]) + '\n'
                outputPath = os.path.join("x64\Debug", output)
                res1 = res2 = []
                res1.append(subprocess.check_output([EXE_FILE, operation, inputPath, id, type, outputPath])[13:].splitlines())
                res2.append(compare_to.splitlines())
                assert res1 == res2
            elif type == "String":
                compare_to = myDict["compare_to"] + '\n'
                outputPath = os.path.join("x64\Debug", output)
                res1 = res2 = []
                res1.append(subprocess.check_output([EXE_FILE, operation, inputPath, id, type, outputPath])[13:].splitlines())
                res2.append(compare_to.splitlines())
                assert res1 == res2
            elif type == "Buffer" or type == "ParameterList":
                output = myDict["output"]
                outputPath = os.path.join("x64\Debug", output)
                if "compare_to" in myDict.keys():
                    compare_to = myDict["compare_to"]
                    compare_toPath = os.path.join("x64\Debug", compare_to)
                    subprocess.call([EXE_FILE, operation, inputPath, id, type, outputPath])
                    assert open(compare_toPath, 'rb').read() == open(outputPath, 'rb').read()
                else:
                    subprocess.call([EXE_FILE, operation, inputPath, id, type, outputPath])
            else:
                continue

        elif operation == "write":
            output = myDict["output"]
            outputPath = os.path.join("x64\Debug", output)

            if type == "Int":
                content = str(myDict["content"])
                subprocess.call([EXE_FILE, operation, inputPath, outputPath, id, type, content])
            elif type == "String":
                content = myDict["content"]
                subprocess.call([EXE_FILE, operation, inputPath, outputPath, id, type, content])
            elif type == "Buffer" or type == "ParameterList":
                content = os.path.join("x64\Debug", myDict["content"])
                subprocess.call([EXE_FILE, operation, inputPath, outputPath, id, type, content])
            else:
                continue

        else:
            continue

run()
print("tests ran successfully")
