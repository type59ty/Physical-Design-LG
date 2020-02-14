# HW3 Abacus
### File hierarchy
```
+-- src/
|   +-- main.cpp
|   +-- ds.h
|   +-- ds.cpp
|   +-- read_legal.h
|   +-- read_legal.cpp
|   +-- read_net.h
|   +-- read_net.cpp
|   +-- read_node.h
|   +-- read_node.cpp
|   +-- read_scl.h
|   +-- read_scl.cpp
|   +-- read_shape.h
|   +-- read_shape.cpp
|   +-- abacus.h
|   +-- abacus.cpp
+-- obj/
|   +-- objective codes
+-- benchmark/
|   +-- benchmark files
--- Makefile
|
--- LG_P76071218
```

### Platform
- Ubuntu 18.04.1 LTS
- g++ 7.4.0

### Usage
- compile
```
$ make
```
- run benchmark 1 ~ 3
```
$ make sb1
$ make sb5
$ make sb19
```
- run all benchmark
```
$ make test_all
```
- run legality checker
```
$ make legal
```
- run HPWL checker
```
$ make hpwl
```

- result
```
Phase 1: .nodes file
         Total Nodes             : 847441
         Movable Nodes           : 765102
         Terminal Nodes          : 82339
         Fixed Terminal Nodes    : 52627
         Fixed_NI Terminal Nodes : 29712
Phase 2: .shapes file
         Total Non-Rectangular Nodes  : 37
Phase 3: .pl file
         Total Nodes  : 847441
Phase 4: .scl file
         NumRows   : 1829
         RowHeight : 9
         Image     : (18, 18) - (22482, 16479)
Phase 5: solution .pl (LG_P76071218_superblue1.pl) file
         Total Nodes  : 847441
-----------------------------------------------------
Phase 6: Check Legality
         ERROR_TYPE 0: 0
         ERROR_TYPE 1: 0
         ERROR_TYPE 2: 0
         ERROR_TYPE 3: 0
         ERROR_TYPE 4: 0
         Placement is legal
-----------------------------------------------------


Phase 1: .nodes file
         Total Nodes             : 772457
         Movable Nodes           : 677416
         Terminal Nodes          : 95041
         Fixed Terminal Nodes    : 74365
         Fixed_NI Terminal Nodes : 20676
Phase 2: .shapes file
         Total Non-Rectangular Nodes  : 115
Phase 3: .pl file
         Total Nodes  : 772457
Phase 4: .scl file
         NumRows   : 2528
         RowHeight : 9
         Image     : (18, 18) - (24745, 22770)
Phase 5: solution .pl (LG_P76071218_superblue5.pl) file
         Total Nodes  : 772457
-----------------------------------------------------
Phase 6: Check Legality
         ERROR_TYPE 0: 0
         ERROR_TYPE 1: 0
         ERROR_TYPE 2: 0
         ERROR_TYPE 3: 0
         ERROR_TYPE 4: 0
         Placement is legal
-----------------------------------------------------


Phase 1: .nodes file
         Total Nodes             : 522775
         Movable Nodes           : 506097
         Terminal Nodes          : 16678
         Fixed Terminal Nodes    : 286
         Fixed_NI Terminal Nodes : 16392
Phase 2: .shapes file
         Total Non-Rectangular Nodes  : 22
Phase 3: .pl file
         Total Nodes  : 522775
Phase 4: .scl file
         NumRows   : 2294
         RowHeight : 9
         Image     : (18, 18) - (10226, 20664)
Phase 5: solution .pl (LG_P76071218_superblue19.pl) file
         Total Nodes  : 522775
-----------------------------------------------------
Phase 6: Check Legality
         ERROR_TYPE 0: 0
         ERROR_TYPE 1: 0
         ERROR_TYPE 2: 0
         ERROR_TYPE 3: 0
         ERROR_TYPE 4: 0
         Placement is legal
-----------------------------------------------------
```

```
Phase 1: .nodes file
         Total Nodes             : 847441
         Movable Nodes           : 765102
         Terminal Nodes          : 82339
         Fixed Terminal Nodes    : 52627
         Fixed_NI Terminal Nodes : 29712
Phase 2: .pl file
         Total Nodes  : 847441
Phase 3: solution .pl (LG_P76071218_superblue1.pl) file
         Movable Nodes: 765102
Phase 4: .nets file
         Total Nets         : 822744
         Total Pins         : 2861188
-----------------------------------------------------
 Total Half Perimeter Wire Length: 332051818 
-----------------------------------------------------
Phase 1: .nodes file
         Total Nodes             : 772457
         Movable Nodes           : 677416
         Terminal Nodes          : 95041
         Fixed Terminal Nodes    : 74365
         Fixed_NI Terminal Nodes : 20676
Phase 2: .pl file
         Total Nodes  : 772457
Phase 3: solution .pl (LG_P76071218_superblue5.pl) file
         Movable Nodes: 677416
Phase 4: .nets file
         Total Nets         : 786999
         Total Pins         : 2500306
-----------------------------------------------------
 Total Half Perimeter Wire Length: 387443376
-----------------------------------------------------
Phase 1: .nodes file
         Total Nodes             : 522775
         Movable Nodes           : 506097
         Terminal Nodes          : 16678
         Fixed Terminal Nodes    : 286
         Fixed_NI Terminal Nodes : 16392
Phase 2: .pl file
         Total Nodes  : 522775
Phase 3: solution .pl (LG_P76071218_superblue19.pl) file
         Movable Nodes: 506097
Phase 4: .nets file
         Total Nets         : 511685
         Total Pins         : 1714351
-----------------------------------------------------
 Total Half Perimeter Wire Length: 163297261
-----------------------------------------------------
```
