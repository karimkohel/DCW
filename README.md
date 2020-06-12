# DCW 1.0
Welcome to the **DCW** documentation.
The **DCW** is a lossless compression command line tool for text files. 
The tool is in it's early stages, please feel free to report any bugs to the github [Issues](https://github.com/karimkohel/DCW/issues) page.

## Contents
- [Usage](https://github.com/karimkohel/DCW#usage)
-- [Default](https://github.com/karimkohel/DCW#default-condition)
-- [More Usage](https://github.com/karimkohel/DCW#specific-usage)


## Usage
### Default condition
The tool supports a default user friendly running condition if no command line arguments are provided and to make it easier and faster in testing, by just running the tool like so
> `./DCW`

- Takes in a default input file by the name input.txt
- generates the output files required later for decompression 

---
### Specific Usage
To correctly use the tool to the full of it's extent command line arguments are provided to specify which file to compress/decompress.
> `./DCW <option> <input filename.txt> <compressed filename>`

or

> `./DCW <option> <compressed filename> <output filename.txt>`

|Option | Description |  
| ----------- | ----------- |  
| -c | Compress |  
| -d | Decompress |

- The tool will generate the decompressed/compressed file in the same directory
- more than one file will be generated, all files must be kept for later use in decompression

---

