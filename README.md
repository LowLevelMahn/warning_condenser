# warning_condenser

simple C++ tool for condensing/sorting duplicated warnings in build outputs of gcc,clang
it help to better see relevant warnings or start reducing them beginning with the most occuring

warning_condenser file_with_warnings [-d]

-d shows also the diagnosis

wrote that tool before knowing: `-fdiagnostics-format=json` (https://stackoverflow.com/questions/36657869/how-do-i-dump-gcc-warnings-into-a-structured-format)

tested with clang 14 & 17 and gcc 11 & 13

just grab all the build warnings with 

[build command] > file_with_warnings.txt 2>&1
build command can be make, cmake, a direct gcc,g++,clang,clang++ line, etc.

and run

warning_condenser file_with_warnings.txt

example output:

```
(count:    20) type: -Wunused-function
  (   30) /home/linux/tests/kuzu_dev/kuzu/src/include/common/utils.h:48:13: unused function 'isLittleEndian'
  (   17) /home/linux/tests/kuzu_dev/kuzu/src/include/common/utils.h:36:17: unused function 'nextPowerOfTwo'
  (    3) /home/linux/tests/kuzu_dev/kuzu/src/include/function/cast/functions/numeric_cast.h:103:6: unused function 'tryCastWithOverflowCheck<float, unsigned long>'
  (    3) /home/linux/tests/kuzu_dev/kuzu/src/include/function/cast/functions/numeric_cast.h:66:6: unused function 'tryCastWithOverflowCheck<float, signed char>'
  (    3) /home/linux/tests/kuzu_dev/kuzu/src/include/function/cast/functions/numeric_cast.h:88:6: unused function 'tryCastWithOverflowCheck<float, unsigned char>'
  (    3) /home/linux/tests/kuzu_dev/kuzu/src/include/function/cast/functions/numeric_cast.h:93:6: unused function 'tryCastWithOverflowCheck<float, unsigned short>'
  (    3) /home/linux/tests/kuzu_dev/kuzu/src/include/function/cast/functions/numeric_cast.h:98:6: unused function 'tryCastWithOverflowCheck<float, unsigned int>'
  (    2) /home/linux/tests/kuzu_dev/kuzu/src/include/function/cast/functions/numeric_cast.h:131:6: unused function 'tryCastWithOverflowCheck<double, unsigned char>'
(count:     7) type: -Wpessimizing-move
  (    1) /home/linux/tests/kuzu_dev/kuzu/src/binder/bind/bind_copy.cpp:43:51: moving a temporary object prevents copy elision
  (    1) /home/linux/tests/kuzu_dev/kuzu/src/common/arrow/arrow_converter.cpp:181:12: moving a local object in a return statement prevents copy elision
  (    1) /home/linux/tests/kuzu_dev/kuzu/src/common/arrow/arrow_row_batch.cpp:178:12: moving a local object in a return statement prevents copy elision
  (    1) /home/linux/tests/kuzu_dev/kuzu/src/common/arrow/arrow_row_batch.cpp:547:12: moving a local object in a return statement prevents copy elision
(count:     6) type: -Wunused-variable
  (    1) /home/linux/tests/kuzu_dev/kuzu/src/expression_evaluator/case_evaluator.cpp:104:26: unused variable 'resultEntry'
  (    1) /home/linux/tests/kuzu_dev/kuzu/src/function/cast/cast_fixed_list.cpp:33:18: unused variable 'result'
  (    1) /home/linux/tests/kuzu_dev/kuzu/src/processor/map/map_dummy_scan.cpp:12:10: unused variable 'logicalDummyScan'
  (    1) /home/linux/tests/kuzu_dev/kuzu/src/processor/operator/aggregate/simple_aggregate_scan.cpp:10:16: unused variable 'dataPos'
```

TODOs:
- include/exclude filter for pathes
- importer for -fdiagnostics-format=json
