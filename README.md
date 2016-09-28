# ParameterList
Serialization module accompanied by a tester in Python.

It is suitable for the communication between processes such as a remote console for the main process and the actual main process, because it can serialize(deserialize) integers, strings, and stl vectors. It can also serialize(deserialize) ParameterLists.
The whole implementation is in a header file for easiness.

A C++ tester reads from and writes in files serialized information.
The Python tester uses a configuration file to parse, read and right serialized information in files and checks if the result is the desired one.

obs: the Python tester is implemented to work for a x64 Debug built and uses the files in \ParameterList\files\
