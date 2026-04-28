Flight-Manager
Flight‑management tools built to explore data structure design.
Project structure
```
flight-manager/
├── Hash/                     ← Hash-based manager directory
│   ├── ExampleInput.txt      ← Text file containing example input
│   ├── ExampleOutput.txt     ← Text file containing example output
│   ├── Hash                  ← Pre-compiled executable
│   ├── Hash.cpp              ← C++ file containing user input functionality
│   ├── Hash.h                ← Header file containing hash table functions
│   └── LinkedList.h          ← Header file containing linked list implementation
├── LinkedList/               ← Linked list-based manager directory
│   ├── ExampleInput.txt      ← Text file containing example input
│   ├── ExampleOutput.txt     ← Text file containing example output
│   ├── LinkedList            ← Pre-compiled executable
│   ├── LinkedList.cpp        ← C++ file containing user input functionality
│   └── LinkedList.h          ← Header file containing linked list implementation
├── MaxHeap/                  ← Heap-based manager directory
│   ├── ExampleInput.txt      ← Text file containing example input
│   ├── ExampleOutput.txt     ← Text file containing example output
│   ├── MaxHeap               ← Pre-compiled executable
│   ├── MaxHeap.cpp           ← C++ file containing user input functionality
│   └── MaxHeap.h             ← Header file containing heap manipulation functions
└── RedBlackTree/             ← RBT-based manager directory
    ├── ExampleInput.txt      ← Text file containing example input
    ├── ExampleOutput.txt     ← Text file containing example output
    ├── Manager               ← Pre-compiled executable
    ├── Manager.cpp           ← C++ file containing user input functionality
    ├── RedBlackTree.cpp      ← C++ file containing RBT implementation
    └── RedBlackTree.h        ← Header file containg RBT function definitions
```
All programs were compiled using G++.
To compile manually:
  1. Insure that all files: *.cpp, *h (precomiled executable & example IO optional) are present in working directory
  2. Run command "g++ *.cpp -o {name}", for RBT compile using Manager.cpp
