# shared-memory-linux
Using shared memory in linux to share data between two separate programs (not simultaneously)

# Summary
Writer program finds leaf sub-directories in the given directory and stores some of them on shared memory in a linked list structure after applying a simple encryption.

Reader program decrypts every element of the shared linked list and prints out the result.

# Running
```shell
  sh run.sh [path] [size]
```
size is the size of linked list

path is the directory we look in to it for finding sub-directories

example
```shell
  sh run.sh ~/ 5
```
